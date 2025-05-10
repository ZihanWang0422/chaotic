#ifndef REMOTECONTROL_HHHHH
#define REMOTECONTROL_HHHHH
#include "pindefine.h"
#define DELTA 3
#include <Arduino.h>
void setPinMode();
int judgeAngleLeft(double initial, double now);
int judgeAngleRight(double initial, double now);
// static void ShowHelp(void);
// static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
// static void Delayms(uint16_t ucMs);

#endif