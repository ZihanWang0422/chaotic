#include "move.h"
#include <Servo.h> 

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
    analogWrite(LEFT_FRONT_PWM, 60);
    analogWrite(LEFT_REAR_PWM, 60);
    analogWrite(RIGHT_FRONT_PWM, 60);
    analogWrite(RIGHT_REAR_PWM, 60);
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
    analogWrite(LEFT_FRONT_PWM, 50);
    analogWrite(LEFT_REAR_PWM, 50);
    analogWrite(RIGHT_FRONT_PWM, 50);
    analogWrite(RIGHT_REAR_PWM, 50);
    delay(75);
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
    analogWrite(LEFT_FRONT_PWM, 50);
    analogWrite(LEFT_REAR_PWM, 50);
    analogWrite(RIGHT_FRONT_PWM, 50);
    analogWrite(RIGHT_REAR_PWM, 50);
    delay(80);
}

void moveLeftFront(){
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, 60);
    delay(1);
}

void moveRightFront(){
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    analogWrite(RIGHT_FRONT_PWM, 60);
    delay(1);
}

void moveLeftRear(){
    digitalWrite(LEFT_REAR_OUT_1, HIGH);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    analogWrite(LEFT_REAR_PWM, 60);
    delay(1);
}

void moveRightRear(){
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(RIGHT_REAR_PWM, 60);
    delay(1);
}

void moveFetch(){
    int pos = 160;
    Servo myservo;
    myservo.attach(9, 500, 2500);
    myservo.write(pos);
    delay(3000);
    for (int i = 0; i <= 160;i++){
        myservo.write(pos-i);
        delay(10);
    }
}

void moveFrontOneBlock(int t, int speed1,int speed2,int speed3,int speed4)
{
    digitalWrite(LEFT_FRONT_OUT_1, HIGH);
    digitalWrite(LEFT_FRONT_OUT_2, LOW);
    digitalWrite(RIGHT_FRONT_OUT_1, HIGH);
    digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    digitalWrite(LEFT_REAR_OUT_1, HIGH);
    digitalWrite(LEFT_REAR_OUT_2, LOW);
    digitalWrite(RIGHT_REAR_OUT_1, HIGH);
    digitalWrite(RIGHT_REAR_OUT_2, LOW);
    analogWrite(LEFT_FRONT_PWM, speed1);
    analogWrite(LEFT_REAR_PWM, speed2);
    analogWrite(RIGHT_FRONT_PWM, speed3);
    analogWrite(RIGHT_REAR_PWM, speed4);
    delay(t);
}