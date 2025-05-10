import chaoticLaptop.transmission as transmission
import chaoticLaptop.chaotic_locate as chaotic_locate
import cv2
import imutils
import time

right = 0
left = 1
down = 2
up = 3

eps = 8


def get_coordinates(path):
    # with open(path, 'r') as f:
    #     knot_archived = [int(x) for x in (f.readline().split())]
    knot_archived = path
    return [(a//9*80+40, a % 9*80+40) for a in knot_archived]


def get_direction(src, dst):
    if src[1] == dst[1]:
        if src[0] < dst[0]:
            return right
        else:
            return left
    if src[0] == dst[0]:
        if src[1] < dst[1]:
            return left
        else:
            return up


def single_line_trace(src, dst, init, direction, matrix):
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    transmission.front()
    arrived = 0
    print(direction)
    while (True):
        # first_flag = 1
        ret1, curr_raw = cap.read()
        curr_half = imutils.resize(curr_raw, height=720)
        curr = cv2.warpPerspective(curr_half, matrix, (720, 720)) 
        # curr =  cv2.convertScaleAbs(curr_half, alpha=1.5, beta=0)
        # curr = curr_half
        cv2.imshow("test", curr)
        if cv2.waitKey(1) and arrived:
            break
        ssim, vertices = chaotic_locate.shrink_the_range(init, curr)
        if ssim < 0.95:
            print(vertices)
            mid = ((vertices[0][0]+vertices[2][0])/2,
                   (vertices[0][1]+vertices[2][1])/2)
        #    if first_flag == 0:
        #        if abs(premid[0]-mid[0]) > 2*eps or abs(premid[1]-mid[1]) > 2*eps:
        #            continue
            premid = mid
            print(mid)
        #    if first_flag == 1:
        #        first_flag = 0
            if direction == right:
                if abs(mid[0] - dst[0]) < eps:
                    arrived = 1
                if src[1] - mid[1] > eps:
                    transmission.right_micro()
                    transmission.front()
                elif mid[1] - src[1] > eps:
                    transmission.left_micro()
                    transmission.front()
            elif direction == left:
                if abs(mid[0] - dst[0]) < eps:
                    arrived = 1
                if src[1] - mid[1] > eps:
                    transmission.left_micro()
                    transmission.front()
                elif mid[1] - src[1] > eps:
                    transmission.right_micro()
                    transmission.front()
            elif direction == up:
                if abs(mid[1] - dst[1]) < eps:
                    arrived = 1
                if src[0] - mid[0] > eps:
                    transmission.left_micro()
                    transmission.front()
                elif mid[0] - src[0] > eps:
                    transmission.right_micro()
                    transmission.front()
            elif direction == down:
                if abs(mid[1] - dst[1]) < eps:
                    arrived = 1
                if src[0] - mid[0] > eps:
                    transmission.right_micro()
                    transmission.front()
                elif mid[0] - src[0] > eps:
                    transmission.left_micro()
                    transmission.front()
    cap.release()
    cv2.destroyAllWindows()


def travel(path, field, matrix):
    knot_coordinates = get_coordinates(path)
    print(knot_coordinates)
    l_path = len(knot_coordinates) - 1
    prev_dir = get_direction(knot_coordinates[0], knot_coordinates[1])
    # single_line_trace(knot_coordinates[0], knot_coordinates[1], 
    #                    field, prev_dir, matrix)
    for i in range(1, l_path):
        curr_dir = get_direction(knot_coordinates[i], knot_coordinates[i+1])
        print(curr_dir)
        if prev_dir == right:
            if curr_dir == up:
                transmission.left_90()
            elif curr_dir == down:
                transmission.right_90()
            elif curr_dir==right:
                transmission.front()
            elif curr_dir==left:
                transmission.left_90()
                transmission.stop()
                transmission.left_90()
                transmission.stop()
        if prev_dir == left:
            if curr_dir == up:
                transmission.right_90()
            elif curr_dir == down:
                transmission.left_90()
            elif curr_dir==left:
                transmission.front()
            elif curr_dir==right:
                transmission.left_90()
                transmission.stop()
                transmission.left_90()
                transmission.stop()
        if prev_dir == up:
            if curr_dir == right:
                transmission.right_90()
            elif curr_dir == left:
                transmission.left_90()
            elif curr_dir==up:
                transmission.front()
            elif curr_dir==down:
                transmission.left_90()
                transmission.stop()
                transmission.left_90()
                transmission.stop()
        if prev_dir == down:
            if curr_dir == left:
                transmission.right_90()
            elif curr_dir == right:
                transmission.left_90()
            elif curr_dir==down:
                transmission.front()
            elif curr_dir==up:
                transmission.left_90()
                transmission.stop()
                transmission.left_90()
                transmission.stop()                
        time.sleep(2)
        # single_line_trace(knot_coordinates[i], knot_coordinates[i+1], 
        #                   field, curr_dir,matrix)
        prev_dir = curr_dir
