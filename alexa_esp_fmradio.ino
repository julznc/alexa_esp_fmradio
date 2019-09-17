#include <ESP8266WiFi.h>

#define SERIAL_BAUDRATE                 115200
#define LED                             0

void setup() {
  // Init debug serial port
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  pinMode(LED, OUTPUT);

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

}
