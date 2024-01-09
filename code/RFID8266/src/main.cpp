
#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <vector>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <ESP8266WiFi.h>

const char *ssid = "A30s";
const char *password = "dasun531";

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

String tagId = "None";
std::vector<String> tagIds;

void setup(void)
{
    tagIds.push_back("83 71 2D 25");
    tagIds.push_back("74 01 43 4A");
    tagIds.push_back("64 D0 AD 4A");
    tagIds.push_back("74 88 B1 4A");
    tagIds.push_back("64 B3 9C 4A");
    tagIds.push_back("64 C6 5C 4A");
    Serial.begin(9600);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
    nfc.begin();
}

void loop(void)
{
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
            }
        }
    }
    delay(500);
}
