import cv2
import chaotic_locate
import matplotlib.pyplot as plt

# empty_map = cv2.imread('results.png')
# current_capture = cv2.imread('results_with_vehicle.png')

# ssim, vertices = chaotic_locate.shrink_the_range(
#     empty_map, current_capture)
# print(vertices)


cap = cv2.VideoCapture(0)
ret0, init = cap.read()
while (True):
    # 一帧一帧捕捉
    ret1, curr = cap.read()
    # 我们对帧的操作在这里
    # 显示返回的每帧
    cv2.imshow("test", curr)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break
    ssim, vertices = chaotic_locate.shrink_the_range(init, curr)
    if ssim < 0.95:
        print(vertices)
# 当所有事完成，释放 VideoCapture 对象
cap.release()
cv2.destroyAllWindows()
