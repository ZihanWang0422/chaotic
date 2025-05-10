#include "REG.h"
#include "move.h"
#include "pindefine.h"
#include "remotecontrol.h"
#include "wit_c_sdk.h"
#include <Arduino.h>
#include <MsTimer2.h> //定时器库的头文件
#include <Servo.h>

int tick = 0;                          // 计数值
int cnt_motor_impulse_LEFT_FRONT = 0;  // 100ms内左前接收到的电机的脉冲数
int cnt_motor_impulse_RIGHT_FRONT = 0; // 100ms内右前接收到的电机的脉冲数
int cnt_motor_impulse_LEFT_REAR = 0;   // 100ms内左后接收到的电机的脉冲数
int cnt_motor_impulse_RIGHT_REAR = 0;  // 100ms内右后接收到的电机的脉冲数

int prev = 0;
int speed = 60;

#define SPEED 60
#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE 0x08
#define READ_UPDATE 0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;

static void CmdProcess(void);
static void AutoScanSensor(void);
// static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
// static void Delayms(uint16_t ucMs);
const uint32_t c_uiBaud[8] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400};

int total_impulse_LF = 0, total_impulse_LR = 0, total_impulse_RF = 0, total_impulse_RR = 0;

int limit = 690;
int set1, set2, set3, set4;//////这里可能要改成0
double err1i = 0, err2i = 0, err3i = 0, err4i = 0; // 上上次的误差
double err1j = 0, err2j = 0, err3j = 0, err4j = 0; // 上次的误差
double err1k = 0, err2k = 0, err3k = 0, err4k = 0; // 本次的误差
double kp_speed = 0.1;
double ki_speed = 0.1;
int total_set1 = 0, total_set2 = 0, total_set3 = 0, total_set4 = 0;//每个电机应该要走的速度
double err1j_dis = 0, err2j_dis = 0, err3j_dis = 0, err4j_dis = 0; // 上次的距离误差
double err1k_dis = 0, err2k_dis = 0, err3k_dis = 0, err4k_dis = 0; // 本次的距离误差
double err1_dis_total = 0, err2_dis_total = 0, err3_dis_total = 0, err4_dis_total = 0;//电机的总距离差
double kp_dis = 0.15;
double ki_dis = 0;
double kd_dis = 0.2;

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

// 中断服务程序
void onTimer()
{
    Serial.print("timer ");
    Serial.print(tick++);
    Serial.print("\t");
    Serial.print(cnt_motor_impulse_LEFT_FRONT);
    Serial.print("\t");
    Serial.print(cnt_motor_impulse_LEFT_REAR);
    Serial.print("\t");
    Serial.print(cnt_motor_impulse_RIGHT_FRONT);
    Serial.print("\t");
    Serial.println(cnt_motor_impulse_RIGHT_REAR);
    err1i = err1j;
    err1j = err1k;
    err2i = err2j;
    err2j = err2k;
    err3i = err3j;
    err3j = err3k;
    err4i = err4j;
    err4j = err4k;

    err1j_dis = err1k_dis;
    err2j_dis = err2k_dis;
    err3j_dis = err3k_dis;
    err4j_dis = err4k_dis;

    err1k_dis = limit - total_impulse_LF;//当前的距离误差=一格的总脉冲-当前已走过的脉冲
    err2k_dis = limit - total_impulse_LR;//当前的距离误差=一格的总脉冲-当前已走过的脉冲
    err3k_dis = limit - total_impulse_RF;//当前的距离误差=一格的总脉冲-当前已走过的脉冲
    err4k_dis = limit - total_impulse_RR;//当前的距离误差=一格的总脉冲-当前已走过的脉冲

    err1_dis_total += err1k_dis;//距离误差的计算
    err2_dis_total += err2k_dis;//距离误差的计算
    err3_dis_total += err3k_dis;//距离误差的计算
    err4_dis_total += err4k_dis;//距离误差的计算

    total_set1 = int(kp_dis * err1k_dis + ki_dis * err1_dis_total + kd_dis * (err1k_dis - err1j_dis));
    total_set2 = int(kp_dis * err2k_dis + ki_dis * err2_dis_total + kd_dis * (err2k_dis - err2j_dis));
    total_set3 = int(kp_dis * err3k_dis + ki_dis * err3_dis_total + kd_dis * (err3k_dis - err3j_dis));
    total_set4 = int(kp_dis * err4k_dis + ki_dis * err4_dis_total + kd_dis * (err4k_dis - err4j_dis));


    err1k = total_set1 - cnt_motor_impulse_LEFT_FRONT;//速度误差计算
    err2k = total_set2 - cnt_motor_impulse_LEFT_REAR;//速度误差计算
    err3k = total_set3 - cnt_motor_impulse_RIGHT_FRONT;//速度误差计算
    err4k = total_set4 - cnt_motor_impulse_RIGHT_REAR;//速度误差计算


    set1 += int(kp_speed * (err1k - err1j)  + ki_speed * err1k );
    set2 += int(kp_speed * (err2k - err2j)  + ki_speed * err2k );
    set3 += int(kp_speed * (err3k - err3j)  + ki_speed * err3k );
    set4 += int(kp_speed * (err4k - err4j)  + ki_speed * err4k );
    // Serial.print(err1);
    // Serial.print("\t");
    // Serial.print(err2);
    // Serial.print("\t");
    // Serial.print(err3);
    // Serial.print("\t");
    // Serial.println(err4);
    cnt_motor_impulse_LEFT_FRONT = 0;
    cnt_motor_impulse_LEFT_REAR = 0;
    cnt_motor_impulse_RIGHT_FRONT = 0;
    cnt_motor_impulse_RIGHT_REAR = 0;
}

void count_LEFT_FRONT()
{
    cnt_motor_impulse_LEFT_FRONT++;
    total_impulse_LF++;
}

void count_LEFT_REAR()
{
    cnt_motor_impulse_LEFT_REAR++;
    total_impulse_LR++;
}

void count_RIGHT_FRONT()
{
    cnt_motor_impulse_RIGHT_FRONT++;
    total_impulse_RF++;
    // Serial.println("1");
}

void count_RIGHT_REAR()
{
    cnt_motor_impulse_RIGHT_REAR++;
    total_impulse_RR++;
    // Serial.println("2");
}

void att_Interrupt()
{
    attachInterrupt(digitalPinToInterrupt(LEFT_FRONT_IN), count_LEFT_FRONT, RISING);
    attachInterrupt(digitalPinToInterrupt(LEFT_REAR_IN), count_LEFT_REAR, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_FRONT_IN), count_RIGHT_FRONT, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_REAR_IN), count_RIGHT_REAR, RISING);
}

void setup()
{
    // put your setup code here, to run once
    pinModeSetup();       // 电机的引脚声明
    setPinMode();         // 与ESP32互联的引脚声明
    Serial.begin(115200); // 初始化串口
    WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(SensorUartSend);
    WitRegisterCallBack(SensorDataUpdata);
    WitDelayMsRegister(Delayms);
    Serial.print("\r\n********************** wit-motion normal example  ************************\r\n");
    AutoScanSensor();
    MsTimer2::set(50, onTimer); // 设置中断，每1000ms进入一次中断服务程序 onTimer()
    MsTimer2::start();           // 开始计时
}

float fAcc[3], fGyro[3], fAngle[3];
double angle()
{
    while (Serial1.available()) {
        WitSerialDataIn(Serial1.read());
    }
    while (Serial.available()) {
        CopeCmdData(Serial.read());
    }
    CmdProcess();
    if (s_cDataUpdate) {
        for (int i = 0; i < 3; i++) {
            fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
        }
        if (s_cDataUpdate & ANGLE_UPDATE) {
            Serial.print("angle:");
            // Serial.print(fAngle[0], 3);
            // Serial.print(" ");
            // Serial.print(fAngle[1], 3);
            // Serial.print(" ");
            // Serial.print(initial);
            // Serial.print(" ");
            Serial.print(fAngle[2], 3);
            Serial.print("\r\n");
            s_cDataUpdate &= ~ANGLE_UPDATE;
        }
        s_cDataUpdate = 0;
    }
    return fAngle[2];
}

void errToZero(){
    err1i = 0;
    err1j = 0;
    err1k = 0;
    err2i = 0;
    err2j = 0;
    err2k = 0;
    err3i = 0;
    err3j = 0;
    err3k = 0;
    err4i = 0;
    err4j = 0;
    err4k = 0;
    err1j_dis = 0;
    err1k_dis = 0;
    err2j_dis = 0;
    err2k_dis = 0;
    err3j_dis = 0;
    err3k_dis = 0;
    err4j_dis = 0;
    err4k_dis = 0;
    err1_dis_total = 0;
    err2_dis_total = 0;
    err3_dis_total = 0;
    err4_dis_total = 0;
}

void oneBlock()
{
    total_impulse_LF = 0;
    total_impulse_LR = 0;
    total_impulse_RF = 0;
    total_impulse_RR = 0;

    errToZero();
    set1 = 0, set2 = 0, set3 = 0, set4 = 0;
    while (total_impulse_LF <= limit && total_impulse_LR <= limit && total_impulse_RF <= limit && total_impulse_RR <= limit) {//////可能要改
        moveFrontOneBlock(1, set1, set2, set3+8, set4+8);
        att_Interrupt();    
    }
    // moveBack(1, 10);
    // if(cnt_motor_impulse_LEFT_FRONT<=limit){
    //     moveLeftFront();
    //     attachInterrupt(digitalPinToInterrupt(LEFT_FRONT_IN), count_LEFT_FRONT, RISING);
    // }
    // else{
    //     digitalWrite(LEFT_FRONT_OUT_1, LOW);
    //     digitalWrite(LEFT_FRONT_OUT_2, LOW);
    // }

    // if(cnt_motor_impulse_LEFT_REAR<=limit){
    //     moveLeftRear();
    //     attachInterrupt(digitalPinToInterrupt(LEFT_REAR_IN), count_LEFT_FRONT, RISING);
    // }
    // else{
    //     digitalWrite(LEFT_REAR_OUT_1, LOW);
    //     digitalWrite(LEFT_REAR_OUT_2, LOW);
    // }

    // if(cnt_motor_impulse_RIGHT_FRONT<=limit){
    //     moveRightFront();
    //     attachInterrupt(digitalPinToInterrupt(RIGHT_FRONT_IN), count_LEFT_FRONT, RISING);
    // }
    // else{
    //     digitalWrite(RIGHT_FRONT_OUT_1, LOW);
    //     digitalWrite(RIGHT_FRONT_OUT_2, LOW);
    // }

    // if(cnt_motor_impulse_RIGHT_REAR<=limit){
    //     moveRightRear();
    //     attachInterrupt(digitalPinToInterrupt(RIGHT_REAR_IN), count_LEFT_FRONT, RISING);
    // }
    // else{
    //     digitalWrite(RIGHT_REAR_OUT_1, LOW);
    //     digitalWrite(RIGHT_REAR_OUT_2, LOW);
    // }
    Serial.print(total_impulse_LF);
    Serial.print("\t");
    Serial.print(total_impulse_LR);
    Serial.print("\t");
    Serial.print(total_impulse_RF);
    Serial.print("\t");
    Serial.println(total_impulse_RR);
}

int i;
int flag = 0;
int initial = 0;
void loop()
{
    // put your main code here, to run repeatedly:
    angle();
    if(digitalRead(MOVE_FRONT_PIN) == LOW && flag==0){
        oneBlock();
        moveStop();
        delay(500);
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
        moveTurnRightMicro();
        delay(10);
        moveStop();
        delay(500);
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
        moveTurnLeftMicro();
        delay(10);
        moveStop();
        delay(500);
    }
    if(digitalRead(FETCH_PIN)==LOW &&flag==0){//49
        moveFetch();
    }
}