#ifndef FRAMEUTILITY_H
#define FRAMEUTILITY_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <QString>
#include <QDebug>
#include <QThread>

using namespace cv;

class frameUtility : public QThread
{
public:
    frameUtility();
    bool openCamera(VideoCapture *cap_cam, int cameraIndex);
    void startCapture();
    void run();
    void get_cam_original_setting(VideoCapture *cap_cam);
    void cam_setting(VideoCapture *cap_cam, int width,int height);
    void video_out_setting(VideoWriter &video_out);
    void Video_illuminationChange(QString srcPath);
    void eyeAlign(QString srcPath);

    void setWidth(int w);
    void setHeight(int h);
    void setFPS(double fps);
    void setExpose(int expose);

    int getWidth();
    int getHeight();
    double getFPS();
    int getExpose();



private:
    void readVideo(QString path);
    void resize(int w, int h, Mat &frame);
    bool frameQualified(Mat &frame);
    void removeHighlight(Mat &frame);
    void eyeAlignment(Mat &frame);
    void saveVideo(QString path);


    int m_cam_width ;
    int m_cam_height;
    double m_fps;
    QString m_videoPath;
    int m_fourcc;
    bool m_record;
    QString m_format;
    int m_expose_value;
    int m_biterate;
};

#endif // FRAMEUTILITY_H
