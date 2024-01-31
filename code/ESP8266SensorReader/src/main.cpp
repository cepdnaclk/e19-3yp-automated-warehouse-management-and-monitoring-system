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

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include <vector>
#include <string>

#define AWS_IOT_PUBLISH_TOPIC "palletJack1/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "palletJack1/sub"
#define alertPin 2
#define trigPin 14
#define echoPin 16
#define nfcLED 10 // white
#define awsLED 0  // black
#define dirrectionPin1 3
#define dirrectionPin2 15

short minimum = 10;
short distance;
int obstacalWaitTime = 500;

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
String tagId = "AA AA AA AA";
std::string tagIDstd = "Base Station";

const int HX711_dout = 12; // mcu > HX711 dout pin, must be external interrupt capable!
const int HX711_sck = 13;  // mcu > HX711 sck pin

HX711_ADC LoadCell(HX711_dout, HX711_sck);

struct TagData
{
  std::string tagID;
  short startX;
  short startY;
};

std::vector<TagData> tagData;

bool objectDetected = false;

StaticJsonDocument<200> jsonDoc;
short endX;
short endY;

short nextInstruction = 1;

std::string getStartXY(const std::string &tagID)
{
  for (const TagData &data : tagData)
  {
    if (data.tagID == tagID)
    {
      short startX = data.startX;
      short startY = data.startY;
      return std::to_string(startX) + ", " + std::to_string(startY);
    }
  }
  return "Base Station";
}

void getStartXYShort(short &startX, short &startY)
{
  Serial.print("tagID: ");
  Serial.println(tagId);
  for (const TagData &data : tagData)
  {
    if (data.tagID == tagId.c_str())
    {
      startX = data.startX;
      startY = data.startY;
    }
  }
}

void calculatePath(short endX, short endY)
{
  // 0 - Not Moving
  // 1 - Forward
  // 2 - Left
  // 3 - Right

  short startX;
  short startY;

  getStartXYShort(startX, startY);
  Serial.print("startX: ");
  Serial.print(startX);
  Serial.print(" startY: ");
  Serial.println(startY);
  Serial.print("endX: ");
  Serial.print(endX);
  Serial.print(" endY: ");
  Serial.println(endY);

  if (startX == 1 && startY == 0 && endX == 2 && endY == 1)
  {
    nextInstruction = 2;
  }
  else if (startX == 1 && startY == 0 && endX == 3 && endY == 0)
  {
    nextInstruction = 1;
  }
  else if (startX == 1 && startY == 0 && endX == 4 && endY == 1)
  {
    nextInstruction = 1;
  }
  else if (startX == 1 && startY == 0 && endX == 3 && endY == 2)
  {
    nextInstruction = 2;
  }
  else if (startX == 2 && startY == 1 && endX == 1 && endY == 0)
  {
    nextInstruction = 3;
  }
  else if (startX == 2 && startY == 1 && endX == 3 && endY == 0)
  {
    nextInstruction = 2;
  }
  else if (startX == 2 && startY == 1 && endX == 4 && endY == 1)
  {
    nextInstruction = 2;
  }
  else if (startX == 2 && startY == 1 && endX == 3 && endY == 2)
  {
    nextInstruction = 3;
  }
  else if (startX == 3 && startY == 0 && endX == 2 && endY == 1)
  {
    nextInstruction = 3;
  }
  else if (startX == 3 && startY == 0 && endX == 1 && endY == 0)
  {
    nextInstruction = 1;
  }
  else if (startX == 3 && startY == 0 && endX == 4 && endY == 1)
  {
    nextInstruction = 2;
  }
  else if (startX == 3 && startY == 0 && endX == 3 && endY == 2)
  {
    nextInstruction = 2;
  }
  else if (startX == 4 && startY == 1 && endX == 2 && endY == 1)
  {
    nextInstruction = 2;
  }
  else if (startX == 4 && startY == 1 && endX == 3 && endY == 0)
  {
    nextInstruction = 3;
  }
  else if (startX == 4 && startY == 1 && endX == 1 && endY == 0)
  {
    nextInstruction = 3;
  }
  else if (startX == 4 && startY == 1 && endX == 3 && endY == 2)
  {
    nextInstruction = 2;
  }
  else if (startX == 3 && startY == 2 && endX == 2 && endY == 1)
  {
    nextInstruction = 2;
  }
  else if (startX == 3 && startY == 2 && endX == 3 && endY == 0)
  {
    nextInstruction = 3;
  }
  else if (startX == 3 && startY == 2 && endX == 1 && endY == 0)
  {
    nextInstruction = 2;
  }
  else if (startX == 3 && startY == 2 && endX == 4 && endY == 1)
  {
    nextInstruction = 3;
  }
  else
  {
    nextInstruction = 0;
  }
  Serial.print("Next Instruction: ");
  Serial.println(nextInstruction);
  if (nextInstruction == 0)
  {
    Serial.println("Not Moving");
    digitalWrite(dirrectionPin1, LOW);
    digitalWrite(dirrectionPin2, LOW);
  }
  else if (nextInstruction == 1)
  {
    Serial.println("Moving F");
    digitalWrite(dirrectionPin1, LOW);
    digitalWrite(dirrectionPin2, HIGH);
  }
  else if (nextInstruction == 2)
  {
    Serial.println("Moving R");
    digitalWrite(dirrectionPin1, HIGH);
    digitalWrite(dirrectionPin2, LOW);
  }
  else if (nextInstruction == 3)
  {
    Serial.println("Not Moving L");
    digitalWrite(dirrectionPin1, HIGH);
    digitalWrite(dirrectionPin2, HIGH);
  }
}

int cal_distance()
{
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

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
  analogWrite(awsLED, 100);
}

void publishMessage()
{
  // if (!client.connected())
  // {
  //   Serial.println("MQTT Client not connected. Reconnecting...");
  //   connectAWS();
  // }
  StaticJsonDocument<200> doc;
  doc["id"] = (String(PalletJackId));
  doc["locationid"] = String(tagIDstd.c_str());
  doc["weight"] = String(currentWeight);
  doc["active"] = "Busy";
  doc["obstacle"] = objectDetected ? "Obstacle Detected": "Path is clear";
  // doc["PalletJackID"] = "(String(PalletJackId)";
  // doc["TagID"] = "String(tagId)";
  // doc["Weight"] = "String(currentWeight)";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  Serial.println("Publishing message to AWS IoT..");
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

// void messageReceived(char *topic, byte *payload, unsigned int length)
// {
//   Serial.print("Received [");
//   Serial.print(topic);
//   Serial.print("]: ");
//   for (int i = 0; i < length; i++)
//   {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

void messageReceived(char *topic, byte *payload, unsigned int length)
{
  jsonDoc.clear();
  String payloadStr = "";
  for (int i = 0; i < length; i++)
  {
    payloadStr += (char)payload[i];
  }
  DeserializationError error = deserializeJson(jsonDoc, payloadStr);
  if (error)
  {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }
  endX = jsonDoc["row"].as<short>();
  endY = jsonDoc["col"].as<short>();
  Serial.print("endX: ");
  Serial.println(endX);
  Serial.print("endY: ");
  Serial.println(endY);
  calculatePath(endX, endY);
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
  nfc.begin();
  pinMode(nfcLED, OUTPUT);
  pinMode(awsLED, OUTPUT);
  analogWrite(nfcLED, 100);
  float calibrationValue;   // calibration value
  calibrationValue = -1.80; // uncomment this if you want to set this value in the sketch
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
    Serial.println("Loadcell Startup is complete");
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alertPin, OUTPUT);
  pinMode(dirrectionPin1, OUTPUT);
  pinMode(dirrectionPin2, OUTPUT);
  TagData tag1 = {"74 01 43 4A", 2, 1};
  TagData tag2 = {"64 B3 9C 4A", 3, 2};
  TagData tag3 = {"64 D0 AD 4A", 3, 0};
  TagData tag4 = {"83 71 2D 25", 1, 0};
  TagData tag5 = {"74 88 B1 4A", 4, 1};
  tagData.push_back(tag1);
  tagData.push_back(tag2);
  tagData.push_back(tag3);
  tagData.push_back(tag4);
  tagData.push_back(tag5);

  // for (const auto& entry : tagData) {
  //   String currentTag = entry.first;
  //   short startX = entry.second.first;
  //   short startY = entry.second.second;

  //   Serial.print("CurrentTag: ");
  //   Serial.print(currentTag);
  //   Serial.print(", StartX: ");
  //   Serial.print(startX);
  //   Serial.print(", StartY: ");
  //   Serial.println(startY);
  // }
}

void loop()
{
  static boolean newDataReady = 0;
  const int serialPrintInterval = 500;
  now = time(nullptr);

  if (!client.connected())
  {
    Serial.println("MQTT Client not connected. Reconnecting...");
    analogWrite(awsLED, 0);
    connectAWS();
  }
  else
  {
    client.loop();
  }

  distance = cal_distance();
  // Serial.print("Distance: ");
  // Serial.println(distance);
  objectDetected = false;
  int i = 0;

  if (distance < minimum && distance > 2)
  {
    digitalWrite(alertPin, HIGH);
  }
  else
  {
    digitalWrite(alertPin, LOW);
  }

  while (distance < minimum && distance > 2)
  {
    Serial.println("Waiting for object to move");
    delay(obstacalWaitTime);
    i++;
    distance = cal_distance();
    if (i > 10)
    {
      Serial.println("Object not moving");
      objectDetected = true;
      break;
    }
  }
  if (objectDetected)
  {
    Serial.println("Alerting");
    digitalWrite(alertPin, HIGH);
    publishMessage();
  }

  // Serial.println("Reached card reading");
  if (nfc.tagPresent(10))
  {
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
    Serial.print("Tag id: ");
    tagIDstd = getStartXY(tagId.c_str());
    String s = String(tagIDstd.c_str());
    Serial.println(s);
    if (millis() > rfidTime + 10 * serialPrintInterval)
    {
      publishMessage();
      rfidTime = millis();
    }
    calculatePath(endX, endY);
  }
  // Serial.println("Reached weight reading");
  if (LoadCell.update())
    newDataReady = true;

  if (newDataReady)
  {
    if (millis() > tempTime + 4 * serialPrintInterval)
    {
      // currentWeight = (LoadCell.getData());
      currentWeight = (LoadCell.getData() / 1000);
      Serial.print("Load_cell output val: ");
      if (currentWeight < 1)
      {
        currentWeight = 0;
      }
      Serial.println(currentWeight);
      if (millis() > weightTime + 20 * serialPrintInterval)
      {
        publishMessage();
        weightTime = millis();
      }
      newDataReady = 0;
      tempTime = millis();
    }
  }
}
