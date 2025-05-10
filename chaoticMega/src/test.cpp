// #include "REG.h"
// #include "move.h"
// #include "pindefine.h"
// #include "positionPID.h"
// #include "wit_c_sdk.h"
// #include <Arduino.h>
// #include <MsTimer2.h> //定时器库的头文件
// #include <PIDController.h>
// #include "remotecontrol.h"

// int tick = 0;                          // 计数值
// int cnt_motor_impulse_LEFT_FRONT = 0;  // 100ms内左前接收到的电机的脉冲数
// int cnt_motor_impulse_RIGHT_FRONT = 0; // 100ms内右前接收到的电机的脉冲数
// int cnt_motor_impulse_LEFT_REAR = 0;   // 100ms内左后接收到的电机的脉冲数
// int cnt_motor_impulse_RIGHT_REAR = 0;  // 100ms内右后接收到的电机的脉冲数

// int prev = 0;
// int speed = 60;

// // 中断服务程序
// void onTimer()
// {
//     Serial.print("timer ");
//     Serial.print(tick++);
//     Serial.print("\t");
//     Serial.print(cnt_motor_impulse_LEFT_FRONT);
//     Serial.print("\t");
//     Serial.print(cnt_motor_impulse_LEFT_REAR);
//     Serial.print("\t");
//     Serial.print(cnt_motor_impulse_LEFT_REAR);
//     Serial.print("\t");
//     Serial.println(cnt_motor_impulse_LEFT_REAR);
//     cnt_motor_impulse_LEFT_FRONT = 0;
//     cnt_motor_impulse_LEFT_REAR = 0;
//     cnt_motor_impulse_RIGHT_FRONT = 0;
//     cnt_motor_impulse_RIGHT_REAR = 0;
// }

// void count_LEFT_FRONT()
// {
//     cnt_motor_impulse_LEFT_FRONT++;
// }

// void count_LEFT_REAR()
// {
//     cnt_motor_impulse_LEFT_REAR++;
// }

// void count_RIGHT_FRONT()
// {
//     cnt_motor_impulse_RIGHT_FRONT++;
// }

// void count_RIGHT_REAR()
// {
//     cnt_motor_impulse_RIGHT_REAR++;
// }

// void att_Interrupt(){
//     attachInterrupt(digitalPinToInterrupt(18), count_LEFT_FRONT, RISING);
//     attachInterrupt(digitalPinToInterrupt(19), count_LEFT_REAR, RISING);
//     attachInterrupt(digitalPinToInterrupt(20), count_RIGHT_FRONT, RISING);
//     attachInterrupt(digitalPinToInterrupt(21), count_RIGHT_REAR, RISING);
// }



// void setup()
// {
//     pinModeSetup();
//     Serial.begin(9600);          // 初始化串口
//     MsTimer2::set(100, onTimer); // 设置中断，每1000ms进入一次中断服务程序 onTimer()
//     MsTimer2::start();           // 开始计时
// }
// void loop()
// {

//     for (int i = 0; i < 4000;i++){
//         moveFront(1, speed);
//         att_Interrupt();
//     }
    


    

// }
