#include <Arduino.h>

// #define MOTOR1_EN_PIN 19
// #define PIN_IN1 18
// #define PIN_IN2 5
// #define MOTOR2_EN_PIN 15
// #define PIN_IN3 4
// #define PIN_IN4 2
#define joystickXPin 39
#define joystickYPin 36
// #define switchPin 23
// #define alertPin 22
// #define obstacleInputPin 13
// #define bounceDuration 20

// const int ldrArray[] = {34, 35, 32, 33, 25, 26, 27, 14};

// bool obstacaleAlert = false;
// volatile unsigned long bounceTime = 0;
// bool manualMode = false;
// int *ldrArrayValues = new int[8];
// int *ldrArrayAverage = new int[5];
// bool stopRunning = false;
// bool pauseRunning = false;

// int P, D, I, previousError, PIDvalue, error;
// int lsp, rsp;
// int lfspeed = 240;

// float Kp = 0;
// float Kd = 0;
// float Ki = 0 ;

// int minValues[6], maxValues[6], threshold[6];

// void calibrate();
// void followTheLine();
// void switchInterrupt();
// void alertInterrupt();
// void obstacleInterrupt();
// void manualMovement();
// void automatedMovement();

// void MOTOR1_Move(int pwmVal, int pin1, int pin2)
// {
//   analogWrite(MOTOR1_EN_PIN, pwmVal);
//   digitalWrite(PIN_IN1, pin1);
//   digitalWrite(PIN_IN2, pin2);
// }

// void MOTOR2_Move(int pwmVal, int pin1, int pin2)
// {
//   analogWrite(MOTOR2_EN_PIN, pwmVal);
//   digitalWrite(PIN_IN3, pin1);
//   digitalWrite(PIN_IN4, pin2);
// }

void setup()
{
  Serial.begin(115200);
  // pinMode(MOTOR1_EN_PIN, OUTPUT);
  // pinMode(PIN_IN1, OUTPUT);
  // pinMode(PIN_IN2, OUTPUT);
  // pinMode(MOTOR2_EN_PIN, OUTPUT);
  // pinMode(PIN_IN3, OUTPUT);
  // pinMode(PIN_IN4, OUTPUT);
  // pinMode(switchPin, INPUT);
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);

  // for(int i = 0; i < 8; i++) {
  //   pinMode(ldrArray[i], INPUT);
  // }

  // int switchState = digitalRead(switchPin);
  // manualMode = (switchState == HIGH);

  // attachInterrupt(digitalPinToInterrupt(switchPin), switchInterrupt, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(alertPin), alertInterrupt, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(obstacleInputPin), obstacleInterrupt, CHANGE);

  // calibrate();

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

void loop()
{
  Serial.print("X value: ");
  Serial.print(analogRead(joystickXPin));
  
  Serial.print(" Y value: ");
  Serial.println(analogRead(joystickYPin));

  delay(100);
  //   }
  // }
}

// void switchInterrupt()
// {
//   if (millis() > bounceTime)
//   {
//     int switchState = digitalRead(switchPin);

//     manualMode = (switchState == HIGH);

//     if (manualMode)
//     {
//       Serial.println("Switched to Manual Mode");
//     }
//     else
//     {
//       Serial.println("Switched to Automated Mode");
//     }
//     bounceTime = millis() + bounceDuration;
//   }
// }

// void alertInterrupt(){
// if(millis() > bounceTime)
//   {
//     int alertState = digitalRead(alertPin);

//     stopRunning = (alertState == HIGH);

//     if (stopRunning)
//     {
//       Serial.println("Pallet is stopped due to obstacles");
//     }
//     bounceTime = millis() + bounceDuration;
//   }
// }

// void obstacleInterrupt(){
//   if(millis() > bounceTime)
//   {
//     int switchState = digitalRead(obstacleInputPin);

//     pauseRunning = (switchState == HIGH);

//     if (pauseRunning)
//     {
//       Serial.println("Pallet is paused running. Initiating obstacle avoidance algorighm");
//     }
//     else
//     {
//       Serial.println("Pallet is resuming running");
//     }
//     bounceTime = millis() + bounceDuration;
//   }
// }
unsigned long int i = 0;
unsigned long int j = 0;
unsigned long int k = 0;

// void automatedMovement() {
  //     for(int i = 0; i < 8; i++) {
  //       ldrArrayValues[i] = analogRead(ldrArray[i]);
  //     }

  //     ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
  //     ldrArrayAverage[1] = ldrArrayValues[2];
  //     ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
  //     ldrArrayAverage[3] = ldrArrayValues[5];
  //     ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;

  //     // Serial.print(" ");
  //     // Serial.print(ldrArrayAverage[0]);
  //     // Serial.print(" ");
  //     // Serial.print(ldrArrayAverage[1]);
  //     // Serial.print(" ");
  //     // Serial.print(ldrArrayAverage[2]);
  //     // Serial.print(" ");
  //     // Serial.print(ldrArrayAverage[3]);
  //     // Serial.print(" ");
  //     // Serial.print(ldrArrayAverage[4]);
  //     // Serial.print(" ");
  //     // Serial.println();
  //     // delay(500);

  //     if (ldrArrayAverage[0] > threshold[1] && ldrArrayAverage[4] < threshold[5] )
  //     {
  //       lsp = 0; rsp = lfspeed;
  //       MOTOR1_Move(0, LOW, LOW);
  //       MOTOR2_Move(lfspeed, HIGH, LOW);
  //     }

  //     else if (ldrArrayAverage[0] > threshold[5] && ldrArrayAverage[4] < threshold[1])
  //     {
  //       lsp = lfspeed; rsp = 0;
  //       MOTOR1_Move(lfspeed, HIGH, LOW);
  //       MOTOR2_Move(0, LOW, LOW);
  //     }
  //     else if (ldrArrayAverage[3] > threshold[3])
  //     {
  //       Kp = 0.0006 * (1000 - ldrArrayAverage[3]);
  //       Kd = 10 * Kp;
  //       //Ki = 0.0001;
  //       followTheLine();
  //     }
  //   
// }

// void manualMovement()
// {
//   // while(1){
//   int joystickXValue = analogRead(joystickXPin);
//   int joystickYValue = analogRead(joystickYPin);

//   int motorSpeedX, motorSpeedY;

//   if (joystickXValue > 1700 && joystickXValue < 1900 && joystickYValue > 1700 && joystickYValue < 1900)
//   {
//     MOTOR1_Move(0, HIGH, HIGH);
//     MOTOR2_Move(0, HIGH, HIGH);
//     Serial.println("Stop");
//     return;
//   }

//   if (joystickXValue > 1800 && joystickXValue <= 4100 && joystickYValue <= 4100 && joystickYValue > 1850)
//   {
//     // 2
//     Serial.println("2");
//     motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
//     motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
//     Serial.print("Pwm M1: ");
//     Serial.print(motorSpeedY - motorSpeedX);
//     Serial.print("IN M1: HIGH LOW");
//     Serial.print("  Pwm M2: ");
//     Serial.print(motorSpeedY);
//     Serial.print("IN M2: LOW HIGH");
//     MOTOR1_Move((motorSpeedY - motorSpeedX), HIGH, LOW);
//     MOTOR2_Move(motorSpeedY, LOW, HIGH);
//     Serial.print(" Motor 1 Mode");
//     Serial.print(" High Low");

//     Serial.print(" Motor 2 Mode");
//     Serial.print(" Low High");
//   }
//   else if (joystickXValue > 1800 && joystickXValue <= 4100 && joystickYValue >= 0 && joystickYValue <= 1750)
//   {
//     // 3
//     Serial.println("3");

//     motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
//     motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
//     MOTOR1_Move(motorSpeedY, LOW, HIGH);
//     MOTOR2_Move(motorSpeedY, HIGH, LOW);

//     Serial.print(" Motor 1 Mode");
//     Serial.print(" Low High");

//     Serial.print(" Motor 2 Mode");
//     Serial.print(" High Low");
//   }
//   else if (joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue <= 4100 && joystickYValue > 1850)
//   {
//     // 1
//     Serial.println("1");

//     motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
//     motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
//     MOTOR1_Move(motorSpeedY, HIGH, LOW);
//     MOTOR2_Move((motorSpeedY - motorSpeedX), LOW, HIGH);

//     Serial.print(" Motor 1 Mode");
//     Serial.print(" High Low");

//     Serial.print(" Motor 2 Mode");
//     Serial.print(" Low High");
//   }
//   else if (joystickXValue >= 0 && joystickXValue <= 1800 && joystickYValue >= 0 && joystickYValue <= 1750)
//   {
//     // 4
//     Serial.println("4");

//     motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
//     motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
//     MOTOR1_Move((motorSpeedY - motorSpeedX), LOW, HIGH);
//     MOTOR2_Move(motorSpeedY, HIGH, LOW);

//     Serial.print(" Motor 1 Mode");
//     Serial.print(" Low High");

//     Serial.print(" Motor 2 Mode");
//     Serial.print(" High Low");
//   }

//   Serial.print(" Motor X: ");
//   Serial.print(motorSpeedX);
//   Serial.print(", Motor Y: ");
//   Serial.println(motorSpeedY);
// }
// }

// void followTheLine(){
//   int error = (ldrArrayAverage[2] - ldrArrayAverage[4]);

//   P = error;
//   I = I + error;
//   D = error - previousError;

//   PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
//   previousError = error;

//   lsp = lfspeed - PIDvalue;
//   rsp = lfspeed + PIDvalue;

//   if (lsp > 255) {
//     lsp = 255;
//   }
//   if (lsp < 0) {
//     lsp = 0;
//   }
//   if (rsp > 255) {
//     rsp = 255;
//   }
//   if (rsp < 0) {
//     rsp = 0;
//   }
//   MOTOR1_Move(lsp, HIGH, LOW);
//   MOTOR2_Move(rsp, HIGH, LOW);
// }

// void calibrate()
// {
//   for(int i = 0; i < 8; i++) {
//       ldrArrayValues[i] = analogRead(ldrArray[i]);
//   }

//   ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
//   ldrArrayAverage[1] = ldrArrayValues[2];
//   ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
//   ldrArrayAverage[3] = ldrArrayValues[5];
//   ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;

//   for ( int i = 0; i < 5; i++)
//   {
//     minValues[i] = ldrArrayAverage[i];
//     maxValues[i] = ldrArrayAverage[i];
//   }

//   Serial.println("Calibrating in 5sec....");
//   delay(5000);

//   for (int i = 0; i < 10000; i++)
//   {
//     Serial.println("Calibrating....");
//     MOTOR1_Move(250,HIGH,LOW);
//     MOTOR2_Move(250,LOW,HIGH);

//     for(int i = 0; i < 8; i++) {
//       ldrArrayValues[i] = analogRead(ldrArray[i]);
//     }

//     ldrArrayAverage[0] = (ldrArrayValues[0] + ldrArrayValues[1]) / 2;
//     ldrArrayAverage[1] = ldrArrayValues[2];
//     ldrArrayAverage[2] = (ldrArrayValues[3] + ldrArrayValues[4]) / 2 ;
//     ldrArrayAverage[3] = ldrArrayValues[5];
//     ldrArrayAverage[4] = (ldrArrayValues[6] + ldrArrayValues[7]) / 2;

//     for ( int i = 0; i < 5; i++)
//     {
//       if (ldrArrayAverage[i] < minValues[i])
//       {
//         minValues[i] = ldrArrayAverage[i];
//       }
//       if (ldrArrayAverage[i] > maxValues[i])
//       {
//         maxValues[i] = ldrArrayAverage[i];

//       }
//     }
//   }

//   for ( int i = 0; i < 5; i++)
//   {
//     threshold[i] = (minValues[i] + maxValues[i]) / 2;
//     Serial.print(threshold[i]);
//     Serial.print("   ");
//   }
//   Serial.println();
//   Serial.println("Finished Calibration....");

//   MOTOR1_Move(0,LOW, LOW);
//   MOTOR2_Move(0,LOW, LOW);
// }
