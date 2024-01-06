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
bool running = true;


long duration;
int distance;

void setup() {
  myServo.attach(SERVO_PIN); // Attach the servo to the GPIO pin

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    
  myServo.write(90);  
  Serial.begin(9600);

  
}

int cal_distance(int duration){

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}

void loop() {
  if(running){

    distance = cal_distance(duration);

    Serial.print("Distance: ");
    Serial.println(distance);
    
    if (distance < minimum && distance > 2) {
      Serial.println("Object Detected at front. Turning Right");
      objectDetectedRight = true;
      myServo.write(180);     // Move servo to right
      facingRight = true;
                 
      delay(5000);

      distance = cal_distance(duration);

      if(distance < minimum && distance > 2) {
        Serial.println("Object Detected at Right. Turning Left");
        objectDetectedRight = true;
        myServo.write(0);     // Move servo to left
        delay(5000);

        distance = cal_distance(duration);

        if (distance < minimum && distance > 2) {
          Serial.println("Object Detected at LEFT.");
          objectDetectedLeft = true;
          facingLeft = true;
          myServo.write(90);     // Move servo to front
          delay(5000);
          Serial.println("Stopping....");
          running = false;


        }else{
          Serial.println("Object Not Detected at LEFT.");
          objectDetectedLeft = false;
          myServo.write(90);    // Move servo to front
          delay(5000);
        }
      }else{
        Serial.println("Object Not Detected at Right.");
        objectDetectedRight = false;
        myServo.write(90);    // Move servo to front     
        delay(5000);
      }

    }
    
    
    delay(200);


    }

  else{
    distance = cal_distance(duration);
    if (distance < minimum && distance > 2){
      running = false;
    }
    else{
      running = true;
    }



  }

  

}

