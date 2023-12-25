#include <ESP8266WiFi.h>

const char* ssid = "Beacon 1";
const char* password = "987654321";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password,0);
  Serial.begin(9600);
}

void loop() {}