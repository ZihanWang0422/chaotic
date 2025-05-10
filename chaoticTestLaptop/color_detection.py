def hsv2color(hsv_value):
    h, s, v = hsv_value
    if s < 5 and v > 221 and h < 5:
        return 1 #白
    if h > 100 and h < 124 and s > 43 and v > 46:
        return 2 #蓝
    if h > 35 and s > 43 and v > 46 and h < 77:
        return 3 #绿
    if h > 11 and s > 43 and v > 127 and h < 34:
        return 4 #黄
    return 0     #其他的统一黑色处理