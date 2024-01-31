#include <Arduino.h>

#define MOTOR1_EN_PIN 19
#define PIN_IN1 18
#define PIN_IN2 5
#define MOTOR2_EN_PIN 15
#define PIN_IN3 4
#define PIN_IN4 2
#define joystickXPin 39
#define joystickYPin 36
#define switchPin 23
#define alertPin 22
#define bounceDuration 20
#define directionPin1 21
#define directionPin2 26

const int ldrArray[] = {34, 35, 32, 33, 25};

bool obstacaleAlert = false;
volatile unsigned long bounceTime = 0;
bool manualMode = false;
int *ldrArrayAverage = new int[5];
bool stopRunning = false;
bool pauseRunning = false;

int P, D, I, previousError, PIDvalue, error;
int leftMotor, rightMotor;
int maxSpeed = 240;

float Kp = 0;
float Kd = 0;
float Ki = 0;

int minValues[5], maxValues[5], threshold[5];

void calibrate();
void followTheLine();
void switchInterrupt();
void alertInterrupt();
void obstacleInterrupt();
void manualMovement();
void automatedMovement();

void MOTOR1_Move(int pwmVal, int pin1, int pin2)
{
  analogWrite(MOTOR1_EN_PIN, pwmVal);
  digitalWrite(PIN_IN1, pin1);
  digitalWrite(PIN_IN2, pin2);
}

void MOTOR2_Move(int pwmVal, int pin1, int pin2)
{
  analogWrite(MOTOR2_EN_PIN, pwmVal);
  digitalWrite(PIN_IN3, pin1);
  digitalWrite(PIN_IN4, pin2);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial Begin");
  pinMode(MOTOR1_EN_PIN, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(MOTOR2_EN_PIN, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(alertPin, INPUT);
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);
  pinMode(directionPin1, INPUT);
  pinMode(directionPin2, INPUT);

  for (int i = 0; i < 5; i++)
  {
    pinMode(ldrArray[i], INPUT);
  }

  int switchState = digitalRead(switchPin);
  manualMode = (switchState == HIGH);

  attachInterrupt(digitalPinToInterrupt(switchPin), switchInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(alertPin), alertInterrupt, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(obstacleInputPin), obstacleInterrupt, CHANGE);

  MOTOR1_Move(0, LOW, LOW);
  MOTOR2_Move(0, LOW, LOW);

  calibrate();

  // Serial.println("Moving motor 1 forward");
  // MOTOR1_Move(250,HIGH,LOW);
  // delay(10000);
  // Serial.println("Moving motor 1 backward");
  // delay(10000);
  // Serial.println("Moving motor 2 forward");
  // MOTOR2_Move(250,HIGH,LOW);
  // delay(10000);
  // Serial.println("Moving motor 2 backward");
  // delay(10000);
}

void loop()
{
  if (!stopRunning || manualMode)
  {
    // if(true){
    if (bounceTime > 4000000000)
    {
      bounceTime = 0;
    }
    delay(10);

    if (manualMode)
    {
      // Serial.println("Manual Mode");
      manualMovement();
    }
    else
    {
      // Serial.println("Automated Mode");
      automatedMovement();
    }
  }
  else
  {
    Serial.println("Pallet is paused running. Initiating obstacle avoidance algorighm");
  }
}

void switchInterrupt()
{
  if (millis() > bounceTime)
  {
    int switchState = digitalRead(switchPin);

    manualMode = (switchState == HIGH);

    bounceTime = millis() + bounceDuration;
  }
}

void alertInterrupt()
{
  if (millis() > bounceTime)
  {
    int alertState = digitalRead(alertPin);

    stopRunning = (alertState == HIGH);
    bounceTime = millis() + bounceDuration;
  }
}

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

void automatedMovement()
{

  for (int i = 0; i < 5; i++)
  {
    ldrArrayAverage[i] = analogRead(ldrArray[i]);
  }

  // Serial.print("Dirrection 1 ");
  // Serial.print(digitalRead(directionPin1));
  // // Serial.print("| ");
  // Serial.printf("%04d",ldrArrayAverage[0]);
  // Serial.print(" | ");
  // // Serial.printf("%04d",ldrArrayAverage[1]);
  // // Serial.print(" | ");
  // // Serial.printf("%04d",ldrArrayAverage[2]);
  // // Serial.print(" | ");
  // // Serial.printf("%04d",ldrArrayAverage[3]);
  // // Serial.print(" | ");
  // // Serial.printf("%04d",ldrArrayAverage[4]);
  // // Serial.print(" | ");
  // // Serial.println();
  // // delay(100);

  Serial.print("Digital Read 1: ");
  Serial.print(digitalRead(directionPin1));
  Serial.print("  Digital Read 2: ");
  Serial.println(digitalRead(directionPin2));

  if (!digitalRead(directionPin1) && !digitalRead(directionPin2))
  {
    Serial.println("Stopped");
    MOTOR1_Move(0, LOW, LOW);
    MOTOR2_Move(0, LOW, LOW);
  }
  else if (ldrArrayAverage[2] < threshold[2])
  {
    Serial.println("Moving Forward");
    Kp = 0.006 * (1000 - ldrArrayAverage[2]);
    Kd = 10 * Kp;
    // Ki = 0.0001;
    followTheLine();
    ldrArrayAverage[0] = analogRead(ldrArray[0]);
    ldrArrayAverage[2] = analogRead(ldrArray[2]);
    ldrArrayAverage[4] = analogRead(ldrArray[4]);

    if (ldrArrayAverage[0] < threshold[0] || ldrArrayAverage[4] < threshold[4])
    {
      if (!digitalRead(directionPin1 && digitalRead(directionPin2)))
      {
        while ((ldrArrayAverage[0] > threshold[0] || ldrArrayAverage[4] > threshold[4]))
        {
          Serial.println("Moving Forward");
          Kp = 0.006 * (1000 - ldrArrayAverage[2]);
          Kd = 10 * Kp;
          // Ki = 0.0001;
          followTheLine();
          ldrArrayAverage[0] = analogRead(ldrArray[0]);
          ldrArrayAverage[2] = analogRead(ldrArray[2]);
          ldrArrayAverage[4] = analogRead(ldrArray[4]);
        }
      }
      else if (!digitalRead(directionPin1) && !digitalRead(directionPin2))
      {
        for (int i = 0; i < 20; i++)
        {
          Serial.println("Hardcoded Right");
          MOTOR1_Move(250, HIGH, LOW);
          MOTOR2_Move(250, HIGH, LOW);
          delay(100);
        }
        while (analogRead(ldrArray[2]) < threshold[2])
        {
          Serial.println("Right till Array");
          MOTOR1_Move(250, HIGH, LOW);
          MOTOR2_Move(250, HIGH, LOW);
        }
      }
      else if (digitalRead(directionPin1) && digitalRead(directionPin2))
      {
        for (int i = 0; i < 20; i++)
        {
          Serial.println("Hardcoded Left");
          MOTOR1_Move(250, HIGH, LOW);
          MOTOR2_Move(250, HIGH, LOW);
          delay(100);
        }
        while (analogRead(ldrArray[2]) < threshold[2])
        {
          Serial.println("Left till Array");
          MOTOR1_Move(250, HIGH, LOW);
          MOTOR2_Move(250, HIGH, LOW);
        }
      }
    }
  }
    // // if(((ldrArrayAverage[0] < threshold[0] && ldrArrayAverage[4] > threshold[4]) || (ldrArrayAverage[0] < threshold[0] && ldrArrayAverage[4] < threshold[4])) && !digitalRead(directionPin1)){
    // //   while (1)
    // //   {
    // //     if (ldrArrayAverage[2] < threshold[2] && ldrArrayAverage[4] > threshold[4] && ldrArrayAverage[0] > threshold[0])
    // //     {
    // //       break;
    // //     }
    // //     ldrArrayAverage[0] = analogRead(ldrArray[0]);
    // //     ldrArrayAverage[2] = analogRead(ldrArray[2]);
    // //     ldrArrayAverage[4] = analogRead(ldrArray[4]);
    // //     MOTOR1_Move(250, HIGH, LOW);
    // //     MOTOR2_Move(90, HIGH, LOW );
    // //   }
    // // }else if(((ldrArrayAverage[0] > threshold[0] && ldrArrayAverage[4] < threshold[4]) || (ldrArrayAverage[0] < threshold[0] && ldrArrayAverage[4] < threshold[4])) && digitalRead(directionPin1)){
    // //   while (1)
    // //   {
    // //     if (ldrArrayAverage[2] < threshold[2] && ldrArrayAverage[4] > threshold[4] && ldrArrayAverage[0] < threshold[0])
    // //     {
    // //       break;
    // //     }
    // //     ldrArrayAverage[0] = analogRead(ldrArray[0]);
    // //     ldrArrayAverage[2] = analogRead(ldrArray[2]);
    // //     ldrArrayAverage[4] = analogRead(ldrArray[4]);
    // //     MOTOR1_Move(90, LOW, HIGH);
    // //     MOTOR2_Move(250, LOW, HIGH);
    // //   }
    // // }
  }

  void manualMovement()
  {

    int joystickXValue = analogRead(joystickXPin);
    int joystickYValue = analogRead(joystickYPin);

    int motorSpeedX, motorSpeedY;

    if (joystickXValue > 1500 && joystickXValue < 1700 && joystickYValue > 1500 && joystickYValue < 1700)
    {
      MOTOR1_Move(0, LOW, LOW);
      MOTOR2_Move(0, LOW, LOW);
      // Serial.print(" Motor 1 OFF");
      // Serial.println(" Motor 2 OFF");
      return;
    }

    if (joystickXValue > 1600 && joystickXValue <= 4100 && joystickYValue <= 4100 && joystickYValue > 1650)
    {
      // 2
      motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
      motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
      MOTOR1_Move((motorSpeedY - motorSpeedX), HIGH, LOW);
      MOTOR2_Move(motorSpeedY, LOW, HIGH);
      // Serial.print(" Motor 1 Mode");
      // Serial.print(" High Low");

      // Serial.print(" Motor 2 Mode");
      // Serial.println(" Low High");
      // Serial.print(" Motor 1: ");
      // Serial.print(motorSpeedY - motorSpeedX);
      // Serial.print(", Motor 2: ");
      // Serial.println(motorSpeedY);
    }
    else if (joystickXValue > 1600 && joystickXValue <= 4100 && joystickYValue >= 0 && joystickYValue <= 1550)
    {
      // 3
      motorSpeedX = map(joystickXValue, 4100, 1800, 250, 50);
      motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
      MOTOR1_Move((motorSpeedY - motorSpeedX), LOW, HIGH);
      MOTOR2_Move(motorSpeedY, HIGH, LOW);

      // Serial.print(" Motor 1 Mode");
      // Serial.print(" Low High");

      // Serial.print(" Motor 2 Mode");
      // Serial.println(" High Low");
      // Serial.print(" Motor 1: ");
      // Serial.print(motorSpeedY - motorSpeedX);
      // Serial.print(", Motor 2: ");
      // Serial.println(motorSpeedY);
    }
    else if (joystickXValue >= 0 && joystickXValue <= 1600 && joystickYValue <= 4100 && joystickYValue > 1550)
    {
      // 1
      motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
      motorSpeedY = map(joystickYValue, 4100, 1800, 250, 50);
      MOTOR1_Move(motorSpeedY, HIGH, LOW);
      MOTOR2_Move((motorSpeedY - motorSpeedX), LOW, HIGH);

      // Serial.print(" Motor 1 Mode");
      // Serial.print(" High Low");

      // Serial.print(" Motor 2 Mode");
      // Serial.println(" Low High");
      // Serial.print(" Motor 1: ");
      // Serial.print(motorSpeedY);
      // Serial.print(", Motor 2: ");
      // Serial.println(motorSpeedY - motorSpeedX);
    }
    else if (joystickXValue >= 0 && joystickXValue <= 1600 && joystickYValue >= 0 && joystickYValue <= 1550)
    {
      // 4
      motorSpeedX = map(joystickXValue, 0, 1800, 250, 50);
      motorSpeedY = map(joystickYValue, 0, 1800, 250, 50);
      MOTOR1_Move((motorSpeedY), LOW, HIGH);
      MOTOR2_Move((motorSpeedY - motorSpeedX), HIGH, LOW);

      // Serial.print(" Motor 1 Mode");
      // Serial.print(" Low High");

      // Serial.print(" Motor 2 Mode");
      // Serial.println(" High Low");
      // Serial.print(" Motor 1: ");
      // Serial.print(motorSpeedY);
      // Serial.print(", Motor 2: ");
      // Serial.println(motorSpeedY - motorSpeedX);
    }
  }

  void followTheLine()
  {
    int error = (ldrArrayAverage[1] - ldrArrayAverage[3]);

    P = error;
    I = I + error;
    D = error - previousError;

    PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
    previousError = error;
    // Serial.print("PID Value: ");
    // Serial.println(PIDvalue);

    leftMotor = maxSpeed - PIDvalue;
    rightMotor = maxSpeed + PIDvalue;

    if (leftMotor > 255)
    {
      leftMotor = 255;
    }
    if (leftMotor < 0)
    {
      leftMotor = 0;
    }
    if (rightMotor > 255)
    {
      rightMotor = 255;
    }
    if (rightMotor < 0)
    {
      rightMotor = 0;
    }
    MOTOR1_Move(rightMotor, HIGH, LOW);
    MOTOR2_Move(leftMotor, LOW, HIGH);
    // Serial.print("Motor 1: ");
    // Serial.print(leftMotor);
    // Serial.print(" Motor 2: ");
    // Serial.println(rightMotor);
  }

  void calibrate()
  {
    for (int i = 0; i < 5; i++)
    {
      ldrArrayAverage[i] = analogRead(ldrArray[i]);
    }

    for (int i = 0; i < 5; i++)
    {
      minValues[i] = ldrArrayAverage[i];
      maxValues[i] = ldrArrayAverage[i];
    }

    Serial.println("Calibrating in 5sec....");
    delay(5000);

    for (int i = 0; i < 200; i++)
    {
      delay(12);
      Serial.println("Calibrating....");
      MOTOR1_Move(250, HIGH, LOW);
      MOTOR2_Move(250, HIGH, LOW);

      for (int i = 0; i < 5; i++)
      {
        ldrArrayAverage[i] = analogRead(ldrArray[i]);
      }

      for (int i = 0; i < 5; i++)
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
    for (int i = 0; i < 400; i++)
    {
      delay(12);
      Serial.println("Calibrating....");
      MOTOR1_Move(250, LOW, HIGH);
      MOTOR2_Move(250, LOW, HIGH);

      for (int i = 0; i < 5; i++)
      {
        ldrArrayAverage[i] = analogRead(ldrArray[i]);
      }

      for (int i = 0; i < 5; i++)
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

    for (int i = 0; i < 5; i++)
    {
      threshold[i] = (minValues[i] + maxValues[i]) / 2;
      Serial.print(threshold[i]);
      Serial.print("   ");
    }

    while (!(analogRead(ldrArray[2]) < threshold[2] && analogRead(ldrArray[1]) > threshold[1] && analogRead(ldrArray[3]) > threshold[3]))
    {
      MOTOR1_Move(250, HIGH, LOW);
      MOTOR2_Move(250, HIGH, LOW);
    }

    Serial.println();
    Serial.println("Finished Calibration....");

    MOTOR1_Move(0, LOW, LOW);
    MOTOR2_Move(0, LOW, LOW);
  }
