#include <Arduino.h>

#define MOTOR1_EN_PIN 19
#define PIN_IN1 18
#define PIN_IN2 5
#define MOTOR2_EN_PIN 15
#define PIN_IN3 4
#define PIN_IN4 2


void MOTOR1_Move(int pwmVal,int pin1,int pin2) {
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
}

void loop() {
  Serial.println("MOTOR1_FORWARD full speed");
  MOTOR1_Move(255, HIGH, LOW);
  delay(5000);
  Serial.println("MOTOR1_STOP");
  MOTOR1_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR1_BACKWARD full speed");
  MOTOR1_Move(255, LOW, HIGH);
  delay(5000);
  Serial.println("MOTOR1_STOP");
  MOTOR1_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR2_FORWARD full speed");
  MOTOR2_Move(255, HIGH, LOW);
  delay(5000);
  Serial.println("MOTOR2_STOP");
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR2_BACKWARD full speed");
  MOTOR2_Move(255, LOW, HIGH);
  delay(5000);
  Serial.println("MOTOR2_STOP");
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR1_FORWARD pwm");
  for (int i = 0; i < 255; i++) {
    MOTOR1_Move(i, HIGH, LOW);
    Serial.println("Value :" +  i);
    delay(50);
  }
  Serial.println("MOTOR1_STOP");
  MOTOR1_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR1_BACKWARD pwm");
  for (int i = 0; i < 255; i++) {
    MOTOR1_Move(i, LOW, HIGH);
    Serial.println("Value :" +  i);
    delay(50);
  }
  Serial.println("MOTOR1_STOP");
  MOTOR1_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR2_FORWARD pwm");
  for (int i = 0; i < 255; i++) {
    MOTOR2_Move(i, HIGH, LOW);
    Serial.println("Value :" +  i);
    delay(50);
  }
  Serial.println("MOTOR2_STOP");
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("MOTOR2_BACKWARD pwm");
  for (int i = 0; i < 255; i++) {
    MOTOR2_Move(i, LOW, HIGH);
    Serial.println("Value :" +  i);
    delay(50);
  }
  Serial.println("MOTOR2_STOP");
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("BOTH FORWARD full speed");
  MOTOR1_Move(255, HIGH, LOW);
  MOTOR2_Move(255, HIGH, LOW);
  delay(5000);
  Serial.println("BOTH STOP");
  MOTOR1_Move(0, LOW, LOW);
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("BOTH BACKWARD full speed");
  MOTOR1_Move(255, LOW, HIGH);
  MOTOR2_Move(255, LOW, HIGH);
  delay(5000);
  Serial.println("BOTH STOP");
  MOTOR1_Move(0, LOW, LOW);
  MOTOR2_Move(0, LOW, LOW);
  delay(1000);
  Serial.println("BOTH FORWARD pwm");
  for (int i = 0; i < 255; i++) {
    MOTOR1_Move(i, HIGH, LOW);
    MOTOR2_Move(i, HIGH, LOW);
    Serial.println("Value :" +  i);
    delay(50);
  }
  Serial.println("BOTH STOP");
  MOTOR1_Move(0, LOW, LOW);
  MOTOR2_Move(0, LOW, LOW);
  delay(5000);
}


