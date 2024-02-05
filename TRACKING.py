import cv2
import numpy as np
import os
import sys

def spilitVideoOverlap(srcPath, format,segmentStartIndex,segmentEndIndex):
    # 打開影片檔案
    file_path = srcPath
    cap = cv2.VideoCapture(file_path)
    
    dir_name = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)

    # 獲取影片的基本信息
    fps = cap.get(cv2.CAP_PROP_FPS)
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    #foucc = cap.get(cv2.CAP_PROP_FOURCC)

    if format == "avi" :
        foucc = cv2.VideoWriter_fourcc('M','J','P','G')
    else :
        foucc = cv2.VideoWriter_fourcc('m','p','4','v')

    # 創建一個VideoWriter對象及紀錄segment陣列
    ssegmentMode1_list = []

    # 使用迴圈來生成數字遞增序列
    for i in range(28):
        ssegmentMode1_list.append([i, i+3])


    #f"output_{n}.{i}

    frameIndex = 0
    interval = 3
    framepersec = 30
    preVideoInx = 0
    videoIndex = 0
    intervalIndex = 0
    frameRate = interval * framepersec
    startFrame = segmentStartIndex * framepersec
    endFrame = segmentEndIndex * framepersec
    file_count = 0
    #cv2.VideoWriter_fourcc(*'mp4v')

    spilit_out = f'{dir_name}\\overlap_{segmentStartIndex}_{file_name}'
    out = cv2.VideoWriter(spilit_out, foucc, fps, (width,height))
    while True:
        ret,roi = cap.read()
        if ret is False:
            break
        if frameIndex >= endFrame :
            #print("frameIndex >= endFrame ;break;")
            break

        frameIndex +=1
        
        if frameIndex >= startFrame and frameIndex <= endFrame:
            #print(frameIndex)
            out.write(roi)

    out.release()
    cv2.destroyAllWindows()

def splitVideo(srcPath, format):    
    file_path = srcPath
    cap = cv2.VideoCapture(file_path)
    
    dir_name = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)

    # 獲取影片的基本信息
    fps = cap.get(cv2.CAP_PROP_FPS)
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    print("spilt width:",width,"height",height)
    #foucc = cap.get(cv2.CAP_PROP_FOURCC)

    if format == "avi" :
        foucc = cv2.VideoWriter_fourcc('M','J','P','G')
    else :
        foucc = cv2.VideoWriter_fourcc('m','p','4','v')

    # 創建一個VideoWriter對象及紀錄segment陣列
    ssegmentMode1_list = []

    # 使用迴圈來生成數字遞增序列
    for i in range(28):
        ssegmentMode1_list.append([i, i+3])

    #f"output_{n}.{i}

    frameIndex = 0
    interval = 3
    framepersec = 30
    preVideoInx = 0
    videoIndex = 0
    intervalIndex = 0
    frameRate = interval * framepersec
    file_count = 0
    #cv2.VideoWriter_fourcc(*'mp4v')
    spilit_out = f'{dir_name}\\{videoIndex}_{file_name}'
    out = cv2.VideoWriter(f'{dir_name}\\{videoIndex}_{file_name}', foucc, fps, (width,height))
    
    while True:
        #print("frameIndex=",frameIndex)
        ret,roi = cap.read()
        if ret is False:
            break
         
        frameIndex +=1
        videoIndex = frameIndex//frameRate
        #print(frameIndex,videoIndex)
    
        if videoIndex != preVideoInx :
            #print("create a new one video",videoIndex ,"!=", preVideoInx)
            out = cv2.VideoWriter(f'{dir_name}\\{videoIndex}_{file_name}', foucc, fps, (width,height))
            preVideoInx = videoIndex
        else:
            preVideoInx = videoIndex

        out.write(roi)
           
        key = cv2.waitKey(30)
        if key == 27:
            break
    cv2.destroyAllWindows()

def roi_Create(image):
    # 讀取原始圖片
    
    input_image = image
    # 獲取原始圖片的尺寸# Read the input image
    height, width, _ = input_image.shape
    #print("width:",width,"height:",height)

    
    w_multi = 300//width
    h_multi = 300//height
    #print("寬要拼接 次 w_multi:",w_multi+1,"高h_multi:",h_multi+1)
    
    newImg_width = width*(w_multi+1)
    newImg_height = height*(h_multi+1)
   

    # 添加座標到陣列中
    # 創建一個空的陣列來存放coordinates值
    coordinates_array = []

    # 將coordinates值存入陣列
    for i in range(h_multi+1):
        for j in range(w_multi+1):
            coordinates_array.append((j*width, i*height))        

    
    # Create a blank image larger than 300x300
    larger_image = 255 * np.ones((newImg_height,newImg_width , 3), dtype=np.uint8)
    for coordinate in coordinates_array:
        x = coordinate[0]
        y = coordinate[1]
        larger_image[y:y+height, x:x+width] = input_image

    return larger_image[0:300,0:300]
    
def trackingROI(srcPath,eyeSide,format,AUTO=True):
    tracker = cv2.TrackerCSRT_create()  # 創建追蹤器
    tracking = False                    # 設定 False 表示尚未開始追蹤

    #print("format:",format)
    file_path = srcPath
    dir_name = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)

    roi_path = f'{dir_name}\\ROI_{file_name}'
    roi_crop_path = f'{dir_name}\\ROI_crop_{file_name}'

    if format == "avi" :
        foucc = cv2.VideoWriter_fourcc('M','J','P','G')
    else :
        foucc = cv2.VideoWriter_fourcc('m','p','4','v')

    cap = cv2.VideoCapture(file_path)
    fps = cap.get(cv2.CAP_PROP_FPS)
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    frameIndex = 0
    interval = 3
    framepersec = 30
    preVideoInx = 0
    videoIndex = 0
    intervalIndex = 0
    frameRate = interval * framepersec
    file_count = 0
    #cv2.VideoWriter_fourcc(*'mp4v')
    out = cv2.VideoWriter(roi_path, foucc, fps, (width,height))
    out_ROI = cv2.VideoWriter(roi_crop_path, foucc, fps, (300,300))
    if  AUTO :
        if eyeSide == "left" :
            area = (162,207,117,97)
        else:
            area = (138,207,117,97)
    
    while True:
        ret, frame = cap.read()
        if not ret:
            #print("Cannot receive frame")
            break

        keyName = cv2.waitKey(1)

        if keyName == ord('q'):
            break
        if tracking == False:
            if AUTO == False:
                area = cv2.selectROI('selectROI', frame, showCrosshair=False, fromCenter=False)
                #print(area[0],area[1],area[2],area[3])
                tracker.init(frame, area)    # 初始化追蹤器
                tracking = True              # 設定可以開始追蹤
            else:
                tracker.init(frame, area)    # 初始化追蹤器
                tracking = True              # 設定可以開始追蹤   
        if tracking:
            success, point = tracker.update(frame)   # 追蹤成功後，不斷回傳左上和右下的座標
            if success:
                p1 = [int(point[0]), int(point[1])]
                p2 = [int(point[0] + point[2]), int(point[1] + point[3])]
                #roi = roi_Create(frame[p1[1]:p2[1], p1[0]:p2[0]])
                roi = roi_Create(frame[p1[1]:p1[1]+100, p1[0]:p1[0]+100])
                cv2.rectangle(frame, p1, p2, (0,0,255), 2)   # 根據座標，繪製四邊形，框住要追蹤的物件
                #cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

                # 擷取矩形框中的像素
                #roi = img[y:y+h, x:x+w]

        cv2.imshow('ROITracking', frame)
        out.write(frame)
        out_ROI.write(roi)
    cap.release()
    cv2.destroyAllWindows()
    
    number_pairs = [(i, i+3) for i in range(28)]
    for pair in number_pairs:
        #print("======new overlap=========")
        #print(pair[0],pair[1]) 
        spilitVideoOverlap(roi_crop_path,format, pair[0],pair[1])
#trackingROI("C:\\DeepObverseCode\\RD_testFolder\\2024-01-30\\yardExposeTest\\2thremove_blink_left.mp4","left","mp4")

def main(argv):
    print(argv[1]) #videopath
    print(argv[2]) #eyeside
    print(argv[3]) #format
    print(argv[4]) #autoTracking default = true
    print(argv[5]) #only Split3 = false 0-3 3-6 6-9
    if argv[5] == "s":
        splitVideo(argv[1],argv[3])
    else:
        if argv[4] == "false":
            trackingROI(argv[1],argv[2],argv[3],False)
        else :
            trackingROI(argv[1],argv[2],argv[3],True)
 
if __name__ == "__main__":
    main(sys.argv)
    #main("C:\\DeepObverseCode\\eyeT\\video\\left1.avi", "left", "avi", "false", "s")
    #splitVideo("C:\\DeepObverseCode\\eyeT\\video\\left1.avi","avi")
    #trackingROI("C:/DeepObverseCode/eyeT/2024-02-04/yard2\\2thremove_blink_right.avi","right","avi",True)