#include <Arduino.h>

const int ldrArray[] = {34, 35, 32, 33, 25, 26, 27, 14};

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
