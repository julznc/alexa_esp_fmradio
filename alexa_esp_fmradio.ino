#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>


#define SERIAL_BAUDRATE                 115200
#define LED                             0


/* WiFi */
#include "credentials.h" // define ssid and password here
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
AsyncWebServer server(80);
void serverSetup() {
  // custom entry point
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, world");
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
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
  pinMode(LED, OUTPUT);

  // WiFi
  wifiSetup();

  // web server
  serverSetup();

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

}
