
#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <vector>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include <Wire.h>

const int HX711_dout = 12; // mcu > HX711 dout pin, must be external interrupt capable!
const int HX711_sck = 13;  // mcu > HX711 sck pin

HX711_ADC LoadCell(HX711_dout, HX711_sck);

unsigned long t = 0;
unsigned long rfidTime = 0;
unsigned long weightTime = 0;
float currentWeight = 0;
volatile boolean newDataReady;

#define AWS_IOT_PUBLISH_TOPIC "palletJack1/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "palletJack1/sub"

WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;

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
  if (!client.connected())
  {
    Serial.println("MQTT Client not connected. Reconnecting...");
    connectAWS();
  }
  StaticJsonDocument<200> doc;
  doc["PalletJackID"] = (String(PalletJackId));
  doc["TagID"] = (tagId);
  doc["Weight"] = String(currentWeight);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}




void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
  NTPConnect();
  // connectAWS();
  nfc.begin();
  float calibrationValue;  // calibration value
  calibrationValue = 3.13; // uncomment this if you want to set this value in the sketch
#if defined(ESP8266) || defined(ESP32)
#endif

  LoadCell.begin();
  LoadCell.setReverseOutput();
  unsigned long stabilizingtime = 1000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true;                 // set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag())
  {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1)
      ;
  }
  else
  {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }

}


void loop()
{
  const int serialPrintInterval = 500;
  now = time(nullptr);

  // if (!client.connected())
  // {
  //   Serial.println("MQTT Client not connected. Reconnecting...");
  //   connectAWS();
  // }
  // else
  // {
  //   client.loop();
  // }

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
    Serial.print("Tag id: ");
    Serial.println(tagId);
    if (millis() > rfidTime + 10 * serialPrintInterval)
    {
      publishMessage();
      rfidTime = millis();
    }
  }
  // get smoothed value from the dataset:
  Serial.print  ("Test: ");
    if (millis() > t + serialPrintInterval)
    {
      currentWeight = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      if (currentWeight < 0)
      {
        currentWeight = 0;
      }
      Serial.println(currentWeight);
      if (millis() > weightTime + 20 * serialPrintInterval)
      {
        publishMessage();
        weightTime = millis();
      }
      t = millis();
    }
  
}
