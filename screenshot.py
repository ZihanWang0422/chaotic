import cv2
import os
import chaoticLaptop.semiautomatic as semiautomatic
from chaoticLaptop.color_detection import hsv2color
import chaoticLaptop.transmission as transmisson
from chaoticLaptop.line_trace import travel
import networkx as nx
import pylab 
import imutils
import numpy as np

def take_screenshot(matrix):
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    cnt = 1
    while (True):
        # first_flag = 1
        ret1, curr_raw = cap.read()
        curr_half = imutils.resize(curr_raw, height=720)
        curr = cv2.warpPerspective(curr_half, matrix, (720, 720)) 
        # curr =  cv2.convertScaleAbs(curr_half, alpha=1.5, beta=0)
        # curr = curr_half
        cv2.imshow("test", curr)
        filename = '/chaoticCascade/posi/vehicle' + str(cnt) + '.jpg'
        cv2.imwrite(filename, curr)
        if cv2.waitKey(1) & 0xff == ord('s'):
            break
        # ssim, vertices = chaotic_locate.shrink_the_range(init, curr)
        # if ssim < 0.95:
        #     print(vertices)
        #     mid = ((vertices[0][0]+vertices[2][0])/2,
        #            (vertices[0][1]+vertices[2][1])/2)
        # #    if first_flag == 0:
        # #        if abs(premid[0]-mid[0]) > 2*eps or abs(premid[1]-mid[1]) > 2*eps:
        # #            continue
        #     premid = mid
        #     print(mid)
        # #    if first_flag == 1:
        # #        first_flag = 0
        #     if direction == right:
        #         if abs(mid[0] - dst[0]) < eps:
        #             arrived = 1
        #         if src[1] - mid[1] > eps:
        #             transmission.right_micro()
        #             transmission.front()
        #         elif mid[1] - src[1] > eps:
        #             transmission.left_micro()
        #             transmission.front()
        #     elif direction == left:
        #         if abs(mid[0] - dst[0]) < eps:
        #             arrived = 1
        #         if src[1] - mid[1] > eps:
        #             transmission.left_micro()
        #             transmission.front()
        #         elif mid[1] - src[1] > eps:
        #             transmission.right_micro()
        #             transmission.front()
        #     elif direction == up:
        #         if abs(mid[1] - dst[1]) < eps:
        #             arrived = 1
        #         if src[0] - mid[0] > eps:
        #             transmission.left_micro()
        #             transmission.front()
        #         elif mid[0] - src[0] > eps:
        #             transmission.right_micro()
        #             transmission.front()
        #     elif direction == down:
        #         if abs(mid[1] - dst[1]) < eps:
        #             arrived = 1
        #         if src[0] - mid[0] > eps:
        #             transmission.right_micro()
        #             transmission.front()
        #         elif mid[0] - src[0] > eps:
        #             transmission.left_micro()
        #             transmission.front()
    cap.release()
    cv2.destroyAllWindows()


############# for debugging ##################
###### might comment out during contest ######
print("If you are debugging and do not want to take another picture, enter 0.")
print("Enter 1 for complete process.")
debug_flag = int(input())
##############################################

picture_path = 'image.jpg'


# Part I
# take the correct picture
if debug_flag:
    cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)
    while (True):
        # 一帧一帧捕捉
        ret, frame = cap.read()
        # 我们对帧的操作在这里
        # 显示返回的每帧
        cv2.imshow("Press 's' to save the current picture", frame)
        if cv2.waitKey(1) & 0xff == ord('s'):
            cv2.imwrite(picture_path, frame)
            break
    # 当所有事完成，释放 VideoCapture 对象
    cap.release()
    cv2.destroyAllWindows()


# Part II
# Analyze the Picture
print('Select the border vertices.')
mat, result = semiautomatic.image_transformer(picture_path)
print(mat)
cv2.imwrite('result.png', result)
print('Enhancing Picture, this might take a long time...')
enhanced = cv2.convertScaleAbs(result, alpha=2, beta=0)
cv2.imwrite('enhanced.png', enhanced)
hsv = cv2.cvtColor(enhanced, cv2.COLOR_BGR2HSV)
print('Converting Picture to Text...')
i = j = 40
# mat = []
# with open('field.txt', 'w') as output:
#     while i < 720:
#         #        row = []
#         while j < 720:
#             #            row.append(hsv2color(hsv[i, j]))
#             output.write(str(hsv2color(hsv[i, j])))
#             j += 80
# #        mat.append(row)
#         j = 40
#         i += 80
#    print(mat)
# 原理：在每个方格中心取样本点考虑颜色。
# 后期如果需要的话可能考虑对于某个方格多取几个采样点
tiles = []
while i < 720:
    #        row = []
    while j < 720:
        tiles.append(hsv2color(hsv[i, j]))
        #   output.write(str(hsv2color(hsv[i, j])))
        j += 80
#        mat.append(row)
    j = 40
    i += 80
tiles[80]=2 # blue
tiles[6]=3 # green
tiles[72]=4 # yellow
# Part III
# launch the Dijkstra and Transmission
print('Dijkstra Running...')
colors = ['black','white','blue','green','yellow']
# with open('field.txt', "r") as f:
#     tiles = f.readline()

G = nx.Graph()
for i in range(0, 81):
    G.add_node(i, desc =str(i))
for target in range(0, 81):
    up = target - 9;
    down = target + 9;
    left = target - 1;
    right = target + 1;
    if tiles[target] == 4:
        start = target
    if tiles[target] == 2:
        treasure = target
    if tiles[target] == 3:
        destination = target    
    if up >= 0:
        if tiles[up] == 0:
            G.add_weighted_edges_from([(target,up,1000)])
        else:
            G.add_weighted_edges_from([(target,up,1)])
    if down < 81:
        if tiles[down]==0:
            G.add_weighted_edges_from([(target,down,1000)])
        else:
            G.add_weighted_edges_from([(target,down,1)])
    if left >= 0 and left // 9 == target // 9:
        if tiles[left]==0:
            G.add_weighted_edges_from([(target,left,1000)])
        else:
            G.add_weighted_edges_from([(target,left,1)])
    if right < 81 and right % 9 == target % 9:
        if tiles[up]==0:
            G.add_weighted_edges_from([(target,right,1000)])
        else:
            G.add_weighted_edges_from([(target,right,1)])
pos=nx.shell_layout(G)
pos = {}
for i in range(0, 81):
    pos[i] = [i%9, 8-i//9]

find_treasure=nx.dijkstra_path(G,source=start,target=treasure)
print(find_treasure)
treasure_edge = []
for i in range(len(find_treasure)-1):
    treasure_edge.append((find_treasure[i],find_treasure[i+1]))
find_exit=nx.dijkstra_path(G,source=treasure,target=destination)
exit_edge = []
for i in range(len(find_exit)-1):
    exit_edge.append((find_exit[i],find_exit[i+1]))
print(find_exit)
nx.draw_networkx_nodes(G,pos,node_size = 50,node_color = [colors[n] for n in tiles])
nx.draw_networkx_labels(G,pos,labels = nx.get_node_attributes(G, 'desc'))
nx.draw_networkx_edges(G,pos,edgelist = treasure_edge, width = 5, edge_color = 'red', alpha = 0.25)
nx.draw_networkx_edges(G,pos,edgelist = exit_edge, width = 5, edge_color = 'red', alpha = 0.25)
pylab.title('Field',fontsize=15)
pylab.show()
print('Enter Any Key Once Ready')
input()
# travel(find_treasure, result, mat)
# transmisson.fetch()

# take_screenshot(mat)

font = cv2.FONT_HERSHEY_SIMPLEX
 
lower_red = np.array([0, 127, 128])  # 红色低阈值
upper_red = np.array([10, 255, 255])  # 红色高阈值
 
cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)  # 打开USB摄像头
if (cap.isOpened()):  # 视频打开成功
    flag = 1
else:
    flag = 0
num = 0
if (flag):
    while (True):
        ret, curr_raw = cap.read()  # 读取一帧
        if ret == False:  # 读取帧失败
            break
        curr_half = imutils.resize(curr_raw, height=720)
        frame = cv2.warpPerspective(curr_half, mat, (720, 720)) 
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
#transmisson.stop()
print('Success')
