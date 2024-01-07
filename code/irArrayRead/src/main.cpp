#include <Arduino.h>

const int ldrArray[] = {15, 13, 4, 25, 33, 14, 27, 26};

void setup() {
  for(int i = 0; i < 8; i++) {
    pinMode(ldrArray[i], INPUT);
  }
  Serial.begin(115200);
}

void loop() {
  for(int i = 0; i < 8; i++) {
    Serial.printf("%04d", analogRead(ldrArray[i]));
    Serial.print(" | ");
  }
  Serial.println();
  delay(500);
}
