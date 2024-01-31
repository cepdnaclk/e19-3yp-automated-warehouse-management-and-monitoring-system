#include <vector>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"

#define AWS_IOT_PUBLISH_TOPIC "palletJack1/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "palletJack1/sub"
#define alertPin 2
#define trigPin 14
#define echoPin 16
#define nfcLED 15 // white
#define awsLED 3  // black

short minimum = 50;
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



const int HX711_dout = 12; // mcu > HX711 dout pin, must be external interrupt capable!
const int HX711_sck = 13;  // mcu > HX711 sck pin

HX711_ADC LoadCell(HX711_dout, HX711_sck);

struct KeyValuePair {
  String tag;
  int nextTurn; // 0  = Forward, 1 = Left, 2 = Right
};

bool objectDetected = false;

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
  analogWrite(awsLED, 50);
}

void publishMessage()
{
  // if (!client.connected())
  // {
  //   Serial.println("MQTT Client not connected. Reconnecting...");
  //   connectAWS();
  // }
  StaticJsonDocument<200> doc;
  doc["PalletJackID"] = (String(PalletJackId));
  doc["TagID"] = String(tagId);
  doc["Weight"] = String(currentWeight);
  doc["Object"] = String(objectDetected);
  // doc["PalletJackID"] = "(String(PalletJackId)";
  // doc["TagID"] = "String(tagId)";
  // doc["Weight"] = "String(currentWeight)";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  Serial.println("Publishing message to AWS IoT..");
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageReceived(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++)
  {
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
  nfc.begin();
  pinMode(nfcLED, OUTPUT);
  pinMode(awsLED, OUTPUT);
  analogWrite(nfcLED, 50);
  float calibrationValue;  // calibration value
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
  
  if(distance < minimum && distance > 2){
    digitalWrite(alertPin, HIGH);
  }else{
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
    Serial.println(tagId);
    if (millis() > rfidTime + 10 * serialPrintInterval)
    {
      publishMessage();
      rfidTime = millis();
    }
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
