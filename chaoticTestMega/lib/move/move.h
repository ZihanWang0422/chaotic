#ifndef MOVE_H
#define MOVE_H
#include <Arduino.h>
#include "pindefine.h"
void moveFront(int t,int speed);
void moveBack(int t, int speed);
void moveStop();
void moveTurnLeft();
void moveTurnRight();
void moveTurnAround();
void pinModeSetup();
void moveTurnLeftMicro();
void moveTurnRightMicro();
void moveLeftFront();
void moveLeftRear();
void moveRightFront();
void moveRightRear();
void moveFetch();
void moveFrontOneBlock(int t, int speed);
#endif