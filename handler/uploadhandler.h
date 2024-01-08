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
signals:
    void finished();

private :


    uploadUtility *m_uploadCtrl;

    QString m_transReturnText;
};

#endif // UPLOADHANDLER_H
