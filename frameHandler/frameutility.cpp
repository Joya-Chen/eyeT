#include "frameutility.h"

frameUtility::frameUtility()
{

}

void frameUtility::readVideo(QString path)
{
    VideoCapture cap = VideoCapture("");


    return ;
}

void frameUtility::get_cam_original_setting(VideoCapture *cap_cam)
{
    qDebug()<<"weith:"<<cap_cam->get(3);
    qDebug()<<"height:"<<cap_cam->get(4);
    qDebug()<<"fps:"<<cap_cam->get(5);
    qDebug()<< "fourcc" << cap_cam->get(CAP_PROP_FOURCC);
    qDebug()<<"total fps:"<<cap_cam->get(7);
    qDebug()<<"obj format:"<<cap_cam->get(8);
    qDebug()<<"isToRGB:"<<cap_cam->get(16);
    return;
}

void frameUtility::cam_setting(VideoCapture *cap_cam, int width,int height)
{
    cap_cam->set(CAP_PROP_FOURCC,VideoWriter::fourcc('M','J','P','G'));
    cap_cam->set(3,height);
    cap_cam->set(4,width);
}

void frameUtility::video_out_setting()
{

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
