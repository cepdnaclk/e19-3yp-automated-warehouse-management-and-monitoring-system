#include <Servo.h> // Include the Servo library

#define SERVO_PIN 15 

Servo myServo; // Create a servo object

void setup() {
  myServo.attach(SERVO_PIN); // Attach the servo to the GPIO pin
}

void loop() {
  myServo.write(0);   // Move servo to 0 degrees
  delay(1000);
  myServo.write(90);  // Move servo to 90 degrees
  delay(1000);
  myServo.write(180); // Move servo to 180 degrees
  delay(1000);
}
