#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>
#include <QSettings>
#include <QProcess>
#include <QAxObject>
#include <QTranslator>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui_aboutDialog = new Dialog(this);

    ui_settingForm = new SettingForm(this);

    ui_videoParam = new videoParam(this);

    ui_processForm = new processForm(this);

    //ui_processForm->show();

    ui_processForm->hide();

    this->startUploadThread();

    this->loadConfigAndSet();

    this->loadVConfigAndSet();

    m_version = "v2024.04.25.19";

    m_releaseNote = QString::fromUtf8("");

    this->initMenu();

    this->initialElementState();

    recordingType = false;

    m_countdown = recordTime;

    //this->startUploadThread();

    m_todayFolder = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    m_timer = new QTimer(this);

    m_timer_cam_r = new QTimer(this);

    m_timer_cam_l = new QTimer(this);

    m_countdownTimer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));

    connect(m_countdownTimer, SIGNAL(timeout()), this, SLOT(setCountdownText()));

    connect(m_timer_cam_r, SIGNAL(timeout()), this, SLOT(saveRVideoEnd()));

    connect(m_timer_cam_l, SIGNAL(timeout()), this, SLOT(saveLVideoEnd()));

    connect(ui_settingForm,SIGNAL(paramUpdate(QString,QString,QString,int)),this,SLOT(updateSettingParam(QString,QString,QString,int)));

    connect(ui_videoParam,SIGNAL(paramUpdate(QString,int,int)),this,SLOT(updateVideoSettingParam(QString,int,int)));

    this->detectCamera();
}

MainWindow::~MainWindow()
{

    m_uploadThread->deleteLater();


    delete ui;
    delete ui_videoParam;
    delete ui_settingForm;
    delete ui_processForm;
    delete ui_aboutDialog;
    delete m_uploadThread;

}
bool MainWindow::openCamera(int cameraIndex)
{
    cap_Beam_Cam.release();

    cap_Beam_Cam.open(cameraIndex,CAP_ANY);

    m_videoUti.cam_setting(&cap_Beam_Cam,480,640);

    m_videoUti.get_cam_original_setting(&cap_Beam_Cam);

    if(cap_Beam_Cam.isOpened() == false){

        ui->txtShow->appendPlainText("error : camera can't access.");

        return false;
    }

    m_timer->start(10);

    return true;

}
int MainWindow::detectCameraCount(){

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        qDebug()<<"CameraInfo:\n,description:"<<cameraInfo.description();

        m_CameraList.append(cameraInfo.description());

        m_camera_count ++ ;
    }

    return m_camera_count;

}

void MainWindow::detectCamera()
{
    m_camera_count = 0 ;

    m_CameraList.clear();

    ui->comboBox_camList->clear();

    if(this->detectCameraCount()!=0){

        for(int i = 0 ; i < m_CameraList.size() ; i++ ){
            ui->comboBox_camList->addItem(QString("%1.%2").arg(i+1).arg(m_CameraList.at(i)));
        }
    }
    else{
        ui->txtShow->appendPlainText("error: no camera detected.Please press refresh button.");

        return ;
    }

    return ;

}

bool MainWindow::doExVideo(int bitrate_M,QString vPath, QString &oPath)
{
    int result = this->deleteFile(oPath);

    if(result == RESULT::DeleteFail)
    {

    }
    else if(result == RESULT::FileNotExist)
    {

    }

    this->updateBitrate(bitrate_M, vPath, oPath);

    return true;
}

QString MainWindow::getVersion()
{
    QString returnNote = QString("%1%2").arg(m_version).arg(m_releaseNote);
    return returnNote;
}

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type())
        {
           case QEvent::LanguageChange:
                qDebug()<<"MainWindow::LanguageChange";
                //還有其他手工更新界面的內容
            break;
           default:
            break;
        }
}

void MainWindow::processFrameAndUpdateGUI()
{
    cap_Beam_Cam.read(mat_original_frame);


    if(mat_original_frame.empty() == true)  return;

    if(recordingType)
    {

        videoOut.write(mat_original_frame);
    }

    QImage qimg_original(mat_original_frame.data,mat_original_frame.cols,mat_original_frame.rows,mat_original_frame.step,QImage::Format_RGB888);

    ui->right_label->setPixmap(QPixmap::fromImage(qimg_original.rgbSwapped()));


}
void MainWindow::saveVideoEnd(){
    recordingType = false;

    videoOut.release();

    QMessageBox::information(this,tr("Info"),tr("影片擷取結束"),QMessageBox::Ok);

    ui->btnCameraStart->setText(tr("開始擷取影像"));

    this->enableAllBtn();

    m_countdownTimer->stop();

    m_countdown = recordTime;

    ui->label_showInfo->setText("");
}

void MainWindow::saveRVideoEnd(){
    recordingType = false;

    videoOut.release();

    QMessageBox::information(this,tr("Info"),tr("右眼影片擷取結束"),QMessageBox::Ok);

    //this->enableAllBtn();

    m_timer_cam_r->stop();

    m_countdownTimer->stop();

    m_countdown = recordTime;

    ui->label_showInfo->setText("");

    ui->btnCameraStart_r->setEnabled(true);

    ui->btnCameraStart_l->setEnabled(true);

    ui->btnOpenFolder->setEnabled(true);

    ui->btnCameraStart_r->setText(tr("重新採樣右眼"));

    ui->comboBox_camList->setEnabled(true);

    ui->btnRefresh->setEnabled(true);

    ui->btn_tester_finish->setEnabled(true);

    ui_processForm->setHintText(tr("影片處理中"));

    ui_processForm->show();

    // 開始處理任務
    QString path = QString("%1/right.%2").arg(m_testerData.m_testerPath).arg(ui_videoParam->getFileCode());
    /*
    QString oPath = QString("%1/exright.%2").arg(m_testerData.m_testerPath).arg(ui_videoParam->getFileCode());
    this->doExVideo(2,path,oPath);
    */
    QEventLoop m_loop;

    QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));

    emit autoProcessVideo(path,"right",ui_videoParam->getFileCode());

    m_loop.exec();

    qDebug()<<"finish";

    QString returnText = m_uploadThread->getReturnText();

    if(returnText.contains("-1"))
    {
        ui_processForm->hide();

        QMessageBox::information(this,tr("Info"),tr("取用影格太少，請重新量測!"),QMessageBox::Ok);

        return ;

    }

    QDir dir(m_testerData.m_testerPath);

    QStringList filters;

    filters << "overlap_*.avi" << "overlap_*.mp4"; // 選擇以overlap_開頭的jpg和png文件

    dir.setNameFilters(filters);

    QStringList fileList = dir.entryList(QDir::Files); // 只選文件，不包括folder

    QStringList files;
    foreach(QString file, fileList) {

        QString absolutePath = dir.absoluteFilePath(file);

        files.append(absolutePath);

        qDebug() << "Found file:" << absolutePath;

    }

    this->doFilesUpload(files);

    return ;
}

void MainWindow::saveLVideoEnd()
{
    recordingType = false;

    videoOut.release();

    QMessageBox::information(this,tr("Info"),tr("左眼影片擷取結束"),QMessageBox::Ok);

    //this->enableAllBtn();

    m_countdownTimer->stop();

    m_timer_cam_l->stop();

    m_countdown = recordTime;

    ui->label_showInfo->setText("");

    ui->btnCameraStart_r->setEnabled(true);

    ui->btnCameraStart_l->setEnabled(true);

    ui->btnOpenFolder->setEnabled(true);

    ui->btn_tester_finish->setEnabled(true);

    m_testerData.m_videoLeftFinished = true;

    ui->btnCameraStart_l->setText(tr("重新取樣左眼"));

    ui->comboBox_camList->setEnabled(true);

    ui->btnRefresh->setEnabled(true);

    ui->btn_tester_finish->setEnabled(true);

    ui_processForm->setHintText(tr("影片處理中"));

    ui_processForm->show();

    // 開始處理任務
    QString path = QString("%1/left.%2").arg(m_testerData.m_testerPath).arg(ui_videoParam->getFileCode());

    QEventLoop m_loop;

    QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));

    emit autoProcessVideo(path,"left",ui_videoParam->getFileCode());

    m_loop.exec();

    qDebug()<<"finish";

    QString returnText = m_uploadThread->getReturnText();

    if(returnText.contains("-1"))
    {
        ui_processForm->hide();

        QMessageBox::information(this,tr("Info"),tr("取用影格太少，請重新量測!"),QMessageBox::Ok);

        return ;

    }

    QDir dir(m_testerData.m_testerPath);

    QStringList filters;

    filters << "overlap_*.avi" << "overlap_*.mp4"; // 選擇以overlap_開頭的jpg和png文件

    dir.setNameFilters(filters);

    QStringList fileList = dir.entryList(QDir::Files); // 只選文件，不包括folder

    QStringList files;
    foreach(QString file, fileList) {

        QString absolutePath = dir.absoluteFilePath(file);

        files.append(absolutePath);

        qDebug() << "Found file:" << absolutePath;

    }

    this->doFilesUpload(files);

    return ;

}

void MainWindow::setCountdownText()
{
    m_countdown-- ;
    ui->label_showInfo->setText(QString(tr("影像擷取中 倒數 %1")).arg(m_countdown));

    if(m_countdown == 0) m_countdownTimer->stop();

}

void MainWindow::uploadDone()
{
    ui->txtShow->appendPlainText(tr("檔案上傳完成"));
    ui->txtShow->appendPlainText("\"Executiontime\":\"0.0\",\n"
                                 "\"HW\":\"NAN\",\n"
                                 "\"ID_NO\":\"test_case\",\n"
                                 "\"LTv\":\"0.93\",\n"
                                 "\"RT\":\"NAN\",\n"
                                 "\"S2\":\"[96]\",\n"
                                 "\"Situation\":\"1\",\n"
                                 "\"bpm\":\"80\",\n"
                                 "\"bpv0\":\"89\",\n"
                                 "\"bpv1\":\"122\"");
}


void MainWindow::updateSettingParam(QString url, QString pwd, QString dataInfo, int timeout)
{
    QSettings settings("./config.ini", QSettings::IniFormat);

    settings.beginGroup("General");

    settings.setValue("SERVER_URL",url);

    settings.setValue("PWD",pwd);

    settings.setValue("DATA_INFO",dataInfo);

    settings.setValue("TIMEOUT",timeout);

    settings.endGroup();

    emit setUploadParam(url,pwd,dataInfo,timeout);

}

void MainWindow::updateVideoSettingParam(QString format, int expose_value, int biteratet)
{
    QSettings settings("./video_config.ini", QSettings::IniFormat);

    settings.beginGroup("General");

    settings.setValue("file_Code", format);

    settings.setValue("expose_value", expose_value);

    settings.setValue("bite_rate", biteratet);

    settings.endGroup();

    m_videoUti.setExpose(expose_value);

}

void MainWindow::loadConfigAndSet()
{
    QSettings settings("./config.ini", QSettings::IniFormat);

    settings.beginGroup("General");

    QString url ;
    QString pwd ;
    QString dataInfo;
    int timeout;

    url = settings.value("SERVER_URL").toString();
    if(url =="")
    {
        qDebug()<<"no SERVER_URL data";
        settings.setValue("SERVER_URL","http://125.228.205.202:8080/eye_api");
        url = "http://125.228.205.202:8080/eye_api";
    }

    pwd = settings.value("PWD").toString();
    if(pwd =="")
    {
        qDebug()<<"no PWD data";
        settings.setValue("PWD","jihwosh2oh");
        pwd = "jihwosh2oh";
    }

    dataInfo = settings.value("DATA_INFO").toString();
    if(dataInfo =="")
    {
        qDebug()<<"no DATA_INFO data";
        settings.setValue("DATA_INFO","test_case");
        dataInfo = "test_case";
    }

    timeout = settings.value("TIMEOUT").toInt();
    if(timeout ==0)
    {
        qDebug()<<"no TIMEOUT data";
        settings.setValue("TIMEOUT",10);
        timeout = 10;
    }

    settings.endGroup();

    ui_settingForm->setDefault(url,pwd,dataInfo,timeout);

    emit setUploadParam(url,pwd,dataInfo,timeout);

}
void MainWindow::loadVConfigAndSet()
{
    QSettings settings("./video_config.ini", QSettings::IniFormat);

    settings.beginGroup("General");

    QString file_Code;
    int expose_value;
    int bite_rate;
    file_Code = settings.value("file_Code","avi").toString();

    expose_value = settings.value("expose_value",-5).toInt();

    bite_rate = settings.value("bite_rate",0).toInt();

    settings.endGroup();

    ui_videoParam->setDefaultValue(file_Code,expose_value,bite_rate);

    m_videoUti.setExpose(expose_value);


}

void MainWindow::initMenu()
{
    ui->actionEnglish->setIcon(QIcon("./—Pngtree—mathematical symbol icon free illustration_4663861.png"));
    ui->actionchinese->setIcon(QIcon("./—Pngtree—mathematical symbol icon free illustration_4663861.png"));
    ui->actionShowDetail->setIcon(QIcon("./—Pngtree—mathematical symbol icon free illustration_4663861.png"));

    ui->actionEnglish->setIconVisibleInMenu(true);
    ui->actionchinese->setIconVisibleInMenu(false);
    ui->actionShowDetail->setIconVisibleInMenu(false);

    CLS_GLOBAL::hideUploadDetail = true;

}

void MainWindow::initialElementState()
{
#ifdef SELF_TEST
    ui->btnCameraStart->setEnabled(true);

    ui->btnVideoSetting->setEnabled(true);

    ui->btnVideoSeltoCanny->setEnabled(true);

    ui->btnCameraStop->setEnabled(true);

    ui->btnVideoSelTest->setEnabled(true);

    ui->btnROINUpload->setEnabled(true);

    ui->btn_roiAuto->setEnabled(true);

#else
    ui->btnCameraStart->setHidden(true);

    ui->btnVideoSetting->setHidden(true);

    ui->btnVideoSeltoCanny->setHidden(true);

    ui->btnCameraStop->setHidden(true);

    ui->btnVideoSelTest->setHidden(true);

    ui->btnROINUpload->setHidden(true);

    ui->btn_roiAuto->setHidden(true);

#endif

    ui->btnRefresh->setEnabled(true);

    ui->lineEdit_camName->setEnabled(true);

    ui->btnEditCamName->setEnabled(true);

    ui->comboBox_camList->setEnabled(true);

    ui->textEdit_testerNo->setText("");

    ui->btnBuildTester->setEnabled(true);

    ui->textEdit_testerNo->setEnabled(true);

    ui->btnCameraStart_r->setEnabled(false);

    ui->btnCameraStart_l->setEnabled(false);

    ui->btnOpenFolder->setEnabled(false);

    ui->btn_cancelWriteVideo->setEnabled(false);

    ui->btn_tester_finish->setEnabled(false);

    ui->label_version->setText(this->getVersion());

    ui->btnVideoSelUpload->setEnabled(true);

}

void MainWindow::startToSaveVideo()
{
    /*


    int width = int(cap_Beam_Cam.get(CAP_PROP_FRAME_WIDTH)) ;   // 取得影像寬度

    int height = int(cap_Beam_Cam.get(CAP_PROP_FRAME_HEIGHT));  // 取得影像高度


    qDebug()<<"width:"<<width<<",height:"<<height;

    Size frameSize(width,height);

    double fps = 30.0;



    int fourcc = VideoWriter::fourcc('M','J','P','G');// 設定影片的格式為 MJPG

    QString foler = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    QString name = QDateTime::currentDateTime().toString("hh-mm-ss");

    QDir dir;

    if (dir.mkdir(foler)) { //建立mydir資料夾
        ui->txtShow->appendPlainText(QString(foler) +" : foler successfully created");
    }

    QString filename = QString("%1/%2/%3.avi").arg(dir.currentPath()).arg(foler).arg(name) ;

    videoOut = VideoWriter(filename.toStdString(), fourcc, fps, frameSize, true) ; // 產生空的影片
*/

    QString foler = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    QString name = QDateTime::currentDateTime().toString("hh-mm-ss");

    QDir dir;

    if (dir.mkdir(foler)) { //建立mydir資料夾

    }

    QString filename = QString("%1/%2/%3.%4").arg(dir.currentPath()).arg(foler).arg(name).arg(ui_videoParam->getFileCode()) ;

    this->videoOutSetting(filename);

    recordingType = true;

    QTimer::singleShot( 30000 , this , SLOT(saveVideoEnd()));

    ui->btnCameraStart->setText(tr("擷取中，請稍後"));

    this->disableAllBtn();

    m_countdown = recordTime;

    m_countdownTimer->start(1000);

    ui->label_showInfo->setText(QString("影像擷取中 倒數 %1").arg(m_countdown));

    /*

        Mat frame;

        while (true) {// 擷取影像

            bool ret = cap_Beam_Cam.read(frame); // or cap >> frame;
            if (!ret) {
                qDebug() << "Can't receive frame (stream end?). Exiting ...\n";
                break;
            }

            QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

            ui->right_label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));

            videoOut.write(frame);

            if (waitKey(1) == 'Q')  break;

        }

        cap_Beam_Cam.release();

        out.release();
        */
}
void MainWindow::disableAllBtn(){

    ui->btnCameraStart->setEnabled(false);

    ui->btnCameraStop->setEnabled(false);

    ui->btnRefresh->setEnabled(false);

    ui->lineEdit_camName->setEnabled(false);
    ui->btnEditCamName->setEnabled(false);
    ui->comboBox_camList->setEnabled(false);

    ui->textEdit_testerNo->setText(m_testerData.m_NameNo);

    ui->btnBuildTester->setEnabled(false);

    ui->textEdit_testerNo->setEnabled(false);

    ui->btnCameraStart_r->setEnabled(false);

    ui->btnCameraStart_l->setEnabled(false);

    ui->btnOpenFolder->setEnabled(false);

    ui->btnVideoSelUpload->setEnabled(false);

    ui->btn_tester_finish->setEnabled(false);

}
void MainWindow::enableAllBtn(){
    ui->btnCameraStart->setEnabled(true);
    ui->btnCameraStop->setEnabled(true);
    ui->btnRefresh->setEnabled(true);
    ui->comboBox_camList->setEnabled(true);
    ui->btnVideoSelUpload->setEnabled(true);
    ui->btnBuildTester->setEnabled(true);
    ui->lineEdit_camName->setEnabled(true);
    ui->btnEditCamName->setEnabled(true);
}

void MainWindow::startUploadThread()
{
    m_uploadThread = new uploadThread();

    QObject::connect(this, SIGNAL(uploadVideoFile(QString,QString)), m_uploadThread, SLOT(videoUploadTrans(QString,QString)));
    QObject::connect(this, SIGNAL(batchvideoUploadTrans(QStringList, QString)), m_uploadThread, SLOT(batchvideoUploadTrans(QStringList, QString)));
    QObject::connect(this, SIGNAL(setUploadParam(QString,QString,QString,int)), m_uploadThread, SLOT(uploadParamInitialSet(QString,QString,QString,int)));
    QObject::connect(this, SIGNAL(adjustVideo(QString, QString, QString)), m_uploadThread, SLOT(adjustVideo(QString, QString, QString)));
    QObject::connect(this, SIGNAL(autoROITrackingAndSplite(QString)), m_uploadThread, SLOT(autoROITrackingAndSplite(QString)));
    QObject::connect(this, SIGNAL(roiTrackingAndSplite(QString)), m_uploadThread, SLOT(roiTrackingAndSplite(QString)));
    QObject::connect(this, SIGNAL(splitVideotoSegmant(QString,int)), m_uploadThread, SLOT(splitVideotoSegmant(QString,int)));
    QObject::connect(this, SIGNAL(autoProcessVideo(QString, QString, QString)), m_uploadThread, SLOT(autoProcessVideo(QString, QString, QString)));
    m_uploadThread->moveToThread(&m_uploadT);

    m_uploadT.start();
}

void MainWindow::showInfo(QString title, QString text)
{
    QMessageBox msgBox;
    msgBox.setToolTip(title);
    msgBox.setText(text);
    msgBox.addButton(QMessageBox::Ok);
    msgBox.button(QMessageBox::Ok)->hide();
    msgBox.exec();
}

void MainWindow::initial_Tester_btnStats()
{
    ui->textEdit_testerNo->setEnabled(false);

    ui->btnBuildTester->setDisabled(true);

    ui->btnCameraStart_r->setEnabled(true);

    ui->btnCameraStart_r->setText(tr("擷取右眼影像"));

    ui->btnCameraStart_l->setEnabled(true);

    ui->btnCameraStart_l->setText(tr("擷取左眼影像"));

    ui->comboBox_camList->setEnabled(true);

    ui->btnRefresh->setEnabled(true);

    ui->lineEdit_camName->setEnabled(false);

    ui->btnEditCamName->setEnabled(false);

    ui->btnOpenFolder->setEnabled(true);

    ui->btnCameraStart->setEnabled(false);

    ui->btnCameraStop->setEnabled(false);

    ui->btn_cancelWriteVideo->setEnabled(true);

    ui->btn_tester_finish->setEnabled(true);
}
int MainWindow::deleteFile(QString filePath)
{
    //delete file
    QFile file(filePath);
    if (file.exists()) {
        if (file.remove()) {
            qDebug() << "File removed successfully:"<<filePath;
            //ui->txtShow->appendPlainText("File removed successfully:");
            //ui->txtShow->appendPlainText(filePath);
            return RESULT::DeleteSuccess;
        } else {
            qDebug() << "Failed to remove file:"<<filePath;
            //ui->txtShow->appendPlainText("Failed to remove file:");
            //ui->txtShow->appendPlainText(filePath);
            return RESULT::DeleteFail;
        }
    }
    else {
        qDebug() << "File does not exist:"<<filePath;
        //ui->txtShow->appendPlainText("File does not exist:");
        //ui->txtShow->appendPlainText(filePath);
        return RESULT::FileNotExist;
    }

}

void MainWindow::updateBitrate(int bitrate_M,QString vPath, QString &oPath)
{
    qDebug()<<"bitrate_M:"<<bitrate_M;
    //first check file size

    QString filePath = vPath;

    QFileInfo fileInfo(filePath);

    qint64 fileSize = fileInfo.size();

    qDebug() << "File size: " << fileSize << "bytes";

    int msize = fileSize / 1024 / 1024 ;

    if(msize <= 15) {

        ui->txtShow->appendPlainText("File size does not need to be changed:");

        ui->txtShow->appendPlainText(QString::number(msize).append("M"));

        oPath = oPath.remove("ex");

        return;
    }

    //ffmpeg -i "D:\API\video\6\right.mp4" -c:v mpeg4 -c:a aac -b:v 2M -b:a 256k "D:\API\video\6\right_6.mp4"
    //QString program = "ffmpeg";

    //QString cmd = QString("ffmpeg -i \"%1\" -c:v mpeg4 -c:a aac -b:v 2M -b:a 256k \"%2\"").arg(vPath).arg(oPath);

    QString program = QDir::currentPath().append("/ffmpeg.exe");

    qDebug()<< "program:"<<program;
#ifdef SELF_TEST
    ui->txtShow->appendPlainText(program);
#endif
    QStringList arguments;

    arguments << "-i" << vPath << "-c:v" << "mpeg4" << "-c:a" << "aac" << "-b:v" << "2M" << "-b:a" << "256k"<<"-y" << oPath;

    QProcess *process = new QProcess();
    process->start(program, arguments);
    process->waitForFinished(-1);


    qDebug() << process->errorString()<<","<<process->arguments();
#ifdef SELF_TEST
    ui->txtShow->appendPlainText(process->errorString());
#endif

}
void MainWindow::videoOutSetting(QString videoFilePath)
{
    int fourcc ;
    QString format = ui_videoParam->getFileCode();

    if(format == "avi")
        fourcc = VideoWriter::fourcc('M','J','P','G');// 設定影片的格式為 MJPG
    else
        fourcc = VideoWriter::fourcc('M','P','4','V');

    Size frameSize(m_videoUti.getWidth(), m_videoUti.getHeight());

    double fps = m_videoUti.getFPS();

    qDebug()<<"file path:"<<videoFilePath<<"m_videoUti.getWidth():"<<m_videoUti.getWidth()<<"m_videoUti.getHeight():"<<m_videoUti.getHeight()<<"fps:"<<fps;

    videoOut = VideoWriter(videoFilePath.toStdString(), fourcc, fps, frameSize, true) ; // 產生空的影片
}
void MainWindow::doFilesUpload(QStringList fileNames)
{

    ui_processForm->show();

    ui_processForm->setHintText(tr("檔案上傳中"));

     if (fileNames.isEmpty())
     {
         ui_processForm->hide();

         QMessageBox::information(this,tr("Info"),tr("取用影格太少，請重新量測!"),QMessageBox::Ok);

         return ;
     }
    /*
    //qDebug()<<"before del:"<<fileNames ;
    if (!fileNames.isEmpty()) {

        // 選擇了文件，處理文件列表
        int i = 0;
        foreach (const QString &fileName, fileNames) {
            // 對每個選擇的文件進行處理 確認檔案大小 是否為空 空的刪除
            qDebug()<<i;
            if (!fileName.isEmpty()) {
                // 選擇了文件，可以進行相應的操作
                QFileInfo base(fileName);
                if(base.size()<300000)
                {
                    fileNames[i] = "";
                    //qDebug()<<"delete size too small file:index "<<i<<":"<<fileName;
                    QFile file(fileName);
                    file.remove();
                }
                i++;
            }
        }

        fileNames.removeAll("");
        //qDebug()<<"after del:"<<fileNames ;

    }
    else {
        ui->txtShow->appendPlainText(tr("No file to upload."));
        ui_processForm->hide();
        return ;

    }*/

    if(fileNames.size() == 1)
    {
        QFileInfo base(fileNames.at(0));

        QString outTxtPath = QString("%1/%2_%3").arg(base.path()).arg(base.baseName()).arg("out.txt");

        ui_processForm->setHintText(tr("上傳中"));

        ui_processForm->show();

        QEventLoop m_loop;

        QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
        ///
        emit uploadVideoFile(fileNames.at(0),outTxtPath);

        m_loop.exec();

        qDebug()<<"finish";

        QString result = m_uploadThread->getReturnText();

        ui->txtShow->appendPlainText(result);

        if(result.contains(tr("失敗")))
        {
            ui_processForm->hide();

            return ;
        }

        if(!CLS_GLOBAL::hideUploadDetail)
            ui->txtShow->appendPlainText(QString(tr("自動轉存excel done\n")));

        ui_processForm->hide();

        return ;
    }

    QFileInfo videoBase(fileNames.at(0));

    QString outTxtPath = QString("%1/%2").arg(videoBase.path()).arg("out.txt");

    if(!CLS_GLOBAL::hideUploadDetail)
        ui->txtShow->appendPlainText(tr("上傳%1").arg(videoBase.path()));

    ui_processForm->setHintText(tr("上傳中"));

    ui_processForm->show();

    QEventLoop m_loop;

    QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
    ///
    emit batchvideoUploadTrans(fileNames, outTxtPath);

    m_loop.exec();

    qDebug()<<"finish";

    QString result = m_uploadThread->getReturnText();

    ui->txtShow->appendPlainText(tr("上傳完畢\n結果:\n") + result);

    if(result.contains(tr("失敗")))
    {
        ui_processForm->hide();

        QMessageBox::information(this,tr("Info"),tr("影片已上傳"),QMessageBox::Ok);

        return ;
    }

    if(!CLS_GLOBAL::hideUploadDetail)
        ui->txtShow->appendPlainText(QString(tr("自動轉存excel done\n")));

    ui_processForm->hide();

}

bool MainWindow::addToExcel(QList<EYEData> data)
{
    qDebug()<<"MainWindow::addToExcel";

    QString filepath = QDir::currentPath().append("\\EYEAutoGenData.xlsx");
    QFile file(filepath);
    if(!file.exists())
    {
        qDebug()<<"xlsx not exist, need to create !" ;
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合

        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1


        QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG,*cellH,*cellI;

        //设置标题
        int cellrow=1;
        QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
        QString B="B"+QString::number(cellrow);
        QString C="C"+QString::number(cellrow);
        QString D="D"+QString::number(cellrow);
        QString E="E"+QString::number(cellrow);
        QString F="F"+QString::number(cellrow);
        QString G="G"+QString::number(cellrow);
        QString H="H"+QString::number(cellrow);
        QString I="I"+QString::number(cellrow);
        //获取单元格
        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
        cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
        cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
        cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
        cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
        cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);
        cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);
        //设置单元格的值
        qDebug()<<"填入標題列";
        cellA->dynamicCall("SetValue(const QVariant&)",QVariant("影片路徑"));
        cellB->dynamicCall("SetValue(const QVariant&)",QVariant("文件路徑"));
        cellC->dynamicCall("SetValue(const QVariant&)",QVariant("結果"));
        cellD->dynamicCall("SetValue(const QVariant&)",QVariant("血氧"));
        cellE->dynamicCall("SetValue(const QVariant&)",QVariant("心跳"));
        cellF->dynamicCall("SetValue(const QVariant&)",QVariant("乳酸"));
        cellG->dynamicCall("SetValue(const QVariant&)",QVariant("舒張壓"));
        cellH->dynamicCall("SetValue(const QVariant&)",QVariant("收縮壓"));
        cellI->dynamicCall("SetValue(const QVariant&)",QVariant("血糖Glu"));

        cellrow++;

        int rows=data.size();

        qDebug()<<"資料列數"<<rows;;
        for(int i=0;i<rows;i++){
            qDebug()<<"填入列"<<i;
            QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
            QString B="B"+QString::number(cellrow);
            QString C="C"+QString::number(cellrow);
            QString D="D"+QString::number(cellrow);
            QString E="E"+QString::number(cellrow);
            QString F="F"+QString::number(cellrow);
            QString G="G"+QString::number(cellrow);
            QString H="H"+QString::number(cellrow);
            QString I="I"+QString::number(cellrow);

            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
            cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
            cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
            cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
            cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
            cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
            cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);
            cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);

            qDebug()<<data.at(i).videoPath;
            qDebug()<<data.at(i).outputTxtPath;
            qDebug()<<data.at(i).Situation;
            qDebug()<<data.at(i).S2;
            qDebug()<<data.at(i).bpm;
            qDebug()<<data.at(i).LTv;
            qDebug()<<data.at(i).bpv0;
            qDebug()<<data.at(i).bpv1;
            qDebug()<<data.at(i).glu;

            cellA->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).videoPath));//设置单元格的值
            cellB->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).outputTxtPath));
            cellC->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).Situation));
            cellD->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).S2));//设置单元格的值
            cellE->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpm));
            cellF->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).LTv));
            cellG->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv0));//设置单元格的值
            cellH->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv1));
            cellI->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).glu));

            cellrow++;
        }
        qDebug()<<"SaveAs(const QString&):"<<filepath;
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        qDebug()<<"Close()";
        workbook->dynamicCall("Close()");//关闭工作簿
        qDebug()<<"Quit()";
        excel->dynamicCall("Quit()");//关闭excel
        if(excel)
        {
            qDebug()<<"delete excel" ;
            delete excel;
            excel=NULL;
        }
    }else
    {
        //QAxObject *cell = worksheet->querySubObject("Cells(int, int)", row, column);
        //QVariant value = cell->property("Value");
        qDebug()<<"excle is exist, read it.";
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
        excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        QAxObject *workbook = workbooks->querySubObject("Open(QString&)",filepath);

        QAxObject *worksheets = workbook->querySubObject("WorkSheets");//获取工作表集合

        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
        QAxObject *usedRange = worksheet->querySubObject("UsedRange");
        //取得行數
        QAxObject *rows = usedRange->querySubObject("Rows");
        int iRows = rows->property("Count").toInt();
        qDebug()<<"資料列共"<<iRows;
        int cellrow = iRows + 1 ;
        qDebug()<<"填入列"<<cellrow;
        QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
        QString B="B"+QString::number(cellrow);
        QString C="C"+QString::number(cellrow);
        QString D="D"+QString::number(cellrow);
        QString E="E"+QString::number(cellrow);
        QString F="F"+QString::number(cellrow);
        QString G="G"+QString::number(cellrow);
        QString H="H"+QString::number(cellrow);
        QString I="I"+QString::number(cellrow);

        QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG,*cellH,*cellI;

        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
        cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
        cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
        cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
        cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
        cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);
        cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);
        qDebug()<<data.at(0).videoPath;
        qDebug()<<data.at(0).outputTxtPath;
        qDebug()<<data.at(0).Situation;
        qDebug()<<data.at(0).S2;
        qDebug()<<data.at(0).bpm;
        qDebug()<<data.at(0).LTv;
        qDebug()<<data.at(0).bpv0;
        qDebug()<<data.at(0).bpv1;
        qDebug()<<data.at(0).glu;
        cellA->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).videoPath));//设置单元格的值
        cellB->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).outputTxtPath));
        cellC->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).Situation));
        cellD->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).S2));//设置单元格的值
        cellE->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).bpm));
        cellF->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).LTv));
        cellG->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).bpv0));//设置单元格的值
        cellH->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).bpv1));
        cellI->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(0).glu));
        qDebug()<<"Save()";
        workbook->dynamicCall("Save()");
        qDebug()<<"Close()";
        workbook->dynamicCall("Close()");//关闭工作簿
        qDebug()<<"Quit()";
        excel->dynamicCall("Quit()");//关闭excel
        if(excel)
        {
            qDebug()<<"delete excel";
            delete excel;
            excel=NULL;
        }
    }


    return true;
}

void MainWindow::on_comboBox_camList_currentIndexChanged(int index)
{
    //int index = ui->comboBox_camList->currentIndex() ;

    qDebug()<<"camList_currentIndexChanged : index = "<< index ;

    if(m_timer->isActive() == true){
        m_timer->stop();
        ui->btnCameraStop->setText("Resume");
    }

    ui->lineEdit_camName->setText(ui->comboBox_camList->currentText());

    this->openCamera(index);
}

void MainWindow::on_btnCameraStart_clicked()
{
    this->startToSaveVideo();
}

void MainWindow::on_btnCameraStop_clicked()
{
    if(m_timer->isActive() == true){
        m_timer->stop();
        ui->btnCameraStop->setText("Resume");
    }
    else{
        m_timer->start(20);
        ui->btnCameraStop->setText("Pause");
    }
}

void MainWindow::on_btnRefresh_clicked()
{

    this->detectCamera();
}

void MainWindow::on_btnOpenFolder_clicked()
{
    QString strFilePath = m_testerData.m_testerPath;

    QDesktopServices::openUrl(QUrl::fromLocalFile(strFilePath)) ;

}

void MainWindow::on_btnBuildTester_clicked()
{
    //0 check text number
    //1 check current path
    //2 check no
    //3 create no folder
    //4 set text no
    //5 set btnR & btnL enable
    //6 set open folder enable
    //7 set textInput cant edit
    //8 set 2,3 enable
    //9 set

    //0

    if(index_Cam_R ==-1 or index_Cam_L == -1)
    {
        QMessageBox::information(this,tr("Info"),tr("請先設定相機名字 Left eye | Right eye "),QMessageBox::Ok);
        return ;
    }

    //

    QString name_No = ui->textEdit_testerNo->toPlainText() ;

    m_testerData.initial();

    QDir dir;

    if (dir.mkdir(m_todayFolder)) { //建立mydir資料夾
        ui->txtShow->appendPlainText(QString(m_todayFolder) +" : folder created");
    }

    QDir testerDir = QString(QDir::currentPath() +"//" + m_todayFolder );

    if(name_No.trimmed() == ""){

        QStringList filter;

        QFileInfoList fileInfoList = testerDir.entryInfoList(filter);

        int count = fileInfoList.count() ;

        m_testerData.m_NameNo = QString::number(count+1);
    }
    else
        m_testerData.m_NameNo = name_No.trimmed() ;

    m_testerData.m_testerPath = QString(QDir::currentPath()+"/"+m_todayFolder+"/"+m_testerData.m_NameNo);

    if (dir.mkpath(m_testerData.m_testerPath)) { //建立mydir資料夾
        //ui->txtShow->appendPlainText(QString(m_testerData.m_testerPath) +" : folder created");
        ui->txtShow->appendPlainText(QString(tr("已建立No %1資料夾").arg(m_testerData.m_NameNo)));

    }
    else
    {
        QMessageBox::information(this,tr("Warning"),tr("測試者資料夾建立失敗，請確認是否有特殊字元。\\ *"),QMessageBox::Ok);
        return ;
    }


    ui->textEdit_testerNo->setText(m_testerData.m_NameNo);

    this->initial_Tester_btnStats();


}

void MainWindow::on_btnCameraStart_r_clicked()
{

    //確認擷取的相機是否跟擷取的按鈕一致

    if(ui->comboBox_camList->currentIndex() != index_Cam_R){
        ui->comboBox_camList->setCurrentIndex(index_Cam_R);
        this->openCamera(index_Cam_R);
    }

    QMessageBox::information(this,tr("Info"),tr("調整好相機再按下OK"),QMessageBox::Ok);

    QString name = QString("right");

    QString filename = QString("%1/%2.%3").arg(m_testerData.m_testerPath).arg(name).arg(ui_videoParam->getFileCode()) ;

    QString exfileName = QString("%1/ex%2.%3").arg(m_testerData.m_testerPath).arg(name).arg(ui_videoParam->getFileCode()) ;

    //videoOut = VideoWriter(filename.toStdString(), fourcc, fps, frameSize, true) ; // 產生空的影片

    this->videoOutSetting(filename);

    recordingType = true;

    m_timer_cam_r->start(30000);

    ui->btnCameraStart_r->setText(tr("擷取中，請稍後"));

    this->disableAllBtn();

    m_countdown = recordTime;

    m_countdownTimer->start(1000);

    ui->label_showInfo->setText(tr("影像擷取中\n倒數 %1").arg(m_countdown));
}

void MainWindow::on_btnCameraStart_l_clicked()
{

    //確認擷取的相機是否跟擷取的按鈕一致
    if(ui->comboBox_camList->currentIndex() != index_Cam_L){
        ui->comboBox_camList->setCurrentIndex(index_Cam_L);
        this->openCamera(index_Cam_L);
    }

    QMessageBox::information(this,tr("Info"),tr("調整好相機再按下OK"),QMessageBox::Ok);

    QString name = QString("left");

    QString filename = QString("%1/%2.%3").arg(m_testerData.m_testerPath).arg(name).arg(ui_videoParam->getFileCode()) ;

    QString exfileName = QString("%1/ex%2.%3").arg(m_testerData.m_testerPath).arg(name).arg(ui_videoParam->getFileCode()) ;

    this->videoOutSetting(filename);

    recordingType = true;

    m_timer_cam_l->start(30000);

    ui->btnCameraStart_l->setText(tr("擷取中，請稍後"));

    this->disableAllBtn();

    m_countdown = recordTime;

    m_countdownTimer->start(1000);

    ui->label_showInfo->setText(tr("影像擷取中\n倒數 %1").arg(m_countdown));
}



void MainWindow::on_btnVideoSelUpload_clicked()
{

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("選擇影片檔"), "", tr("所有文件 (*.*)"));

    this->doFilesUpload(fileNames);

}


void MainWindow::on_btnVideoSetting_clicked()
{
    m_videoUti.get_cam_original_setting(&cap_Beam_Cam);

    m_videoUti.openCamera(&cap_Beam_Cam,0);

}

void MainWindow::on_btnVideoSeltoCanny_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("選擇影片"), "", tr("所有文件 (*.*)"));

    if (!fileName.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(fileName);

        qDebug()<< "fileName:"<<fileName <<"dir:"<<base.path();

        QString eyeSide = "right" ;
        QString format = "mp4";

        if(fileName.contains("left")) eyeSide = "left";
        if(fileName.contains("avi")) format = "avi";
        ui_processForm->show();

        ui_processForm->setHintText(tr("影片分割中"));

        QEventLoop m_loop;

        QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
        ///
        emit splitVideotoSegmant(fileName,3);

        m_loop.exec();

        qDebug()<<"finish";

        QString result = m_uploadThread->getReturnText();

        ui_processForm->hide();

        ui->txtShow->appendPlainText(result);

    }
}

void MainWindow::on_btnEditCamName_clicked()
{
    QString cam_name = ui->lineEdit_camName->text();
    int cam_index = ui->comboBox_camList->currentIndex();

    if(cam_name.contains("right",Qt::CaseInsensitive)) index_Cam_R = cam_index;
    else if(cam_name.contains("left",Qt::CaseInsensitive)) index_Cam_L = cam_index;

    ui->comboBox_camList->setItemText(cam_index,cam_name);


}

void MainWindow::on_btn_cancelWriteVideo_clicked()
{
    //將左右眼timer取消
    m_countdownTimer->stop();

    m_timer_cam_l->stop();

    m_timer_cam_r->stop();

    m_countdown = recordTime ;

    ui->label_showInfo->setText("");

    this->initial_Tester_btnStats();




}

void MainWindow::on_btn_tester_finish_clicked()
{
    this->initialElementState();
    ui->btnOpenFolder->setEnabled(true);
    ui->btnVideoSelUpload->setEnabled(true);

}

void MainWindow::on_action_about_triggered()
{
    //  this->ui_aboutDialog->setWindowFlags(Qt::WindowCloseButtonHint);
    this->ui_aboutDialog->setVersion(QString("eyeAnalysis version %1").arg(this->getVersion()));
    this->ui_aboutDialog->show();

}

void MainWindow::on_action_upload_set_triggered()
{
    this->ui_settingForm->show();
}

void MainWindow::on_actio_video_set_triggered()
{
    this->ui_videoParam->show();
}

void MainWindow::on_btnROINUpload_clicked() //ROI手動提取
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("選擇影片檔"), "", tr("所有文件 (*.*)"));

    if (!fileName.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(fileName);

        qDebug()<< "filePath:"<<fileName <<"dir:"<<base.path()<<"fileName"<<base.fileName();

        QString eyeSide = "right" ;
        QString format = "mp4";

        if(fileName.contains("left")) eyeSide = "left";
        if(fileName.contains("avi")) format = "avi";

        ui_processForm->show();

        ui_processForm->setHintText(tr("ROI tracking"));

        QEventLoop m_loop;

        QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
        ///
        emit roiTrackingAndSplite(fileName);

        m_loop.exec();

        qDebug()<<"finish";

        QString result = QString(tr("ROI提取結束，影片已分割")).append(m_uploadThread->getReturnText());

        ui_processForm->hide();

        ui->txtShow->appendPlainText(result);

    }
}

void MainWindow::on_btnVideoSelTest_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("選擇影片"), "", tr("所有文件 (*.*);"));

    if (!fileName.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(fileName);

        qDebug()<< "fileName:"<<fileName <<"dir:"<<base.path();


        ui_processForm->show();

        ui_processForm->setHintText(tr("影片校正中"));

        QEventLoop m_loop;

        QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
        QString eyeSide = "right" ;
        QString format = "mp4";

        if(fileName.contains("left")) eyeSide = "left";
        if(fileName.contains("avi")) format = "avi";
        emit adjustVideo(fileName,eyeSide,format);

        m_loop.exec();

        qDebug()<<"finish";

        QString result = m_uploadThread->getReturnText();

        ui_processForm->hide();

        ui->txtShow->appendPlainText(result);

    }
}

void MainWindow::on_btn_roiAuto_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("選擇影片檔"), "", tr("所有文件 (*.*)"));

    if (!fileName.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(fileName);

        qDebug()<< "filePath:"<<fileName <<"dir:"<<base.path()<<"fileName"<<base.fileName();

        QString eyeSide = "right" ;
        QString format = "mp4";

        if(fileName.contains("left")) eyeSide = "left";
        if(fileName.contains("avi")) format = "avi";

        ui_processForm->show();

        ui_processForm->setHintText(tr("ROI tracking"));

        QEventLoop m_loop;

        QObject::connect(m_uploadThread, SIGNAL(finished()), &m_loop, SLOT(quit()));
        ///
        emit autoROITrackingAndSplite(fileName);

        m_loop.exec();

        qDebug()<<"finish";

        QString result = QString(tr("ROI提取結束，影片已分割")).append(m_uploadThread->getReturnText());

        ui_processForm->hide();

        ui->txtShow->appendPlainText(result);

    }
}

void MainWindow::on_actionchinese_triggered()
{

    if (CLS_GLOBAL::translator != NULL)
    {
        qApp->removeTranslator(CLS_GLOBAL::translator);
        delete CLS_GLOBAL::translator;
        CLS_GLOBAL::translator = NULL;
    }
    CLS_GLOBAL::translator = new QTranslator;
    CLS_GLOBAL::translator->load("./Language/eyeT_zh_TW.qm");
    qApp->installTranslator(CLS_GLOBAL::translator);


    ui->actionEnglish->setIconVisibleInMenu(false);

    ui->actionchinese->setIconVisibleInMenu(true);

    ui->retranslateUi(this);//這裡實現語言翻譯器的更新
}

void MainWindow::on_actionEnglish_triggered()
{
    if (CLS_GLOBAL::translator != NULL)
    {
        qApp->removeTranslator(CLS_GLOBAL::translator);
        delete CLS_GLOBAL::translator;
        CLS_GLOBAL::translator = NULL;
    }
    CLS_GLOBAL::translator = new QTranslator;
    CLS_GLOBAL::translator->load("./Language/eyeT_en.qm");
    qApp->installTranslator(CLS_GLOBAL::translator);

    ui->actionEnglish->setIconVisibleInMenu(true);

    ui->actionchinese->setIconVisibleInMenu(false);

    ui->retranslateUi(this);//這裡實現語言翻譯器的更新
}

void MainWindow::on_actionShowDetail_triggered()
{
    bool iconVisible = ui->actionShowDetail->isIconVisibleInMenu();

    if(iconVisible)
    {
        ui->actionShowDetail->setIconVisibleInMenu(false);

        CLS_GLOBAL::hideUploadDetail = true;
    }
    else
    {
        ui->actionShowDetail->setIconVisibleInMenu(true);

        CLS_GLOBAL::hideUploadDetail = false;
    }


    //update show detail
}
