#include <ESP8266WiFi.h>


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

void setup() {
  // init debug serial port
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  // LED
  pinMode(LED, OUTPUT);

  // WiFi
  wifiSetup();

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

}
