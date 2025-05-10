import nxfind as clnf
import transmission as trans
import time

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
for i in range(len(clnf.find_treasure)-1):
    # 计算当前方块和下一个方块的差值
    diff = clnf.find_treasure[i+1] - clnf.find_treasure[i]
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
diff0 = clnf.find_exit[1] - 80
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
for i in range(len(clnf.find_exit)-2):
    # 计算当前方块和下一个方块的差值(从exit路径find_exit[1]开始)
    diff = clnf.find_exit[i+2] - clnf.find_exit[i+1]
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