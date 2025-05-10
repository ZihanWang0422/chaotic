<!-- LTeX: language=zh-CN -->
# 浑元队芋圆杯项目
## 前言
纪念一次没能成功的尝试，我们真的只差一点儿。  
**该项目目前已被遗弃，不再更新**
## 内容
## 目前进度
已经完成:
* 手动标定场地四角，由此将相机拍摄的场地透视图变换为俯视图。
* 根据图生成最少转弯数的最短路，并使小车严格按照路径形式，使用了PID闭环控制进行路径校正。
* 在宝藏区启动拾取物块装置，并能将物块带到终点。
* 运行`start.py`以启动。
## 开发环境
PlatformIO.
## 代码规范（C/CPP）
```json
 "C_Cpp.clang_format_style": "{ BasedOnStyle: LLVM, BreakBeforeBraces: Linux, UseTab: Never, IndentWidth: 4, TabWidth: 4, AllowShortIfStatementsOnASingleLine: true, IndentCaseLabels: false, ColumnLimit: 0, AccessModifierOffset: -4, NamespaceIndentation: All, FixNamespaceComments: false }",
"C_Cpp.clang_format_fallbackStyle": "{ BasedOnStyle: LLVM, BreakBeforeBraces: Linux, UseTab: Never, IndentWidth: 4, TabWidth: 4, AllowShortIfStatementsOnASingleLine: true, IndentCaseLabels: false, ColumnLimit: 0, AccessModifierOffset: -4, NamespaceIndentation: All, FixNamespaceComments: false }",
```
