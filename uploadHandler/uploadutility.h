#ifndef UPLOADUTILITY_H
#define UPLOADUTILITY_H

#include <QByteArray>
#include <QCoreApplication>
#include "Python.h"
#include <QDebug>

#define PWD = "jihwosh2oh"

class uploadUtility: public QObject   
{
    Q_OBJECT

public:
    uploadUtility();
    ~uploadUtility();

    QString uploadVideo(QString filepath, QString outPath);

    void setUrl(QString url);

    void setPwd(QString pwd);

    void setDataInfo(QString dataInfo);

    void setTimeout(int timeout);





private :
    bool initialPy();

    QString upload(const QString filepath, const QString outPath);

    QString parseResult(QString src);

    QString getUrl();

    QString getPwd();

    QString getDataInfo();

    int getTimeout();

    QString m_url;

    QString m_pwd;

    QString m_dataInfo;

    int m_timeout;



};

#endif // UPLOADUTILITY_H
