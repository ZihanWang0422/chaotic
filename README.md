# Chaotic Project

## 项目概述
该项目实现了图像处理和路径生成算法。通过捕捉和处理图像，将图像转换为文本格式，并使用Dijkstra算法生成最短路径。

## 文件结构

```
chaotic/
├── .gitignore
├── .vscode/
│   ├── launch.json
│   └── settings.json
├── NetAssist.exe
├── README.md
├── chaoticCascade/
│   ├── negadata.txt
│   └── posdata.txt
├── chaoticLaptop/
│   └── test_path_gen.c
├── chaoticTestIILaptop/
│   └── test_path_gen.c
├── chaoticTestLaptop/
│   ├── color_detection.py
│   ├── semi_automatic.py
│   └── test_path_gen.c
├── field.txt
├── findfinish.txt
├── findtreasure.txt
├── path_gen.c
├── path_gen.exe
└── start.py
```

## 文件说明

### 根目录
- `.gitignore`：指定Git应忽略的文件和目录。
- `.vscode/launch.json`：配置VS Code的调试器。
- `.vscode/settings.json`：配置VS Code的用户设置和偏好。
- `NetAssist.exe`：用于网络辅助的可执行文件。
- `README.md`：项目的概述和使用说明。
- `field.txt`：存储图像中的颜色信息，表示为文本格式。
- `findfinish.txt`：存储从起点到终点的路径信息。
- `findtreasure.txt`：存储从起点到宝藏点的路径信息。
- `path_gen.c`：实现路径生成算法，使用Dijkstra算法在图像表示的图形中找到最短路径。
- `path_gen.exe`：用于路径生成的可执行文件。
- `start.py`：使用OpenCV库捕捉图像，并对图像进行处理和增强。

### chaoticCascade 目录
- `negadata.txt`：包含负样本图像的路径，用于图像处理和训练。
- `posdata.txt`：包含正样本图像的路径，用于图像处理和训练。

### chaoticLaptop 目录
- `test_path_gen.c`：路径生成算法的测试代码，验证算法的正确性。

### chaoticTestIILaptop 目录
- `test_path_gen.c`：路径生成算法的测试代码，验证算法的正确性。

### chaoticTestLaptop 目录
- `color_detection.py`：包含颜色检测的函数。
- `semi_automatic.py`：包含图像处理的辅助函数。
- `test_path_gen.c`：路径生成算法的测试代码，验证算法的正确性。

## 使用说明

### 1. 运行 `start.py`
捕捉和处理图像，将图像转换为文本格式，并生成 `field.txt` 文件。
```bash
python 

start.py
```

### 2. 编译并运行 `path_gen.c`
使用Dijkstra算法生成路径，并将路径信息分别存储在 `findfinish.txt` 和 `findtreasure.txt` 文件中。
```bash
gcc 

path_gen.c

 -o path_gen
./path_gen
```

### 3. 查看路径信息
查看 `field.txt`, `findfinish.txt`, 和 `findtreasure.txt` 获取路径信息。

## 贡献
Xuanlin Fan/Jiawei Zhang/Zihan Wang

## 许可证
该项目使用 MIT 许可证。详细信息请参阅 LICENSE 文件。

