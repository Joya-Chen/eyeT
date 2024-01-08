#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include "uploadHandler/uploadutility.h"
#include "frameHandler/frameutility.h"
#include "handler/uploadhandler.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
//#include "python.h"
#include <QByteArray>
#include <QDateTime>
#include <QDir>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QTimer>
#include "dialog.h"
#include "settingform.h"
#define eye_source_xml_addr "haarcascade_eye.xml"
using namespace cv;

class testerData
{
public:
    testerData(){
        initial();
    }

    ~testerData(){

    }

    void initial(){
        m_NameNo.clear();
        m_testerPath.clear();
        m_videoRightFinished = false;
        m_videoLeftFinished = false;
        m_txtRightFinished = false;
        m_txtLeftFinished = false;
    }

    QString m_NameNo;
    QString m_testerPath;
    bool m_videoRightFinished;
    bool m_videoLeftFinished;
    bool m_txtRightFinished;
    bool m_txtLeftFinished;

};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum RESULT {
            DeleteSuccess = 1,
            DeleteFail = 2,
            FileNotExist = 3
        };
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool openCamera(int cameraIndex);
    void detectCamera();
    bool doExVideo(int bitrate_M,QString vPath, QString &oPath);
    QString getVersion();

private:
    Ui::MainWindow *ui;
    Dialog *ui_aboutDialog;
    SettingForm *ui_settingForm;
    QCameraViewfinder *m_viewfindR,*m_viewfindL ;
    QVBoxLayout *m_layoutR;
    VideoCapture cap_Beam_Cam ; //攝影機
    VideoWriter videoOut ;
    Mat mat_original_frame;
    Mat mat_processed_frame;
    QImage img_original;
    QImage img_processed;
    std::vector<Vec3f> vec_circles;
    std::vector<Vec3f>::iterator itr_circles;
    std::vector<Rect> eye_rects;
    QTimer *m_timer,*m_countdownTimer;
    QTimer *m_timer_cam_r, *m_timer_cam_l;
    QList<QString> m_CameraList;
    QString m_todayFolder ;
    QString m_testerNo;
    testerData m_testerData;
    uploadUtility m_upload;
    QThread m_uploadT;
    uploadThread *m_uploadThread;
    frameUtility m_videoUti ;
    int index_Cam_R=-1,index_Cam_L=-1;

    bool recordingType ;
    int m_camera_count ;
    int m_countdown;

    int detectCameraCount();
    const int recordTime = 30;
    QString m_version ;

    void loadConfigAndSet();
    void initialElementState();
    void setConfig();
    void startToSaveVideo();
    void disableAllBtn();
    void enableAllBtn();
    void startUploadThread();
    void showInfo(QString title, QString text);
    void initial_Tester_btnStats();

    int deleteFile(QString filePath);
    void updateBitrate(int bitrate_M,QString vPath, QString &oPath);
signals:
    void uploadVideoFile(QString vPath, QString oPath);

public slots:

    void processFrameAndUpdateGUI();
    void saveVideoEnd();
    void saveRVideoEnd();
    void saveLVideoEnd();
    void setCountdownText();
    void uploadDone();
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void updateSettingParam(QString url, QString pwd, QString dataInfo, int timeout);
private slots:
    void on_comboBox_camList_currentIndexChanged(int index);
    void on_btnCameraStart_clicked();
    void on_btnCameraStop_clicked();
    void on_btnRefresh_clicked();
    void on_btnOpenFolder_clicked();
    void on_btnBuildTester_clicked();
    void on_btnCameraStart_r_clicked();
    void on_btnCameraStart_l_clicked();
    void on_btnVideoSelUpload_clicked();
    void on_btnVideoSetting_clicked();
    void on_btnVideoSeltoNolight_clicked();
    void on_btnVideoSeltoCanny_clicked();
    void on_btnEditCamName_clicked();
    void on_btn_cancelWriteVideo_clicked();
    void on_btn_tester_finish_clicked();
    void on_action_about_triggered();
    void on_action_upload_set_triggered();
};

#endif // MAINWINDOW_H
