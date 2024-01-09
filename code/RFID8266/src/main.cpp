
#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

void setup(void) {
    Serial.begin(9600);
    Serial.println("NDEF Reader");
    nfc.begin();
}

void loop(void) {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();
        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();

        for (int i = 0; i < recordCount; i++) {
            byte payload[64];
            NdefRecord record = message.getRecord(i);
            Serial.print("Record ");
            Serial.println(i + 1);
            Serial.print("Type: ");
            Serial.println(record.getType());
            Serial.print("Payload: ");
            record.getPayload(payload);
            Serial.println((char*)payload);
            Serial.println();
        }

    }
    delay(5000);
}