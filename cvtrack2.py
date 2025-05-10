import numpy as np
import cv2
 
font = cv2.FONT_HERSHEY_SIMPLEX
 
lower_red = np.array([0, 127, 128])  # 红色低阈值
upper_red = np.array([5, 255, 255])  # 红色高阈值
 
cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)  # 打开USB摄像头
if (cap.isOpened()):  # 视频打开成功
    flag = 1
else:
    flag = 0
num = 0
if (flag):
    while (True):
        ret, frame = cap.read()  # 读取一帧
        if ret == False:  # 读取帧失败
            break
 
        hsv_img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)# 根据颜色范围删选
        mask_red = cv2.inRange(hsv_img, lower_red, upper_red)
    
 
        mask_red = cv2.medianBlur(mask_red, 7)        # 中值滤波
    
 

        contours2, hierarchy2 = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

 
        for cnt2 in contours2:
            (x, y, w, h) = cv2.boundingRect(cnt2)  # 该函数返回矩阵四个点
            a1 = x + w / 2
            b1 = y + h / 2
            print(a1, b1)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)  # 将检测到的颜色框起来
            cv2.putText(frame, 'red', (x, y - 5), font, 0.7, (0, 0, 255), 2)

    

        num = num + 1
        cv2.imshow("dection", frame)
        #cv2.imwrite("imgs/%d.jpg" % num, frame)#照片写入，注释后不保存图片，但未注释的需要建imgs
        if cv2.waitKey(20) & 0xFF == 27:
            break
cv2.waitKey(0)
cv2.destroyAllWindows()