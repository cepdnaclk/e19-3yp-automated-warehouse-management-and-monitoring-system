#include <vector>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "A30s";
const char *password = "dasun531";

const char *mqtt_broker = "broker.hivemq.com";
const char *topic = "esp8266/test";
// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";
const int mqtt_port = 1883;

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
WiFiClient espClient;
PubSubClient client(espClient);

String tagId = "None";
std::vector<String> tagIds;

void callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  tagIds.push_back("83 71 2D 25");
  tagIds.push_back("74 01 43 4A");
  tagIds.push_back("64 D0 AD 4A");
  tagIds.push_back("74 88 B1 4A");
  tagIds.push_back("64 B3 9C 4A");
  tagIds.push_back("64 C6 5C 4A");

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected())
  {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str()))
    {
      Serial.println("Public emqx mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  nfc.begin();
  
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  tagIds.push_back(message);
  for(int i=0; i<tagIds.size(); i++){
    Serial.println(tagIds[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop()
{
  client.loop();
  Serial.println("\nScan a NFC tag\n");
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
    Serial.println("Tag id");
    Serial.println(tagId);

    for (int i = 0; i < tagIds.size(); i++)
    {
      if (tagIds[i] == tagId)
      {
        Serial.print("Tag found: ");
        Serial.println(i + 1);
        char msg[10];
        sprintf(msg, "Tag found: %d", i + 1);
        client.publish(topic, msg);
      }
    }
  }
  delay(5000);
}
