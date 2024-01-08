#include <Arduino.h>


const int joystickXPin = 39; 
const int joystickYPin = 36; 

void manualMovement();

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Pallet Jack Controller");
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);

  // attachInterrupt(digitalPinToInterrupt(switchPin), switchInterrupt, CHANGE);
  // Serial.println("Moving motor 1 forward");
  // MOTOR1_Move(250,HIGH,LOW);
  // delay(10000);
  // Serial.println("Moving motor 1 backward");
  // MOTOR1_Move(250,LOW,HIGH);
  // delay(10000);
  // Serial.println("Moving motor 2 forward");
  // MOTOR2_Move(250,HIGH,LOW);
  // delay(10000);
  // Serial.println("Moving motor 2 backward");
  // MOTOR2_Move(250,LOW,HIGH);
  // delay(10000);
}

void loop() {
  delay(100);
  manualMovement();
}

void switchInterrupt() {
  // Read the state of the switch
  //int switchState = digitalRead(switchPin);

  // Update the mode based on the switch state
  //manualMode = (switchState == HIGH);

  // if (manualMode) {
  //   Serial.println("Switched to Manual Mode");
  // } else {
  //   Serial.println("Switched to Automated Mode");
  // }
}

void automatedMovement() {
  // Your automated movement logic goes here
  // For example, control the motor to move the pallet jack automatically
  // digitalWrite(motorPin, HIGH);
  // delay(1000);
  // digitalWrite(motorPin, LOW);
  // delay(1000);
}

void manualMovement() {
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);

  int motorSpeedX, motorSpeedY;

  if(joystickXValue >1700 && joystickXValue < 1900 && joystickYValue >1700 && joystickYValue < 1900){
    
    Serial.print(" Motor 1 OFF");
    Serial.print(" Motor 2 OFF");
    return;
  }

  if(joystickXValue > 1800 && joystickXValue <=4100 && joystickYValue <=4100 && joystickYValue > 1850){
    // 2
    motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
   
    Serial.print(" Motor 1 Mode");
    Serial.print(" High Low");

    Serial.print(" Motor 2 Mode");
    Serial.print(" Low High");

  }else if(joystickXValue >1800 && joystickXValue <=4100 && joystickYValue >=0 && joystickYValue <=1750){
    // 3
    motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
    

    Serial.print(" Motor 1 Mode");
    Serial.print(" Low High");

    Serial.print(" Motor 2 Mode");
    Serial.print(" High Low");

  }else if(joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue <=4100 && joystickYValue >1850){
    // 1
    motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
    

    Serial.print(" Motor 1 Mode");
    Serial.print(" High Low");

    Serial.print(" Motor 2 Mode");
    Serial.print(" Low High");

  }else if(joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue >=0 && joystickYValue <=1750){
    // 4
    motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
    

    Serial.print(" Motor 1 Mode");
    Serial.print(" Low High");

    Serial.print(" Motor 2 Mode");
    Serial.print(" High Low");
  }

  Serial.print(" Motor X: ");
  Serial.print(motorSpeedX);
  Serial.print(", Motor Y: ");
  Serial.println(motorSpeedY);
}
