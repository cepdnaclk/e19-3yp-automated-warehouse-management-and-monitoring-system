#include <Arduino.h>
#include <Servo.h> // Include the Servo library

#define SERVO_PIN 2 

Servo myServo; // Create a servo object

const int trigPin = 12;
const int echoPin = 4;
const int minimum = 50;

bool facingRight = false; 
bool objectDetectedRight = false; 
bool facingLeft = false; 
bool objectDetectedLeft = false;

long duration;
int distance;

void setup() {
  myServo.attach(SERVO_PIN); // Attach the servo to the GPIO pin

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(LED_BUILTIN, OUTPUT);
  myServo.write(90);  
  Serial.begin(9600);

  
}

int cal_distance(int duration){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
     distance = duration * 0.034 / 2;
     return distance;
}

void loop() {
  
  

  duration = pulseIn(echoPin, HIGH);
  distance = cal_distance(duration);

  Serial.print("Distance: ");
  Serial.println(distance);
    
  if (distance < minimum && distance > 5) {
    objectDetectedRight = true;
    myServo.write(180);            // Move servo to right
    delay(100);
    facingRight = true;
    duration = pulseIn(echoPin, HIGH);
    distance = cal_distance(duration);
    if(distance < minimum && distance > 5) {
      objectDetectedRight = true;
    }else{
      objectDetectedRight = false;
    }
  }

  if(facingRight && !objectDetectedRight){
    myServo.write(90);
  }

  if(facingRight && objectDetectedRight) {
    objectDetectedLeft = true;
    myServo.write(0);
    delay(100);
  //   myServo.write(45);
  //   delay(100);
    duration = pulseIn(echoPin, HIGH);
    distance = cal_distance(duration);
    if(distance < minimum && distance > 5){
      objectDetectedLeft = true;
    }else{
      objectDetectedLeft = false;
    }
  }
  if(facingLeft && !objectDetectedLeft){
    myServo.write(90);
  }
  // if(objectDetectedLeft && objectDetectedRight){
  //   Serial.println("Object detected in both directions");
  //   return;
  // }
  // delay(500);
}

