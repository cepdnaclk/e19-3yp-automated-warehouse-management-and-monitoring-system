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
  Serial.println(analogRead(A0));
}
