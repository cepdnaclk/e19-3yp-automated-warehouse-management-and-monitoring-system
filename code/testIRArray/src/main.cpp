#include <Arduino.h>

void setup(void)
{
  Serial.begin(9600);
  pinMode(15, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{
  delay(100);
  digitalWrite(15, HIGH);
  Serial.println(analogRead(A0));
  digitalWrite(15, LOW);
}
