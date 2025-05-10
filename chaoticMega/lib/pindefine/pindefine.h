#ifndef PIN_DEFINE
#define PIN_DEFINE
#include <Arduino.h>
// Pin Defination
// To Motor
//M1 for LEFT_FRONT
//M2 for LEFT_REAR
//M3 for RIGHT_FRONT
//M4 for RIGHT_REAR
#define LEFT_FRONT_OUT_1 22  // Mega output
#define LEFT_FRONT_OUT_2 23  // Mega output
#define RIGHT_FRONT_OUT_1 26 // Mega output
#define RIGHT_FRONT_OUT_2 27 // Mega output
#define LEFT_REAR_OUT_1 30   // Mega output
#define LEFT_REAR_OUT_2 31   // Mega output
#define RIGHT_REAR_OUT_1 28  // Mega output
#define RIGHT_REAR_OUT_2 29  // Mega output
#define LEFT_FRONT_PWM 3// Mega output
#define LEFT_REAR_PWM 4
#define RIGHT_FRONT_PWM 5
#define RIGHT_REAR_PWM 6
// From Motor
#define LEFT_FRONT_IN 36  // Mega input
#define RIGHT_FRONT_IN 40 // Mega input
#define LEFT_REAR_IN 48   // Mega input
#define RIGHT_REAR_IN 42  // Mega input

#define MOVE_FRONT_PIN 48
#define STOP_PIN 49 
#define LEFT_MICRO_PIN 41
#define RIGHT_MICRO_PIN 51 
#define TURN_LEFT_PIN 52
#define TURN_RIGHT_PIN 39

#endif