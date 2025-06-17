# 驭远杯智能小车项目

## 项目概述
本项目实现了一个智能小车系统，通过图像处理、路径规划和无线通信技术，能够在指定场地中自主导航，完成"寻找宝藏"和"到达终点"等任务。系统包含计算机视觉部分、路径规划算法、车载控制以及无线通信模块。

## 系统架构

```
+-------------------+        +-------------------+        +-------------------+
|                   |        |                   |        |                   |
|   图像处理系统    | -----> |   路径规划算法    | -----> |   无线通信模块    |
|   (OpenCV)        |        |   (Dijkstra)      |        |   (ESP32 WiFi)    |
|                   |        |                   |        |                   |
+-------------------+        +-------------------+        +-------------------+
                                                                   |
                                                                   v
                                                          +-------------------+
                                                          |                   |
                                                          |   小车控制系统    |
                                                          |   (Arduino)       |
                                                          |                   |
                                                          +-------------------+
```

## 文件结构

```
chaotic/
├── .gitignore                  # Git忽略文件
├── .vscode/                    # VSCode配置文件
├── README.md                   # 项目说明文档
├── chaoticVehicle/             # 小车控制程序
│   ├── src/                    # 源代码
│   ├── lib/                    # 依赖库
│   └── platformio.ini          # PlatformIO配置
├── chaoticCommunication/       # 无线通信模块
│   ├── src/                    # 源代码(ESP32)
│   └── lib/                    # 依赖库
├── chaoticLaptop/              # 笔记本端程序
│   ├── semiautomatic.py        # 半自动图像处理
│   ├── color_detection.py      # 颜色检测
│   └── transmission.py         # 数据传输
├── path_gen.c                  # 路径生成算法(Dijkstra)
├── path_gen.exe                # 路径生成执行文件
├── start.py                    # 主程序入口
├── field.txt                   # 场地图像转文本信息
├── findfinish.txt              # 终点路径信息
├── findtreasure.txt            # 宝藏路径信息
├── remote_control.py           # 远程控制脚本
└── TCPserver.py/TCPclient.py   # TCP通信脚本
```

## 技术细节

### 1. 图像处理系统
使用OpenCV库对场地进行拍摄和分析，识别出不同颜色区域：
- 黑色(0): 障碍物
- 白色(1): 可通行区域
- 蓝色(2): 宝藏点
- 绿色(3): 终点
- 黄色(4): 起点

系统通过`start.py`捕获图像，进行色彩增强和HSV空间转换，然后将场地信息存储为文本格式。

### 2. 路径规划算法
使用Dijkstra算法(`path_gen.c`)计算最短路径：
- 从起点到宝藏点的路径
- 从宝藏点到终点的路径
为了提高效率，算法还考虑了转弯次数最少的路径方案。

### 3. 无线通信系统
基于ESP32的WiFi通信模块，建立UDP服务器，接收和发送控制指令。通信协议使用简单的数字命令：
- 13: 前进
- 25: 停止
- 27: 左转90度
- 26: 右转90度
- 12: 微左调整
- 14: 微右调整
- 33: 抓取

### 4. 小车控制系统
Arduino控制的四轮小车，通过控制电机实现：
- 前进/后退
- 左/右转向
- 精细方向调整
- 抓取动作

## 使用说明

### 1. 环境设置
确保安装以下依赖:
- Python 3.x 及 OpenCV, NetworkX, PyLab
- C编译器(用于path_gen.c)
- PlatformIO(用于Arduino和ESP32开发)

### 2. 硬件准备
- 四轮Arduino控制小车
- ESP32通信模块
- 摄像头(连接电脑)

### 3. 运行流程

#### 图像采集与分析
```bash
python start.py
```
按's'键拍摄场地照片，程序会自动处理并生成增强后的图像和场地文本表示。

#### 路径规划
```bash
gcc path_gen.c -o path_gen
./path_gen
```
生成从起点到宝藏点和从宝藏点到终点的路径。

#### 小车控制
1. 上传chaoticCommunication代码到ESP32
2. 上传chaoticVehicle代码到Arduino小车
3. 运行远程控制程序：
```bash
python remote_control.py
```

## 调试与测试
- 使用`screenshot.py`查看图像处理结果
- 使用`NetAssist.exe`测试UDP通信
- 使用`cvtrack2.py`和`opencv_object_tracking.py`进行目标跟踪测试









