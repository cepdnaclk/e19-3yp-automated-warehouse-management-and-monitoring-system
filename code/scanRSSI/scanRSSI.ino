#include <ESP8266WiFi.h>
#include <vector>

struct BeaconData {
  String ssid;
  int rssi;
};



void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
}

void loop() {
    std::vector<BeaconData> beaconData;
    int numNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numNetworks; i++) {
      String currentSSID = WiFi.SSID(i);
      if (currentSSID.startsWith("Beacon")) { 
        BeaconData data;
        data.ssid = currentSSID;
        data.rssi = WiFi.RSSI(i);
//          Serial.println(data.rssi);
        beaconData.push_back(data);
      }
    }
}
