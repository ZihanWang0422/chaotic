import cv2
import os
import numpy as np
import semiautomatic

picture_path = 'image.jpg'
result = semiautomatic.image_transformer(picture_path)
enhanced = cv2.convertScaleAbs(result, alpha=1.5, beta=0)
cv2.imwrite('enhanced.png', enhanced)
