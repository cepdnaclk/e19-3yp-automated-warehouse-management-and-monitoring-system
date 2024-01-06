#include <Arduino.h>

#define MOTOR1_EN_PIN 23
#define PIN_IN1 22
#define PIN_IN2 21
#define MOTOR2_EN_PIN 5
#define PIN_IN3 19
#define PIN_IN4 18

int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 240;

float Kp = 0;
float Kd = 0;
float Ki = 0 ;

int minValues[6], maxValues[6], threshold[6];
void calibrate();
void followTheLine();

const int ldrArray[] = {15, 13, 4, 25, 33, 14, 27, 26};
int *ldrArrayValues = new int[8];
int *ldrArrayAverage = new int[5];

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
  for(int i = 0; i < 8; i++) {
    pinMode(ldrArray[i], INPUT);
  } 
}

void loop() {
  
  calibrate();
  
  while (1)
  {
    for(int i = 0; i < 8; i++) {
      ldrArrayValues[i] = analogRead(ldrArray[i]);
    }

    ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
    ldrArrayAverage[1] = ldrArrayValues[2];
    ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
    ldrArrayAverage[3] = ldrArrayValues[5];
    ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;

    // Serial.print(" ");
    // Serial.print(ldrArrayAverage[0]);
    // Serial.print(" ");
    // Serial.print(ldrArrayAverage[1]);
    // Serial.print(" ");
    // Serial.print(ldrArrayAverage[2]);
    // Serial.print(" ");
    // Serial.print(ldrArrayAverage[3]);
    // Serial.print(" ");
    // Serial.print(ldrArrayAverage[4]);
    // Serial.print(" ");
    // Serial.println();
    // delay(500);

    if (ldrArrayAverage[0] > threshold[1] && ldrArrayAverage[4] < threshold[5] )
    {
      lsp = 0; rsp = lfspeed;
      MOTOR1_Move(0, LOW, LOW);
      MOTOR2_Move(lfspeed, HIGH, LOW);
    }

    else if (ldrArrayAverage[0] > threshold[5] && ldrArrayAverage[4] < threshold[1])
    { 
      lsp = lfspeed; rsp = 0;
      MOTOR1_Move(lfspeed, HIGH, LOW);
      MOTOR2_Move(0, LOW, LOW);
    }
    else if (ldrArrayAverage[3] > threshold[3])
    {
      Kp = 0.0006 * (1000 - ldrArrayAverage[3]);
      Kd = 10 * Kp;
      //Ki = 0.0001;
      followTheLine();
    }
  }
}

void followTheLine(){
  int error = (ldrArrayAverage[2] - ldrArrayAverage[4]);

  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  if (lsp > 255) {
    lsp = 255;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 255) {
    rsp = 255;
  }
  if (rsp < 0) {
    rsp = 0;
  }
  MOTOR1_Move(lsp, HIGH, LOW);
  MOTOR2_Move(rsp, HIGH, LOW);
}

void calibrate()
{
  Serial.println("Calibrating...");
  for(int i = 0; i < 8; i++) {
      ldrArrayValues[i] = analogRead(ldrArray[i]);
  }

  ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
  ldrArrayAverage[1] = ldrArrayValues[2];
  ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
  ldrArrayAverage[3] = ldrArrayValues[5];
  ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;
  
  for ( int i = 0; i < 5; i++)
  {
    minValues[i] = ldrArrayAverage[i];
    maxValues[i] = ldrArrayAverage[i];
  }
  
  for (int i = 0; i < 3000; i++)
  {
    Serial.println("Moving motor 1");
    MOTOR1_Move(200,HIGH,LOW);
    Serial.println("Moving motor 2");
    MOTOR2_Move(200,LOW,HIGH);

    for(int i = 0; i < 8; i++) {
      ldrArrayValues[i] = analogRead(ldrArray[i]);
    }

    ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
    ldrArrayAverage[1] = ldrArrayValues[2];
    ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
    ldrArrayAverage[3] = ldrArrayValues[5];
    ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;

    for ( int i = 0; i < 5; i++)
    {
      if (ldrArrayAverage[i] < minValues[i])
      {
        minValues[i] = ldrArrayAverage[i];
      }
      if (ldrArrayAverage[i] > maxValues[i])
      {
        maxValues[i] = ldrArrayAverage[i];
      }
    }
  }

  for ( int i = 0; i < 5; i++)
  {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print(threshold[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  MOTOR1_Move(0,LOW, LOW);
  MOTOR2_Move(0,LOW, LOW);
}

