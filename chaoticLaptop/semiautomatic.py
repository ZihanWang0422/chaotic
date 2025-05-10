# 本程序修改自https://blog.csdn.net/qq_43360420/article/details/125686144?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-1-125686144-blog-114697641.235^v27^pc_relevant_3mothn_strategy_and_data_recovery&spm=1001.2101.3001.4242.2&utm_relevant_index=4
# 为 CSDN 用户霜晨月所原创，被gitee.com/sunkenstar所修改
# 如有侵权请联系fusion_er@outlook.com


import cv2
import numpy as np
import imutils
class GetRoiMouse():

    def __init__(self, img):
        self.lsPointsChoose = []
        self.tpPointsChoose = []
        self.pointsCount = 0  # 顶点计数
        self.pointsMax = 4  # 最大顶点个数
        self.mouseWindowName = 'Counterclockwisely, choose the four vertices from top-left '
        self.img = img  # 输入的图像

    def mouseclick(self):  # 显示一个窗口
        cv2.namedWindow(self.mouseWindowName)
        # opecv可以设置监听鼠标
        # setMouseCallback(windowName,onMouse())
        # 在onMouse中写点击鼠标时要进行的工作
        cv2.setMouseCallback(self.mouseWindowName, self.on_mouse)
        cv2.imshow(self.mouseWindowName, self.img)
        cv2.waitKey(0)
	# 检测当前点个数，满足要求时关闭图像显示窗口
    def checkPointsNum(self):
        if len(self.lsPointsChoose) == 4:
            print('I get 4 points!')
            cv2.destroyAllWindows()

    # OpenCV的鼠标响应函数，可以在内部定义鼠标的各种响应
    def on_mouse(self, event, x, y, flags, param):
        # 左键点击
        if event == cv2.EVENT_LBUTTONDOWN:
            print('left-mouse')
            self.pointsCount += 1
            print(self.pointsCount)
            point1 = (x, y)
            # 画出点击的位置
            img1 = self.img.copy()
            cv2.circle(img1, point1, 10, (0, 255, 0), 2)
            self.lsPointsChoose.append([x, y])
            self.tpPointsChoose.append((x, y))
            # 将鼠标选的点用直线连起来
            for i in range(len(self.tpPointsChoose) - 1):
                cv2.line(img1, self.tpPointsChoose[i], self.tpPointsChoose[i + 1], (0, 0, 255), 2)
            cv2.imshow(self.mouseWindowName, img1)
            self.checkPointsNum()

def image_transformer(target):
	# 读取原图像
    img_src = imutils.resize(cv2.imread(target), height=720)
    # 调用上述类，获取原图像的像素点
    mouse1 = GetRoiMouse(img_src)
    mouse1.mouseclick()
    # 为方便下一步运算，需要将像素点的类型转换为浮点型数据
    pts_src = np.float32(mouse1.lsPointsChoose)
	# 读取目标图像
    pts_dst = np.float32([[0,0],[0,720],[720,720],[720,0]])
	# 目标图像的尺寸
    dw, dh = 720, 720
    # 通过findHomography计算变换矩阵h
    h, status = cv2.findHomography(pts_src, pts_dst, cv2.RANSAC, 5)
    # 将变换矩阵h带入仿射变换实现矫正
    img_out = cv2.warpPerspective(img_src, h, (dw, dh))
	# 展示结果 图像，拼接起来
    # 窗口显示
    # cv2.imshow('result', img_out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return h, img_out

