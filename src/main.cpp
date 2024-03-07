#include <Arduino.h>
int NUM = 0;
int time = 0;

void right(int time)
{
    int NUM = (200);
    analogWrite(6, 201);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    analogWrite(5, 252);
    digitalWrite(7, LOW);
    digitalWrite(11, HIGH);
    delay(time);
}
void left(int time)
{

    int NUM = (150);
    analogWrite(6, 188);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    analogWrite(5, 86);
    digitalWrite(7, LOW);
    digitalWrite(11, HIGH);
    delay(time);
}

void forward(int time)
{
    int NUM = (255);
    analogWrite(6, 254);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    analogWrite(5, 255);
    digitalWrite(7, LOW);
    digitalWrite(11, HIGH);
    delay(time);
}

void stop(int time)
{
    int NUM = (150);
    analogWrite(6, 0);
    analogWrite(5, 0);
    delay(time);
}

void setup()
{
    Serial.begin(9600);
    pinMode(6, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(7, OUTPUT);
}
void loop()
{

    forward(3000);
    right(2000);
    left(2000);
    stop(3000);
}
