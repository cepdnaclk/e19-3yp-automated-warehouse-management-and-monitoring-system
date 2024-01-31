#include <Arduino.h>

const int ldrArray[] = {34, 35, 32, 33, 25};

void setup() {
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);
  for(int i = 0; i < 5; i++) {
    pinMode(ldrArray[i], INPUT);
  }
  Serial.begin(115200);
}

void loop() {
  for(int i = 0; i < 5; i++) {
    Serial.printf("%04d", analogRead(ldrArray[i]));
    Serial.print(" | ");
  }
  Serial.println();
  delay(500);
}
