#include <Arduino.h>

// Right Motor
int ENA = 6;
int IN1 = 10;
int IN2 = 9;

// Left Motor
int ENB = 5;
int IN3 = 11;
int IN4 = 7;

// PD Control
int error, previous_error;
int kd, kp;
int IRsensors[5];
int position;
const int base =2000;

void calculateError();

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

void calculateError()
{
    position = (0*IRsensors[0]+1000*IRsensors[1]+2000*IRsensors[2]+3000*IRsensors[4]+4000*IRsensors[4]);
    position /= (IRsensors[0]+IRsensors[1]+IRsensors[2]+IRsensors[3]+IRsensors[4]);
}
