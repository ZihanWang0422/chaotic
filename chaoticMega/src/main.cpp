// Headers
#include "REG.h"
#include "move.h"
#include "pindefine.h"
#include "positionPID.h"
#include "wit_c_sdk.h"
#include <Arduino.h>
#include <MsTimer2.h> //定时器库的头文件
#include <PIDController.h>
#include "remotecontrol.h"
/*
Test on MEGA 2560. use WT901CTTL sensor

WT901CTTL     MEGA 2560
    VCC <--->  5V/3.3V
    TX  <--->  19(TX1)
    RX  <--->  18(RX1)
    GND <--->  GND
*/
#define SPEED 60
#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE 0x08
#define READ_UPDATE 0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;

static void CmdProcess(void);
static void AutoScanSensor(void);
//static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
//static void Delayms(uint16_t ucMs);
const uint32_t c_uiBaud[8] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400};
void ShowHelp(void)
{
    Serial.print("\r\n************************	 WIT_SDK_DEMO	************************");
    Serial.print("\r\n************************          HELP           ************************\r\n");
    Serial.print("UART SEND:a\\r\\n   Acceleration calibration.\r\n");
    Serial.print("UART SEND:m\\r\\n   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end\r\n");
    Serial.print("UART SEND:U\\r\\n   Bandwidth increase.\r\n");
    Serial.print("UART SEND:u\\r\\n   Bandwidth reduction.\r\n");
    Serial.print("UART SEND:B\\r\\n   Baud rate increased to 115200.\r\n");
    Serial.print("UART SEND:b\\r\\n   Baud rate reduction to 9600.\r\n");
    Serial.print("UART SEND:R\\r\\n   The return rate increases to 10Hz.\r\n");
    Serial.print("UART SEND:r\\r\\n   The return rate reduction to 1Hz.\r\n");
    Serial.print("UART SEND:C\\r\\n   Basic return content: acceleration, angular velocity, angle, magnetic field.\r\n");
    Serial.print("UART SEND:c\\r\\n   Return content: acceleration.\r\n");
    Serial.print("UART SEND:h\\r\\n   help.\r\n");
    Serial.print("******************************************************************************\r\n");
}

static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
    Serial1.write(p_data, uiSize);
    Serial1.flush();
}

static void Delayms(uint16_t ucMs)
{
    delay(ucMs);
}



void CopeCmdData(unsigned char ucData)
{
    static unsigned char s_ucData[50], s_ucRxCnt = 0;

    s_ucData[s_ucRxCnt++] = ucData;
    if (s_ucRxCnt < 3) return; // Less than three data returned
    if (s_ucRxCnt >= 50) s_ucRxCnt = 0;
    if (s_ucRxCnt >= 3) {
        if ((s_ucData[1] == '\r') && (s_ucData[2] == '\n')) {
            s_cCmd = s_ucData[0];
            memset(s_ucData, 0, 50);
            s_ucRxCnt = 0;
        } else {
            s_ucData[0] = s_ucData[1];
            s_ucData[1] = s_ucData[2];
            s_ucRxCnt = 2;
        }
    }
}


static void CmdProcess(void)
{
    switch (s_cCmd) {
    case 'a':
        if (WitStartAccCali() != WIT_HAL_OK) Serial.print("\r\nSet AccCali Error\r\n");
        break;
    case 'm':
        if (WitStartMagCali() != WIT_HAL_OK) Serial.print("\r\nSet MagCali Error\r\n");
        break;
    case 'e':
        if (WitStopMagCali() != WIT_HAL_OK) Serial.print("\r\nSet MagCali Error\r\n");
        break;
    case 'u':
        if (WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK) Serial.print("\r\nSet Bandwidth Error\r\n");
        break;
    case 'U':
        if (WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK) Serial.print("\r\nSet Bandwidth Error\r\n");
        break;
    case 'B':
        if (WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK)
            Serial.print("\r\nSet Baud Error\r\n");
        else {
            Serial1.begin(c_uiBaud[WIT_BAUD_115200]);
            Serial.print(" 115200 Baud rate modified successfully\r\n");
        }
        break;
    case 'b':
        if (WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK)
            Serial.print("\r\nSet Baud Error\r\n");
        else {
            Serial1.begin(c_uiBaud[WIT_BAUD_9600]);
            Serial.print(" 9600 Baud rate modified successfully\r\n");
        }
        break;
    case 'r':
        if (WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK)
            Serial.print("\r\nSet Baud Error\r\n");
        else
            Serial.print("\r\nSet Baud Success\r\n");
        break;
    case 'R':
        if (WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK)
            Serial.print("\r\nSet Baud Error\r\n");
        else
            Serial.print("\r\nSet Baud Success\r\n");
        break;
    case 'C':
        if (WitSetContent(RSW_ACC | RSW_GYRO | RSW_ANGLE | RSW_MAG) != WIT_HAL_OK) Serial.print("\r\nSet RSW Error\r\n");
        break;
    case 'c':
        if (WitSetContent(RSW_ACC) != WIT_HAL_OK) Serial.print("\r\nSet RSW Error\r\n");
        break;
    case 'h':
        ShowHelp();
        break;
    default:
        break;
    }
    s_cCmd = 0xff;
}


static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
    int i;
    for (i = 0; i < uiRegNum; i++) {
        switch (uiReg) {
        case AZ:
            s_cDataUpdate |= ACC_UPDATE;
            break;
        case GZ:
            s_cDataUpdate |= GYRO_UPDATE;
            break;
        case HZ:
            s_cDataUpdate |= MAG_UPDATE;
            break;
        case Yaw:
            s_cDataUpdate |= ANGLE_UPDATE;
            break;
        default:
            s_cDataUpdate |= READ_UPDATE;
            break;
        }
        uiReg++;
    }
}

static void AutoScanSensor(void)
{
    int i;
    int iRetry;

    for (i = 0; i < sizeof(c_uiBaud) / sizeof(c_uiBaud[0]); i++) {
        Serial1.begin(c_uiBaud[i]);
        Serial1.flush();
        iRetry = 2;
        s_cDataUpdate = 0;
        do {
            WitReadReg(AX, 3);
            delay(200);
            while (Serial1.available()) {
                WitSerialDataIn(Serial1.read());
            }
            if (s_cDataUpdate != 0) {
                Serial.print(c_uiBaud[i]);
                Serial.print(" baud find sensor\r\n\r\n");
                ShowHelp();
                return;
            }
            iRetry--;
        } while (iRetry);
    }
    Serial.print("can not find sensor\r\n");
    Serial.print("please check your connection\r\n");
}







void setup()
{
    // put your setup code here, to run once:
    setPinMode();
    Serial.begin(115200);
    WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(SensorUartSend);
    WitRegisterCallBack(SensorDataUpdata);
    WitDelayMsRegister(Delayms);
    Serial.print("\r\n********************** wit-motion normal example  ************************\r\n");
    AutoScanSensor();
}
int i;
float fAcc[3], fGyro[3], fAngle[3];
int flag = 0;
double initial = 0;
void loop()
{
    while (Serial1.available()) {
        WitSerialDataIn(Serial1.read());
    }
    while (Serial.available()) {
        CopeCmdData(Serial.read());
    }
    CmdProcess();
    if (s_cDataUpdate) {
        for (i = 0; i < 3; i++) {
            fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
        }
        if (s_cDataUpdate & ANGLE_UPDATE) {
            Serial.print("angle:");
            // Serial.print(fAngle[0], 3);
            // Serial.print(" ");
            // Serial.print(fAngle[1], 3);
            // Serial.print(" ");
            Serial.print(initial);
            Serial.print(" ");
            Serial.print(fAngle[2], 3);
            Serial.print("\r\n");
            s_cDataUpdate &= ~ANGLE_UPDATE;
        }
        s_cDataUpdate = 0;
    }
    //直行
    if(digitalRead(MOVE_FRONT_PIN) == LOW && flag==0){
        moveFront(50, SPEED);
        Serial.print(digitalRead(MOVE_FRONT_PIN));
        Serial.println("front");
        // moveStop();
    }
    //向左微调
    if(digitalRead(LEFT_MICRO_PIN)==LOW && flag==0){//41
        moveTurnLeftMicro();
        Serial.print(digitalRead(LEFT_MICRO_PIN));
        Serial.println("left_micro");
        moveStop();
    }    //向右微调
    if(digitalRead(RIGHT_MICRO_PIN)==LOW && flag==0){//51
        moveTurnRightMicro();
        Serial.println("right_micro");
        moveStop();
    }
    //停止
    if(digitalRead(STOP_PIN)==LOW &&flag==0){//49
        moveStop();
        delay(10);
        Serial.println("stop");
    }
    //左转90° flag=1
    if (digitalRead(TURN_LEFT_PIN) == LOW && flag == 0) {
        initial = fAngle[2];
        flag = 1;
        Serial.println("1");  
    }
    if (judgeAngleLeft(initial, fAngle[2]) == 0 && flag == 1) {
        moveTurnLeft();
        Serial.println("2");
        // Serial.println(fAngle[2]);
    } else if (judgeAngleLeft(initial, fAngle[2]) == 1 && flag==1) {
        moveStop();
        initial = 0;
        flag = 0;
        Serial.println("3");
    }
    // 右转90° flag=2
    if (digitalRead(TURN_RIGHT_PIN) == LOW && flag == 0) {
        initial = fAngle[2];
        flag = 2;
        Serial.println("4");
    }
    if (judgeAngleRight(initial, fAngle[2]) == 0 && flag == 2) {
        moveTurnRight();
        Serial.println("5");
    } else if (judgeAngleRight(initial,fAngle[2])==1 && flag==2){
        moveStop();
        initial = 0;
        flag = 0;
        Serial.println("6");
    }
}
