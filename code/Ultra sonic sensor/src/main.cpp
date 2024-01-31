#include <Arduino.h>
#include <Servo.h> // Include the Servo library

#define alertPin 2
#define trigPin 14
#define echoPin 16

short minimum = 50;
short distance;
int obstacalWaitTime = 500;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alertPin, OUTPUT);
}

int cal_distance()
{
  long duration;  
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
    distance = cal_distance();
    Serial.print("Distance: ");
    Serial.println(distance);
    bool objectDetected = false;
    // int i = 0;
    // while(distance < minimum && distance > 2) {\
    //   Serial.println("Waiting for object to move");
    //   delay(obstacalWaitTime);
    //   i++;
    //   distance = cal_distance();
    //   if(i > 10) {
    //     Serial.println("Object not moving");
    //     objectDetected = true;
    //     break;
    //   }
    // }
    
    // if(objectDetected) {
    //   Serial.println("Alerting");
    //   digitalWrite(alertPin, HIGH);
    // }else {
    //   Serial.println("No object detected");
    //   digitalWrite(alertPin, LOW);
    // }
    delay(200);
}
