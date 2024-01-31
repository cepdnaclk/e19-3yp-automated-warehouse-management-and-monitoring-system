#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  // pinMode(6, OUTPUT);
  // pinMode(A0, OUTPUT);
  // pinMode(8, OUTPUT);
  // pinMode(9, OUTPUT);
  // pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  Serial.println("Turning High");
  // digitalWrite(6, HIGH);
  analogWrite(7, HIGH);
  // digitalWrite(8, HIGH);
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);
  // digitalWrite(11, HIGH);

  delay(5000);

  Serial.println("Turning low");
  // digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  // digitalWrite(8, LOW);
  // digitalWrite(9, LOW);
  // digitalWrite(10, LOW);
  // digitalWrite(11, LOW);

  delay(5000);
}
