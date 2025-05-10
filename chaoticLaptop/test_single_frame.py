import cv2
import imutils
import numpy as np
single = imutils.resize(cv2.imread('image.jpg'), height=720)
#cv2.imshow('test', single)
mat =np.matrix( [[ 1.99688870e+00  ,1.16891046e+00 ,-8.63581307e+02],
 [ 2.33186616e-01 , 4.17616031e+00 ,-6.90635161e+02],
 [ 2.72782543e-04,  2.91741348e-03  ,1.00000000e+00]])
adjusted = cv2.warpPerspective(single, mat, (720, 720)) 
cv2.imshow('test', adjusted)
cv2.waitKey(0)