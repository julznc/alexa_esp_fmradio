#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <RDA5807M.h>
#include <fauxmoESP.h>

#include "webserver.h"
#include "credentials.h" // define ssid and password here

#define VIRTUAL_DEVICE_NAME             "fm-radio"
#define SERIAL_BAUDRATE                 (115200)
#define LED_PIN                         (0)


RDA5807M radio;
fauxmoESP fauxmo;


/* WiFi */
void wifiSetup() {
  // set module to station mode
  WiFi.mode(WIFI_STA);

  // connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // wait
  while (WL_CONNECTED != WiFi.status()) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // connected
  Serial.printf("[WIFI] STA Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

/* web server */
AsyncWebServer server(WEBSERVER_PORT);
void serverSetup() {
  // custom entry point
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", INDEX_HTML);
  });

  server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", REDIRECT_HTML);
    String freq = request->arg("frequency");
    String vol = request->arg("volume");
    //Serial.print(freq.c_str()); Serial.println();
    //Serial.print(vol.c_str()); Serial.println();
    radio.setFrequency((uint16_t)(freq.toFloat() * 100));
    radio.setVolume((uint8_t)((vol.toInt() * 15) / 100)); // 0 to 15
  });

  // callbacks
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    if (fauxmo.process(request->client(), request->method() == HTTP_GET, request->url(), String((char *)data))) {
      return;
    }
    //
  });

  // 404
  server.onNotFound([](AsyncWebServerRequest *request) {
    String body = (request->hasParam("body", true)) ? request->getParam("body", true)->value() : String();
    if (fauxmo.process(request->client(), request->method() == HTTP_GET, request->url(), body)) {
      return;
    }
    request->send(404, "text/plain", "Not found");
  });

  // start
  server.begin();
}

void setup() {
  // init debug serial port
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  // LED
  pinMode(LED_PIN, OUTPUT);

  // fm receiver
  radio.init();
  radio.setBandFrequency(RADIO_BAND_FM, 10190);
  radio.setVolume(4);
  radio.setMono(false);
  radio.setMute(false);

  // WiFi
  wifiSetup();

  // web server
  serverSetup();

  // fauxmoESP settings
  fauxmo.createServer(false); // custom tcp server
  fauxmo.setPort(WEBSERVER_PORT);
  fauxmo.enable(true);

  // add virtual devices
  fauxmo.addDevice(VIRTUAL_DEVICE_NAME);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    digitalWrite(LED_PIN, !state);
  });

}

void loop() {
  // poll udp packets
  fauxmo.handle();

  char s[12];
  static unsigned long last_ms = 0;
  if (millis() - last_ms > 10000) {
    last_ms = millis();

    // debug free heap
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());

    // debug radio chip data
    radio.formatFrequency(s, sizeof(s));
    Serial.print("Station:"); Serial.println(s);
    Serial.print("Radio:"); radio.debugRadioInfo();
  }

}
