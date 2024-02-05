#!/usr/bin/env python
# -*- coding: utf-8 -*-
# import所需
import cv2
import numpy as np
import os
import sys


# 計算兩張圖片MSE
def mse(img1, img2):
   h, w = img1.shape
   diff = cv2.subtract(img1, img2)
   err = np.sum(diff**2)
   mse = err/(float(h*w))
   return mse, diff

def secondAdjust(srcPath,format):
    #print("format:",format)
    file_path = srcPath
    dir_name = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)

    remove_blink_path = f'{dir_name}\\2th{file_name}'
    #blink_path = f'{dir_name}\\2th_blink_{file_name}'
    #print('srcPath:',srcPath)
    #print('remove_blink_path:', remove_blink_path)
    #print('blink_path:', blink_path)

    cap = cv2.VideoCapture(srcPath)

    if format == "avi" :
        foucc = cv2.VideoWriter_fourcc('M','J','P','G')
    else :
        foucc = cv2.VideoWriter_fourcc('m','p','4','v')


    out2 = cv2.VideoWriter(remove_blink_path, foucc, 30.0,  (400,480))
    #outb2 = cv2.VideoWriter(blink_path, foucc, 30.0,  (400,480))

    ret, bg2 = cap.read()
    bg_gray2 = cv2.cvtColor(bg2, cv2.COLOR_BGR2GRAY)
    error_last2 = 0 
    fist_cal2 = False

    while True:
        ret, frame = cap.read()
        if not ret:
            #print("Cannot receive frame")
            break
        frame_gray =cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 計算2圖片之間的MSE誤差
        error_now, diff1 = mse(bg_gray2, frame_gray)
        if fist_cal2 == False:
            error_last2 = error_now
            fist_cal2 = True
    
        diff = abs(error_now - error_last2)

        # 输出MSE誤差值
       
        if diff < 5 :
            #print("second Adjust:Image matching Error between the two images:",int(error_now),"write")
            out2.write(frame)
        #else :
            #print("second Adjust:Image matching Error between the two images:",int(error_now),"blink write")
            #outb2.write(frame)

    
        if error_now < 30 :
            error_last2 = error_now
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return remove_blink_path


def adjust(srcPath,eyeSide,format):

    file_path = srcPath
    dir_name = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)

    remove_blink_path = f'{dir_name}\\remove_blink_{file_name}'
    blink_path = f'{dir_name}\\blink_{file_name}'

    #print('Directory:', dir_name)
    #print('Filename:', file_name)

    cap = cv2.VideoCapture(srcPath)

    if format == "avi" :
        foucc = cv2.VideoWriter_fourcc('M','J','P','G')
    else :
        foucc = cv2.VideoWriter_fourcc('m','p','4','v')

    width = 400
    height = 480

    if eyeSide=="left" :
        w1 = 50
        w2 = 450
    else :
        w1 = 190
        w2 = 590

    out = cv2.VideoWriter(remove_blink_path, foucc, 30.0, (width,height))
    outb = cv2.VideoWriter(blink_path, foucc, 30.0, (width,height))

    ret, bg = cap.read()
    bg = bg[0:height,w1:w2]
    bg_gray = cv2.cvtColor(bg, cv2.COLOR_BGR2GRAY)
    error_last = 0
    fist_cal = False

    while True:
        ret, frame = cap.read()
        if not ret:
            #print("Cannot receive frame")
            break
        frame = frame[0:height,w1:w2]
        frame_gray =cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 计算2圖片之间的MSE误差
        error_now, diff1 = mse(bg_gray, frame_gray)
        if fist_cal == False:
            error_last = error_now
            fist_cal = True

        diff = abs(error_now - error_last)

        # 輸出MSE誤差值

        if diff < 10 :
            #print("Image matching Error between the two images:",int(error_now),"write")
            out.write(frame)
        else :
            #print("Image matching Error between the two images:",int(error_now),"blink write")
            outb.write(frame)

        if error_now < 30 :
            error_last = error_now
    cap.release()
    out.release()
    outb.release()
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()
    return print(secondAdjust(remove_blink_path,format))

def main(argv):
    #print(argv[1])
    #print(argv[2])
    #print(argv[3])
    adjust(argv[1],argv[2],argv[3])
 
if __name__ == "__main__":
     main(sys.argv)