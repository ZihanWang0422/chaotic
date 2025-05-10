import cv2
import os
import chaoticTestLaptop.semiautomatic as semiautomatic
from chaoticTestLaptop.color_detection import hsv2color
import chaoticTestLaptop.transmission as transmisson
from chaoticTestLaptop.line_trace import travel
import networkx as nx
import pylab 

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
enhanced = cv2.convertScaleAbs(result, alpha=1.5, beta=0)
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
travel(find_exit, result, mat)
transmisson.stop()
print('Success')
