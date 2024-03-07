#include <Arduino.h>
#define IRSIZE 5
#define DELAY 20
#define posConst 1000

// Right Motor
const int ENA = 6;
const int IN1 = 10;
const int IN2 = 9;

// Left Motor
const int ENB = 5;
const int IN3 = 11;
const int IN4 = 7;

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

void setup()
{
    Serial.begin(9600);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
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

    analogWrite(ENA, RM_Speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, LM_Speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    delay(DELAY);
}
