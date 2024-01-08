#ifndef FRAMEUTILITY_H
#define FRAMEUTILITY_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <QString>
#include <QDebug>

using namespace cv;

class frameUtility
{
public:
    frameUtility();
    bool openCamera();
    void startCapture();
    void get_cam_original_setting(VideoCapture *cap_cam);
    void cam_setting(VideoCapture *cap_cam, int width,int height);
    void video_out_setting();
    void Video_illuminationChange(QString srcPath);
    void eyeAlign(QString srcPath);


private:
    void readVideo(QString path);
    void resize(int w, int h, Mat &frame);
    bool frameQualified(Mat &frame);
    void removeHighlight(Mat &frame);
    void eyeAlignment(Mat &frame);
    void saveVideo(QString path);


    int cam_width ;
    int cam_height;
    double fps;
    QString videoPath;
    int fourcc;
};

#endif // FRAMEUTILITY_H
