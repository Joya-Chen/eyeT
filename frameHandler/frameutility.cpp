#include "frameutility.h"
#include <QDateTime>
#include <QDir>
frameUtility::frameUtility()
{
    m_record = false ;
}

void frameUtility::readVideo(QString path)
{
    VideoCapture cap = VideoCapture("");


    return ;
}

bool frameUtility::openCamera(VideoCapture *cap_cam,int cameraIndex)
{
    cap_cam->open(cameraIndex,CAP_ANY);

    this->cam_setting(cap_cam, m_cam_width, m_cam_height);

    if(cap_cam->isOpened() == false){

        qDebug()<<"error : camera can't access.";

        return false;
    }
    else {
        /*
        //處理 opencv while 讀取frame ->to thread
        VideoWriter video_out;
        this->video_out_setting(video_out);

        while (true) {
                cv::Mat frame;
                cap_cam->read(frame);

                //cv::imshow("Camera", frame);

                video_out.write(frame);

                if (cv::waitKey(1) == 'q') {
                            break;
                 }
        }
        video_out.release();*/
    }
}

void frameUtility::startCapture()
{

}

void frameUtility::run()
{

}

void frameUtility::get_cam_original_setting(VideoCapture *cap_cam)
{
    m_cam_width = cap_cam->get(CAP_PROP_FRAME_WIDTH);
    m_cam_height =  cap_cam->get(CAP_PROP_FRAME_HEIGHT);
    m_fps = 30.0;//cap_cam->get(CAP_PROP_FPS);
    int read_expose_value = cap_cam->get(CAP_PROP_EXPOSURE);

    qDebug()<<"Get cam original setting:"<<"m_cam_width:"<<m_cam_width<<", m_cam_height:"<<m_cam_height<<", m_fps:"<<m_fps<<", read_expose_value:"<<read_expose_value;


    return;
}

void frameUtility::cam_setting(VideoCapture *cap_cam, int width,int height)
{

    cap_cam->set(CAP_PROP_FRAME_HEIGHT,height);
    cap_cam->set(CAP_PROP_FRAME_WIDTH,width);
    if(m_expose_value == 1)
        cap_cam->set(CAP_PROP_AUTO_EXPOSURE,m_expose_value);
    else
        {
            cap_cam->set(CAP_PROP_AUTO_EXPOSURE, 0);  // 關閉自動曝光
            cap_cam->set(CAP_PROP_EXPOSURE,m_expose_value);
        }
    cap_cam->set(CAP_PROP_FPS,30.0);



    qDebug()<<"frameUtility::cam_setting:"<<"CAP_PROP_EXPOSURE:"<<m_expose_value;
}

void frameUtility::video_out_setting(VideoWriter &video_out)
{
    int fourcc ;
    if(m_format == "avi")
        fourcc = VideoWriter::fourcc('M','J','P','G');// 設定影片的格式為 MJPG
    else
        fourcc = VideoWriter::fourcc('M','P','4','V');

    Size frameSize(m_cam_width, m_cam_height);

    double fps = 30.0;

    QString foler = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    QString name = QDateTime::currentDateTime().toString("hh-mm-ss");

    QDir dir;

    if (dir.mkdir(foler)) { //建立mydir資料夾

    }

    QString filename = QString("%1/%2/%3.%4").arg(dir.currentPath()).arg(foler).arg(name).arg(m_format) ;

    video_out = VideoWriter(filename.toStdString(), fourcc, fps, frameSize, true) ; // 產生空的影片

    m_record = true;

}

void frameUtility::Video_illuminationChange(QString srcPath)
{
    Mat img = imread(srcPath.toStdString());
    Mat img_bw, img_thres, img_zero ;
    cvtColor(img, img_bw, COLOR_BGR2GRAY);
    threshold(img_bw,img_thres,180,255,0);
  //  findContours(img_thres.copySize(img_,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
  //  img_zero = Mat::zeros(img.size,CV_32FC1);

}
void frameUtility::eyeAlign(QString srcPath)
{
    Mat frame = imread(srcPath.toStdString());
    if(frame.empty()){
        qDebug()<<"cant load image";
    }
    qDebug()<<"frame depth:"<<frame.depth()<<",channal:"<<frame.channels();

    Mat frame_gray,frame_gaussian, frame_canny, frame_edges, frame_cut;

    cvtColor(frame,frame_gray,COLOR_BGR2GRAY);

    GaussianBlur(frame,frame_gaussian,Size(3,3),0);

    Canny(frame_canny,frame_edges,10,200);

    imshow("frame",frame);
    imshow("frame_gray",frame_gray);
    imshow("frame_gaussian",frame_gaussian);
    imshow("frame_edges",frame_edges);

    waitKey(0);
    destroyAllWindows();


}

void frameUtility::setWidth(int w)
{
    m_cam_width = w;
}

void frameUtility::setHeight(int h)
{
    m_cam_height = h;
}

void frameUtility::setFPS(double fps)
{
    m_fps = fps;
}

void frameUtility::setExpose(int expose)
{
    m_expose_value = expose;
}

int frameUtility::getWidth()
{
    return m_cam_width;
}

int frameUtility::getHeight()
{
    return m_cam_height;
}

double frameUtility::getFPS()
{
     return m_fps;
}

int frameUtility::getExpose()
{
    return m_expose_value;
}
