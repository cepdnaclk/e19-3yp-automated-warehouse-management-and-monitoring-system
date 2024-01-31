#include <Arduino.h>

const int trigPin = 14;
const int echoPin = 16;
long duration;
int distance;

int cal_distance(int duration);

void setup(void)
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int cal_distance(int duration)
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void loop()
{
  delay(100);
  distance = cal_distance(duration);

  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance < 50)
  {
    Serial.println("Too close");
  }
}
