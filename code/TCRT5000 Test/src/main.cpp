#include <Arduino.h>

const int pinIRd = 22;
const int pinIRa = 34;

void setup()
{
  Serial.begin(115200);
  pinMode(pinIRd,INPUT);
  pinMode(pinIRa,INPUT);

}

void loop()
{
  Serial.print("Analog Reading=");
  Serial.print(analogRead(pinIRa));
  Serial.print("\t Digital Reading=");
  Serial.println(digitalRead(pinIRd));

  delay(500);
  
}