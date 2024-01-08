#include "uploadutility.h"
#include <QtCore>
#include <QtNetwork>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
uploadUtility::uploadUtility()
{
    this->initialPy();

}
uploadUtility::~uploadUtility()
{
    Py_Finalize();

    deleteLater();
}

QString uploadUtility::uploadVideo(QString filepath, QString outPath)
{
    qDebug()<<"uploadVideo filepath:"<<filepath <<","<<outPath;

    return this->parseResult(this->upload(filepath, outPath));

}

void uploadUtility::setUrl(QString url)
{
   m_url = url;
}

void uploadUtility::setPwd(QString pwd)
{
    m_pwd = pwd;
}

void uploadUtility::setDataInfo(QString dataInfo)
{
    m_dataInfo = dataInfo;
}

void uploadUtility::setTimeout(int timeout)
{
    m_timeout = timeout;
}

bool uploadUtility::initialPy(){

    Py_SetPythonHome((const wchar_t *) L"./Python312");

    Py_Initialize();

    if(!Py_IsInitialized()){
        qDebug()<<"python 初始化失敗";
    }
    else qDebug()<<"python 初始化成功";

}

QString uploadUtility::upload(const QString filepath, const QString outPath)
{
    QString url = this->getUrl();  //http://125.228.205.202:8080/eye_api

    QString pwd = this->getPwd();   //jihwosh2oh

    QString dataInfo = this->getDataInfo();  //"test_case"

    int timeout = this->getTimeout();  //10

    PyObject* fun1Py = PyImport_ImportModule("TEST");

    PyObject* ffhello = PyObject_GetAttrString(fun1Py,"upload");

    // 创建元组设置参数
    //

    PyObject*  arg  = PyBytes_FromString(url.toLatin1().data());
    PyObject*  arg1  = PyBytes_FromString(pwd.toLatin1().data());
    PyObject*  arg2  = PyBytes_FromString(dataInfo.toLatin1().data());
    PyObject*  arg3 = PyBytes_FromString(filepath.toLatin1().data());
    PyObject*  arg4 = PyBytes_FromString(outPath.toLatin1().data());
    PyObject*  arg5 = PyLong_FromLong(timeout);

    PyObject*  args = PyTuple_New(6);
    PyTuple_SetItem(args, 0, arg);
    PyTuple_SetItem(args, 1, arg1);
    PyTuple_SetItem(args, 2, arg2);
    PyTuple_SetItem(args, 3, arg3);
    PyTuple_SetItem(args, 4, arg4);
    PyTuple_SetItem(args, 5, arg5);

/*
    PyObject*  arg1 = PyBytes_FromString(filepath.toLatin1().data());
    PyObject*  arg2 = PyBytes_FromString(outPath.toLatin1().data());

    PyObject*  args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);
*/

    QString result;

    PyObject* fhellocc = PyObject_CallObject(ffhello, args);
    if(fhellocc) {
        result = PyBytes_AsString(fhellocc);
        qDebug() << "call py function result:" << result;
    }
    else{
        qDebug() << "fail load func";
        return QString("call py function fail") ;
    }

    QString fileName = outPath;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result =  QString("Cannot open file for reading:%1").arg(file.errorString());

    }
    else{
        QTextStream in(&file);

        result=in.readAll();

        file.close();
    }
    qDebug() << "result from txt:" << result;


    return result;
}

QString uploadUtility::parseResult(QString src)
{


    QJsonParseError err_rpt;

    QJsonDocument  root_Doc = QJsonDocument::fromJson(src.toLatin1(), &err_rpt); // 字符串格式化为JSON

    qDebug()<<"root doc";

    if(err_rpt.error != QJsonParseError::NoError)

    {
        return QString::fromUtf8("上傳失敗\n%1").arg(src);
    }
    else    // JSON格式
    {
        qDebug() << "JSON格式correct：\n" << root_Doc;

        QJsonObject root_Obj = root_Doc.object();
        QJsonValue DataInfo = root_Obj.value("DataInfo"); // DataInfo
        if(DataInfo.isArray()) // 可省略
        {
            qDebug()<<"isArray";
                    QJsonObject info_Obj = DataInfo.toArray().at(0).toObject();

                    QString Executiontime = info_Obj.value("Executiontime").toString();
                    QString HW = info_Obj.value("HW").toString();
                    QString ID_NO = info_Obj.value("ID_NO").toString();
                    QString LTv = info_Obj.value("LTv").toString();
                    QString S2 = info_Obj.value("S2").toString();
                    int Situation = info_Obj.value("Situation").toInt(); //0 失敗 / 1 成功
                    QString bpm = info_Obj.value("bpm").toString();
                    QString bpv0 = info_Obj.value("bpv0").toString();
                    QString bpv1 = info_Obj.value("bpv1").toString();
                    QString glu = info_Obj.value("glu").toString();

                    qDebug()<<"000";
                    QString result,returnTxt;

                    if(Situation==0){

                        result = QString::fromUtf8("失敗");
                    }
                    else{
                        result = QString::fromUtf8("成功");
                    }

                    returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8\n%9")
                                                .arg(QString::fromUtf8("分析結果:")+ result)
                                                .arg(QString::fromUtf8("乳酸值:") + LTv)
                                                .arg(QString::fromUtf8("血氧值:") + S2)
                                                .arg(QString::fromUtf8("心跳:") + bpm)
                                                .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                                                .arg(QString::fromUtf8("收縮壓:") + bpv1)
                                                .arg(QString::fromUtf8("血糖值:") + glu);



                    qDebug() <<returnTxt ;


                    return returnTxt;

    }
        else
        {
            qDebug()<<"not Array";
            QJsonObject info_Obj = DataInfo.toObject();

            QString Executiontime = info_Obj.value("Executiontime").toString();
            QString HW = info_Obj.value("HW").toString();
            QString ID_NO = info_Obj.value("ID_NO").toString();
            QString LTv = info_Obj.value("LTv").toString();
            QString S2 = info_Obj.value("S2").toString();
            QString Situation = info_Obj.value("Situation").toString(); //0 失敗 / 1 成功
            QString bpm = info_Obj.value("bpm").toString();
            QString bpv0 = info_Obj.value("bpv0").toString();
            QString bpv1 = info_Obj.value("bpv1").toString();
            QString glu = info_Obj.value("glu").toString();

            qDebug()<<"000";
            QString result,returnTxt;

            if(Situation.contains("0")){

                result = QString::fromUtf8("失敗");
            }
            else{
                result = QString::fromUtf8("成功");
            }

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                                        .arg(QString::fromUtf8("分析結果:")+ result)
                                        .arg(QString::fromUtf8("乳酸值:") + LTv)
                                        .arg(QString::fromUtf8("血氧值:") + S2)
                                        .arg(QString::fromUtf8("心跳:") + bpm)
                                        .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                                        .arg(QString::fromUtf8("收縮壓:") + bpv1)
                                        .arg(QString::fromUtf8("血糖值:") + glu);

            qDebug() <<returnTxt ;


            return returnTxt;
        }
    }

}

QString uploadUtility::getUrl()
{
    return m_url;
}

QString uploadUtility::getPwd()
{
    return m_pwd;
}

QString uploadUtility::getDataInfo()
{
    return m_dataInfo ;
}

int uploadUtility::getTimeout()
{
    return m_timeout;
}
