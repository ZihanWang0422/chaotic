import cv2
import os
from color_detection import hsv2color

result = cv2.imread('result.png')
hsv = cv2.cvtColor(result, cv2.COLOR_BGR2HSV)
i = j = 40
# mat = []
with open('field.txt', 'w') as output:
    while i < 720:
#        row = []
        while j < 720:
#            row.append(hsv2color(hsv[i, j]))
            output.write(str(hsv2color(hsv[i, j])))
            j += 80
#        mat.append(row)
        j = 40
        i += 80
#    print(mat)
# 原理：在每个方格中心取样本点考虑颜色。
# 后期如果需要的话可能考虑对于某个方格多取几个采样点