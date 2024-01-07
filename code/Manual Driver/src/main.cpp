#include <Arduino.h>

//ESP32 arrangment
#define MOTOR1_EN_PIN 19
#define PIN_IN1 18
#define PIN_IN2 5
#define MOTOR2_EN_PIN 15
#define PIN_IN3 4
#define PIN_IN4 2

// const int switchPin = 2;     // Switch pin
const int joystickXPin = 34; // Joystick X-axis pin
const int joystickYPin = 35; // Joystick Y-axis pin
bool manualMode = true;

void switchInterrupt();
void manualMovement();
void automatedMovement();


void MOTOR1_Move(int pwmVal,int pin1,int pin2) { // pwmVal= speed of the motor, pin1 and pin2 are the direction of the motor
  analogWrite(MOTOR1_EN_PIN, pwmVal);
  digitalWrite(PIN_IN1, pin1);
  digitalWrite(PIN_IN2, pin2);
}

void MOTOR2_Move(int pwmVal,int pin1,int pin2) {
  analogWrite(MOTOR2_EN_PIN, pwmVal);
  digitalWrite(PIN_IN3, pin1);
  digitalWrite(PIN_IN4, pin2);
}



void setup() {
  Serial.begin(115200);
  pinMode(MOTOR1_EN_PIN, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);  
  pinMode(PIN_IN2, OUTPUT);  
  pinMode(MOTOR2_EN_PIN, OUTPUT);  
  pinMode(PIN_IN3, OUTPUT);  
  pinMode(PIN_IN4, OUTPUT); 
  // pinMode(switchPin, INPUT_PULLUP);
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
  delay(50);
  
  if (manualMode) {

    // Manual mode logic
    manualMovement();
  } else {
    // Automated mode logic
    automatedMovement();
  }
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
    MOTOR1_Move(0, HIGH, HIGH);
    MOTOR2_Move(0, HIGH, HIGH);
    Serial.print(" Motor 1 OFF");
    Serial.print(" Motor 2 OFF");
    return;
  }

  if(joystickXValue > 1800 && joystickXValue <=4100 && joystickYValue <=4100 && joystickYValue > 1800){
    // 2
    motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
    MOTOR1_Move((motorSpeedY - motorSpeedX), HIGH, LOW);
    MOTOR2_Move(motorSpeedY, LOW, HIGH);
    Serial.print(" Motor 1 Mode");
    Serial.print(" High Low");

    Serial.print(" Motor 2 Mode");
    Serial.print(" Low High");

  }else if(joystickXValue >1800 && joystickXValue <=4100 && joystickYValue >=0 && joystickYValue <=1800){
    // 3
    motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
    MOTOR1_Move(motorSpeedY,LOW, HIGH);
    MOTOR2_Move(motorSpeedY,HIGH,LOW);

    Serial.print(" Motor 1 Mode");
    Serial.print(" Low High");

    Serial.print(" Motor 2 Mode");
    Serial.print(" High Low");

  }else if(joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue <=4100 && joystickYValue >1800){
    // 1
    motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
    MOTOR1_Move(motorSpeedY,HIGH,LOW);
    MOTOR2_Move((motorSpeedY-motorSpeedX), LOW, HIGH);

    Serial.print(" Motor 1 Mode");
    Serial.print(" High Low");

    Serial.print(" Motor 2 Mode");
    Serial.print(" Low High");

  }else if(joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue >=0 && joystickYValue <=1800){
    // 4
    motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
    motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
    MOTOR1_Move((motorSpeedY-motorSpeedX),LOW,HIGH);
    MOTOR2_Move(motorSpeedY,HIGH,LOW);

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
