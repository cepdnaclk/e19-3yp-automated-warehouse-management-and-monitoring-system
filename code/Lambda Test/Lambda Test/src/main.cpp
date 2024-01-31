#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"

#define AWS_IOT_PUBLISH_TOPIC "palletJack1/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "palletJack1/sub"


WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;
unsigned long tempTime = 0;
unsigned long rfidTime = 0;
unsigned long weightTime = 0;
float currentWeight = 0;
volatile boolean newDataReady;

String PalletJackId = "1";
String tagId = "None";

void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
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

void connectAWS()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
    Serial.print(".");
    delay(500);
  }

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  client.setServer(MQTT_HOST, 8883);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(500);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  // if (!client.connected())
  // {
  //   Serial.println("MQTT Client not connected. Reconnecting...");
  //   connectAWS();
  // }
  StaticJsonDocument<200> doc;
  doc["palletJackID"] = "1";
  doc["tagID"] = "(tagId)";
  doc["weight"] = "String(currentWeight)";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  Serial.println("Publishing message to AWS IoT..");
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
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

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
  NTPConnect();
  connectAWS();
  client.setCallback(messageReceived);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
}

void loop()
{
  now = time(nullptr);

 if (!client.connected())
  {
    Serial.println("MQTT Client not connected. Reconnecting...");
    connectAWS();
  }
  else
  {
    client.loop();
  }

  if (millis() > rfidTime + 10000)
    {
      publishMessage();
      rfidTime = millis();
    }
}
