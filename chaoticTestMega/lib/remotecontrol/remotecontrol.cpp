#include "remotecontrol.h"
#define DELTA 5

void setPinMode(){
    pinMode(TURN_LEFT_PIN, INPUT_PULLUP);
    pinMode(TURN_RIGHT_PIN, INPUT_PULLUP);
    pinMode(MOVE_FRONT_PIN,INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);
    pinMode(LEFT_MICRO_PIN, INPUT_PULLUP);
    pinMode(RIGHT_MICRO_PIN, INPUT_PULLUP);
    pinMode(FETCH_PIN, INPUT_PULLUP);
}





int judgeAngleLeft(double initial, double now)
{
    if (initial >= 90) {
        if ((now >= initial && now <= 180) || (now >= -180 && now <= -270 + initial)) {
            return 0;
        }
        return 1;
    } else {
        if (now <= initial + 90-DELTA) {//可以改一下这个数提高精度
            return 0;
        }
        return 1;
    }
}


int judgeAngleRight(double initial, double now)
{
    if (initial <= -90) {
        if ((now >= 270 + initial && now <= 180) || (now >= -180 && now <= initial)) {
            return 0;
        }
        return 1;
    } else {
        if (now >= initial - 90+DELTA) {//可以改一下这个数提高精度
            return 0;
        }
        return 1;
    }
}


// void ShowHelp(void)
// {
//     Serial.print("\r\n************************	 WIT_SDK_DEMO	************************");
//     Serial.print("\r\n************************          HELP           ************************\r\n");
//     Serial.print("UART SEND:a\\r\\n   Acceleration calibration.\r\n");
//     Serial.print("UART SEND:m\\r\\n   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end\r\n");
//     Serial.print("UART SEND:U\\r\\n   Bandwidth increase.\r\n");
//     Serial.print("UART SEND:u\\r\\n   Bandwidth reduction.\r\n");
//     Serial.print("UART SEND:B\\r\\n   Baud rate increased to 115200.\r\n");
//     Serial.print("UART SEND:b\\r\\n   Baud rate reduction to 9600.\r\n");
//     Serial.print("UART SEND:R\\r\\n   The return rate increases to 10Hz.\r\n");
//     Serial.print("UART SEND:r\\r\\n   The return rate reduction to 1Hz.\r\n");
//     Serial.print("UART SEND:C\\r\\n   Basic return content: acceleration, angular velocity, angle, magnetic field.\r\n");
//     Serial.print("UART SEND:c\\r\\n   Return content: acceleration.\r\n");
//     Serial.print("UART SEND:h\\r\\n   help.\r\n");
//     Serial.print("******************************************************************************\r\n");
// }

// static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
// {
//     Serial1.write(p_data, uiSize);
//     Serial1.flush();
// }

// static void Delayms(uint16_t ucMs)
// {
//     delay(ucMs);
// }



