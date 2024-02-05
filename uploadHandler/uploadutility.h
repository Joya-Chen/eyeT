#ifndef UPLOADUTILITY_H
#define UPLOADUTILITY_H

#include <QByteArray>
#include <QCoreApplication>
#include "Python.h"
#include <QDebug>
#include <QAxObject>
#define PWD = "jihwosh2oh"
class EYEData
{
public:
    /*
     * videoPath
     * outputTxtPath
     * Situation  //0 失敗 / 1 成功
     * S2
       bpm
       LTv
       bpv0
       bpv1
       glu
     */
    QString videoPath;
    QString outputTxtPath;
    QString Situation;
    QString S2;
    QString bpm;
    QString LTv;
    QString bpv0;
    QString bpv1;
    QString glu;

};
class uploadUtility: public QObject   
{
    Q_OBJECT

public:
    uploadUtility();
    ~uploadUtility();

    QString uploadVideo(QString filepath, QString outPath);

    QString uploadVideo(QStringList filepaths, QString outPath);

    void setUrl(QString url);

    void setPwd(QString pwd);

    void setDataInfo(QString dataInfo);

    void setTimeout(int timeout);

    QString autoProcessVideoToGetROI(QString videoPath);

    QString removeBlink(QString src, QString eyeSide, QString format); //Adjust twice

    QString trackingROIandsave(QString src, QString autoROI = "true"); //return roi path

    void splitVideoSegments(QString src,int segments = 3);

    void splitVideoHasOverlapSegments(QString src,int overlap_segments = 3);


private :
    bool initialPy();

    QString executeProcess(QString program, QStringList arg);

    QString upload(const QString filepath, const QString outPath);

    QString parseResult(QString src,QString filepath, QString outPath);

    QString parsebatchResult(QString src,QString filepath, QString outPath);

    void batchUpload(QStringList pathList);

    bool addToExcel(QList<EYEData> data);

    bool moveFileToSelectFolder(QString file, QString folderName);

    QString getUrl();

    QString getPwd();

    QString getDataInfo();

    int getTimeout();

    QString m_url;

    QString m_pwd;

    QString m_dataInfo;

    int m_timeout;

    QList<EYEData> m_eyeDataList;

    int m_success_ok;

    int m_success_fail;

    int m_http500Error;

    int m_otherhttpError;

    int m_uploadFileCount;

};

#endif // UPLOADUTILITY_H
