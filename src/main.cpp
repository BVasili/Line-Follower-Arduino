#include <Arduino.h>
#define IRSIZE 5
#define DELAY 20
#define posConst 1000

// Right Motor
const int SR = 6;
const int RF = 10;
const int RB = 9;

// Left Motor
const int SL = 5;
const int LF = 11;
const int LB = 7;

// PD Control
int error, previous_error;
int IRsensor[5];
int position;
int correction;
int RM_Speed, LM_Speed;
const int base_speed = 175;
const int kd = 4, kp = 4;
const int base_position = 2000;

void ReadSensor();
void CalculateError();
void CalculatePreviousError();
void CalculateCorrection();
void SetEngineSpeed();
bool isOnBlack();
bool isOnWhite();

void setup()
{
    Serial.begin(9600);
    pinMode(SR, OUTPUT);
    pinMode(RF, OUTPUT);
    pinMode(RB, OUTPUT);
    pinMode(SL, OUTPUT);
    pinMode(LF, OUTPUT);
    pinMode(LB, OUTPUT);
}
void loop()
{
}

void ReadSensor()
{
    IRsensor[0] = digitalRead(A0);
    IRsensor[1] = digitalRead(A1);
    IRsensor[2] = digitalRead(A2);
    IRsensor[3] = digitalRead(A3);
    IRsensor[4] = digitalRead(A4);
}

void CalculateError()
{
    position = 0;
    int SUM = 0;

    for (int i = 0; i < IRSIZE; i++)
        position += i * posConst * IRsensor[i];

    for (int i = 0; i < IRSIZE; i++)
        SUM += IRsensor[i];

    if (SUM == 0)
        return;

    position /= SUM;

    error = position - base_position;
}

void CalculatePreviousError()
{
    previous_error = error;
}

void CalculateCorrection()
{
    correction = kp * error + kd * (error - previous_error);
}

void SetEngineSpeed()
{
    RM_Speed = base_speed + correction;
    LM_Speed = base_speed - correction;

    analogWrite(SR, RM_Speed);
    digitalWrite(RF, HIGH);
    digitalWrite(RB, LOW);

    analogWrite(SL, LM_Speed);
    digitalWrite(LF, LOW);
    digitalWrite(LB, HIGH);

    delay(DELAY);
}
