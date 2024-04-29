#ifndef UPLOADHANDLER_H
#define UPLOADHANDLER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QVariant>
#include <QElapsedTimer>
#include <QCoreApplication>
#include "../uploadHandler/uploadutility.h"
#include <QMap>
class uploadThread:public QObject//public QThread
{
    Q_OBJECT
public:

    uploadThread(QObject *parent = 0):QObject(parent)
    {
        m_uploadCtrl = new uploadUtility();



    }
    ~uploadThread()
    {
        qDebug()<<"retw :: destory uploadThread\n";
        delete m_uploadCtrl;
    }


    QString getReturnText()

    {

        return m_transReturnText;

    }

public slots:

    void videoUploadTrans(QString filePath, QString outPath)
    {
        m_transReturnText = m_uploadCtrl->uploadVideo(filePath,outPath);

        qDebug()<<"transaction end";

        emit finished();
    }

    void uploadParamInitialSet(QString url, QString pwd, QString dataInfo, int timeout)
    {
        qDebug()<<"uploadParamInitialSet:"<<url;
        m_uploadCtrl->setUrl(url);
        m_uploadCtrl->setPwd(pwd);
        m_uploadCtrl->setDataInfo(dataInfo);
        m_uploadCtrl->setTimeout(timeout);

    }

    void adjustVideo(QString src, QString eyeSide, QString format)
    {
        m_transReturnText = m_uploadCtrl->removeBlink(src, eyeSide, format);

        emit finished();
    }

    void autoROITrackingAndSplite(QString src)
    {
        m_transReturnText = m_uploadCtrl->trackingROIandsave(src);

        emit finished();
    }

    void roiTrackingAndSplite(QString src)
    {
        m_transReturnText = m_uploadCtrl->trackingROIandsave(src,"false");

        emit finished();
    }

    void splitVideotoSegmant(QString src,int sec)
    {
        m_uploadCtrl->splitVideoSegments(src,sec);

        m_transReturnText = QString(tr("分割完畢"));
        emit finished();
    }

    void autoProcessVideo(QString src, QString eyeSide, QString format)
    {

        m_transReturnText = m_uploadCtrl->removeBlink(src, eyeSide, format).simplified();

        QString removeblink_path = m_transReturnText;
        qDebug()<<"removeblink path:"<<m_transReturnText;

        if(eyeSide == "right")
            m_transReturnText = m_uploadCtrl->trackingROIandsave(removeblink_path,"false");
        else
            m_transReturnText = m_uploadCtrl->trackingROIandsave(m_transReturnText);

        if(m_transReturnText.trimmed().simplified() == "-2"){
            qDebug()<<"trackingROI fail, start manual tracking...";
            m_transReturnText = m_uploadCtrl->trackingROIandsave(removeblink_path,"false");
        }

        emit finished();
    }

    void batchvideoUploadTrans(QStringList filePaths, QString outPath)
    {
        m_transReturnText = m_uploadCtrl->uploadVideo(filePaths,outPath);

        qDebug()<<"transaction end";

        emit finished();
    }

signals:
    void finished();

private :


    uploadUtility *m_uploadCtrl;

    QString m_transReturnText;
};

#endif // UPLOADHANDLER_H
