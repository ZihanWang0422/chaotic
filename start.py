import cv2
import os
import chaoticLaptop.semiautomatic as semiautomatic
from chaoticLaptop.color_detection import hsv2color
import chaoticLaptop.transmission as trans
from chaoticLaptop.line_trace import travel
from chaoticLaptop.nxfind import find_least_turn
import networkx as nx
import pylab 
import time

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
        if tiles[up] == 0 or tiles[target] == 0:
            G.add_weighted_edges_from([(target,up,1000)],"weight")
        else:
            G.add_weighted_edges_from([(target,up,1)],"weight")
    if down < 81:
        if tiles[down]==0 or tiles[target] == 0:
            G.add_weighted_edges_from([(target,down,1000)],"weight")
        else:
            G.add_weighted_edges_from([(target,down,1)],"weight")
    if left >= 0 and left // 9 == target // 9:
        if tiles[left]==0 or tiles[target] == 0:
            G.add_weighted_edges_from([(target,left,1000)],"weight")
        else:
            G.add_weighted_edges_from([(target,left,1)],"weight")
    if right < 81 and right % 9 == target % 9:
        if tiles[right]== 0 or tiles[target] == 0:
            G.add_weighted_edges_from([(target,right,1000)],"weight")
        else:
            G.add_weighted_edges_from([(target,right,1)],"weight")
pos = {}
for i in range(0, 81):
    pos[i] = [i%9, 8-i//9]

treasure_paths = [p for p in nx.all_shortest_paths(G, source=start, target=treasure, weight="weight")]
find_treasure=find_least_turn(treasure_paths)
print(find_treasure)
treasure_edge = []
for i in range(len(find_treasure)-1):
    treasure_edge.append((find_treasure[i],find_treasure[i+1]))
exit_paths = [p for p in nx.all_shortest_paths(G, source=treasure, target=destination, weight="weight")]
find_exit=find_least_turn(exit_paths)
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
#travel(find_exit, result, mat)
#transmisson.stop()

#PART 4


def repeat_fun(times, f):
    for i in range(times): f()


#定义车子的位置: 0-80
car_position = 72  #初始位置为72

#定义车子车头当前的方位：
#r 表示车头向右
#l 表示车头向左
#u 表示车头向上
#d 表示车头向下
car_direction = 'r'  #初始时车子在起点的车头方位是向右

#起点到宝藏区的循迹
for i in range(len(find_treasure)-1):
    # 计算当前方块和下一个方块的差值
    diff = find_treasure[i+1] - find_treasure[i]
    if diff == 1:  # 下一个方块在右边
        if car_direction == "r":
            trans.front()
            time.sleep(2)
        elif car_direction == "u":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "r"
        elif car_direction == "d":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "r"
        car_position += 1
    elif diff == -1:  # 下一个方块在左边
        if car_direction == "l":
            trans.front()
            time.sleep(2)
        elif car_direction == "u":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
        elif car_direction == "d":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
        car_position -= 1
    elif diff == 9:  # 下一个方块在下面
        if car_direction == "d":
            trans.front()
            time.sleep(2)
        elif car_direction == "l":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "d"
        elif car_direction == "r":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "d"
        car_position += 9
    elif diff == -9:  # 下一个方块在上面
        if car_direction == "u":
            trans.front()
            time.sleep(2)
        elif car_direction == "l":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
        elif car_direction == "r":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
        car_position -= 9
    else:
        print("错误：下一个方块与当前方块不相邻")
        break

#特判从宝藏区到下一个格子(考虑到会有180度转弯)
diff0 = find_exit[1] - 80
if diff0 == -1:  #下一个格子在宝藏区左边
    trans.fetch()
    time.sleep(6)
    if car_direction == "d":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
    elif car_direction == "r":
            for i in range(2) :
                trans.right_90()
                time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
    car_position -= 1

elif diff0 == -9:  #下一个格子在宝藏区上面
    trans.fetch()
    time.sleep(6)
    if car_direction == "r":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
    elif car_direction == "d":
            for i in range(2) :
                trans.right_90()
                time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
    car_position -= 9
    


#宝藏区到终点的循迹
for i in range(len(find_exit)-2):
    # 计算当前方块和下一个方块的差值(从exit路径find_exit[1]开始)
    diff = find_exit[i+2] - find_exit[i+1]
    if diff == 1:  # 下一个方块在右边
        if car_direction == "r":
            trans.front()
            time.sleep(2)
        elif car_direction == "u":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "r"
        elif car_direction == "d":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "r"
        car_position += 1
    elif diff == -1:  # 下一个方块在左边
        if car_direction == "l":
            trans.front()
            time.sleep(2)
        elif car_direction == "u":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
        elif car_direction == "d":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "l"
        car_position -= 1
    elif diff == 9:  # 下一个方块在下面
        if car_direction == "d":
            trans.front()
            time.sleep(2)
        elif car_direction == "l":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "d"
        elif car_direction == "r":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "d"
        car_position += 9
    elif diff == -9:  # 下一个方块在上面
        if car_direction == "u":
            trans.front()
            time.sleep(2)
        elif car_direction == "l":
            trans.right_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
        elif car_direction == "r":
            trans.left_90()
            time.sleep(5)
            trans.front()
            time.sleep(2)
            car_direction = "u"
        car_position -= 9
    else:
        print("错误：下一个方块与当前方块不相邻")
        break