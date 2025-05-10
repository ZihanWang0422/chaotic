#include <Arduino.h>
#include <WiFi.h> //wifi功能需要的库
#include <stdlib.h>

#define FRONT 13    // to 48
#define LEFTMICRO 12    // to 41
#define RIGHTMICRO 14   // to 51
#define LEFT90 27   // to 52
#define RIGHT90 26  // to 39
#define STOP 25     // to 49
#define FETCH 33
#define TEST 2

#define DELAYTIME 10

WiFiUDP Udp; // 声明UDP对象

const char *wifi_SSID = "ChaoticCommunication";      // 存储AP的名称信息
const char *wifi_Password = "1123581321"; // 存储AP的密码信息

uint16_t udp_port = 1122; // 存储需要监听的端口号

char incomingPacket[255]; // 存储Udp客户端发过来的数据

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200); // 开启串口，波特率为115200

    WiFi.softAP(wifi_SSID, wifi_Password); // 打开ESP32热点

    Serial.print("\nIP is ");
    Serial.print(WiFi.softAPIP()); // 串口输出模块IP地址

    Udp.begin(udp_port); // 启动UDP监听这个端口

    pinMode(FRONT, OUTPUT);
    pinMode(LEFTMICRO, OUTPUT);
    pinMode(RIGHTMICRO, OUTPUT);
    pinMode(LEFT90, OUTPUT);
    pinMode(RIGHT90, OUTPUT);
    pinMode(STOP, OUTPUT);
    pinMode(FETCH, OUTPUT);
    pinMode(TEST, OUTPUT);

    digitalWrite(FRONT, HIGH);
    digitalWrite(LEFTMICRO, HIGH);
    digitalWrite(RIGHTMICRO, HIGH);
    digitalWrite(LEFT90, HIGH);
    digitalWrite(RIGHT90, HIGH);
    digitalWrite(STOP, HIGH);
    digitalWrite(FETCH, HIGH);
    digitalWrite(TEST, HIGH);
}

void loop()
{
    // put your main code here, to run repeatedly:
    /*接收发送过来的Udp数据*/
    int Data_length = Udp.parsePacket(); // 获取接收的数据的长度
    if (Data_length)                     // 如果有数据那么Data_length不为0，无数据Data_length为0
    {
        int len = Udp.read(incomingPacket, 255); // 读取数据，将数据保存在数组incomingPacket中
        if (len > 0)                             // 为了避免获取的数据后面乱码做的判断
        {
            incomingPacket[len] = 0;
        }
        digitalWrite(atoi(incomingPacket), LOW);
        delay(DELAYTIME);
        digitalWrite(atoi(incomingPacket), HIGH);
        // /*将接受到的数据发送回去*/
        // Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); // 准备发送数据到目标IP和目标端口
        // Udp.print("receive data:");                        // 将数据receive data:放入发送的缓冲区
        // Udp.println(incomingPacket);                       // 将接收到的数据放入发送的缓冲区
        // Udp.endPacket();                                   // 向目标IP目标端口发送数据
    }
}
