#include "move.h"

void pinModeSetup(){
    pinMode(LEFT_FRONT_OUT_1, OUTPUT);
    pinMode(LEFT_FRONT_OUT_1, OUTPUT);
    pinMode(LEFT_REAR_OUT_1, OUTPUT);
    pinMode(LEFT_REAR_OUT_1, OUTPUT);
    pinMode(RIGHT_FRONT_OUT_1, OUTPUT);
    pinMode(RIGHT_FRONT_OUT_1, OUTPUT);
    pinMode(RIGHT_REAR_OUT_1, OUTPUT);
    pinMode(RIGHT_REAR_OUT_1, OUTPUT);
    pinMode(LEFT_FRONT_PWM, OUTPUT);
    pinMode(LEFT_REAR_PWM, OUTPUT);
    pinMode(RIGHT_FRONT_PWM, OUTPUT);
    pinMode(RIGHT_REAR_PWM, OUTPUT);
}

void moveFront(int t, int speed)
{
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, HIGH);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    digitalWrite(RIGHT_REAR_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, speed);
    analogWrite(LEFT_REAR_PWM, speed);
    analogWrite(RIGHT_FRONT_PWM, speed);
    analogWrite(RIGHT_REAR_PWM, speed);
    delay(t);
}

void moveBack(int t, int speed)
{
    digitalWrite(LEFT_FRONT_OUT_1, LOW);
    digitalWrite(LEFT_FRONT_OUT_2, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_1, LOW);
    digitalWrite(RIGHT_FRONT_OUT_2, HIGH);
    digitalWrite(LEFT_REAR_OUT_1, LOW);
    digitalWrite(LEFT_REAR_OUT_2, HIGH);
    digitalWrite(RIGHT_REAR_OUT_1, LOW);
    digitalWrite(RIGHT_REAR_OUT_2, HIGH);
    analogWrite(LEFT_FRONT_PWM, speed);
    analogWrite(LEFT_REAR_PWM, speed);
    analogWrite(RIGHT_FRONT_PWM, speed);
    analogWrite(RIGHT_REAR_PWM, speed);
    delay(t);
}

void moveStop()
{
    digitalWrite(LEFT_FRONT_OUT_1, LOW);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    digitalWrite(RIGHT_FRONT_OUT_1, LOW);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, LOW);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    digitalWrite(RIGHT_REAR_OUT_1, LOW);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 0);
    analogWrite(LEFT_REAR_PWM, 0);
    analogWrite(RIGHT_FRONT_PWM, 0);
    analogWrite(RIGHT_REAR_PWM, 0);
    delay(10);
}

void moveTurnRight()
{
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    digitalWrite(RIGHT_FRONT_OUT_1, LOW);
    digitalWrite(RIGHT_FRONT_OUT_2, HIGH);
    digitalWrite(LEFT_REAR_OUT_1, HIGH);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    digitalWrite(RIGHT_REAR_OUT_1, LOW);
    digitalWrite(RIGHT_REAR_OUT_2, HIGH);
    analogWrite(LEFT_FRONT_PWM, 60);
    analogWrite(LEFT_REAR_PWM, 60);
    analogWrite(RIGHT_FRONT_PWM, 60);
    analogWrite(RIGHT_REAR_PWM, 60);
    delay(1);
}

void moveTurnLeft()
{
    digitalWrite(LEFT_FRONT_OUT_1, LOW);
    digitalWrite(LEFT_FRONT_OUT_2, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, LOW);
    digitalWrite(LEFT_REAR_OUT_2, HIGH);
    digitalWrite(RIGHT_REAR_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 50);
    analogWrite(LEFT_REAR_PWM, 50);
    analogWrite(RIGHT_FRONT_PWM, 50);
    analogWrite(RIGHT_REAR_PWM, 50);
    delay(1);
}

void moveTurnAround()
{
    digitalWrite(LEFT_FRONT_OUT_1, LOW);
    digitalWrite(LEFT_FRONT_OUT_2, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, LOW);
    digitalWrite(LEFT_REAR_OUT_2, HIGH);
    digitalWrite(RIGHT_REAR_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 60);
    analogWrite(LEFT_REAR_PWM, 60);
    analogWrite(RIGHT_FRONT_PWM, 60);
    analogWrite(RIGHT_REAR_PWM, 60);
    delay(3450);
}

void moveTurnRightMicro()
{
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    digitalWrite(RIGHT_FRONT_OUT_1, LOW);
    digitalWrite(RIGHT_FRONT_OUT_2, HIGH);
    digitalWrite(LEFT_REAR_OUT_1, HIGH);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    digitalWrite(RIGHT_REAR_OUT_1, LOW);
    digitalWrite(RIGHT_REAR_OUT_2, HIGH);
    analogWrite(LEFT_FRONT_PWM, 60);
    analogWrite(LEFT_REAR_PWM, 60);
    analogWrite(RIGHT_FRONT_PWM, 60);
    analogWrite(RIGHT_REAR_PWM, 60);
    delay(30);
}

void moveTurnLeftMicro()
{
    digitalWrite(LEFT_FRONT_OUT_1, LOW);
    digitalWrite(LEFT_FRONT_OUT_2, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, LOW);
    digitalWrite(LEFT_REAR_OUT_2, HIGH);
    digitalWrite(RIGHT_REAR_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 60);
    analogWrite(LEFT_REAR_PWM, 60);
    analogWrite(RIGHT_FRONT_PWM, 60);
    analogWrite(RIGHT_REAR_PWM, 60);
    delay(30);
}


void moveLeftFront(){
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 60);
    delay(1);
}