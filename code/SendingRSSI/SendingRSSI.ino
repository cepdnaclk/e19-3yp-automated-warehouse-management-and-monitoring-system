#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include <Wire.h>

struct BeaconData {
  String ssid;
  int rssi;
};

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;

#define AWS_IOT_PUBLISH_TOPIC   "palletJack1/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "palletJack1/sub"

WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;

std::vector<BeaconData> readRSSI();

void NTPConnect(void){
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish){
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}


void messageReceived(char *topic, byte *payload, unsigned int length){
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void connectAWS(){
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  NTPConnect();

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);


  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)){
    Serial.print(".");
    delay(1000);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}

void publishMessage(const std::vector<BeaconData>& beaconData){
  StaticJsonDocument<200> doc;
  int index = 0;
  for (const auto& data : beaconData) {
    Serial.print("SSID: ");
    Serial.print(data.ssid);
    Serial.print(", RSSI: ");
    Serial.println(data.rssi);
    doc["SSID" + String(index)] = (String(data.ssid));
    doc["RSSI" + String(index)] = (String(data.rssi));
    index = index + 1;
  }
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}


void setup(){
  Serial.begin(9600);
  connectAWS();
}

void loop(){
  delay(2000);
  now = time(nullptr);

  if (!client.connected()){
    connectAWS();
  }else{
    client.loop();
    if (millis() - lastMillis > 1000){
    
      lastMillis = millis();
      publishMessage(readRSSI());
    }
  }
}

std::vector<BeaconData> readRSSI(){
    std::vector<BeaconData> beaconData;
    int numNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numNetworks; i++) {
      String currentSSID = WiFi.SSID(i);
      if (currentSSID.startsWith("Beacon")) {
        BeaconData data;
        data.ssid = currentSSID;
        data.rssi = WiFi.RSSI(i);
        //Serial.println(data.rssi);
        beaconData.push_back(data);
      }
    }
    return beaconData;
  }
