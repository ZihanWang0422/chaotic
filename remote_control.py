import os
import time
while 1:
    a=int (input())
    print(a)
    if a==1:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 13 -q")
        # time.sleep(2)
        # os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 25 -q")

    elif a==2:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 25 -q")
    elif a==3:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 27 -q")
    elif a==4:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 26 -q")
    elif a==5:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 12 -q")
    elif a==6:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 14 -q")
    elif a==7:
        os.system("NetAssist.exe -u -rh 192.168.4.1:1122 -d 33 -q")        
    else:
        a=0