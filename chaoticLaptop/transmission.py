import os

def right_micro():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 14 -q')
    print('right_micro')

def left_micro():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 12 -q')
    print('left_micro')

def right_90():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 26 -q')
    print('right_90')

def left_90():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 27 -q')
    print('left_90')

def fetch():
    stop()
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 33 -q')
    print('fetch')

def front():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 13 -q')
    print('front')

def stop():
    os.system('NetAssist.exe -u -rh 192.168.4.1:1122 -d 25 -q')
    print('stop')