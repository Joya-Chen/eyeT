#include "uploadutility.h"
#include <QtCore>
#include <QtNetwork>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QList>
uploadUtility::uploadUtility()
{
    this->initialPy();

}
uploadUtility::~uploadUtility()
{
    Py_Finalize();

    deleteLater();
}
QString uploadUtility::executeProcess(QString program, QStringList arg)
{

    QTextCodec *codec = QTextCodec::codecForName("Big5");

    qDebug()<< "program:"<<program<<",arg"<<arg;

    QProcess *process = new QProcess();
    process->start(program, arg);
    process->waitForFinished(-1);

    QString reply = codec->toUnicode(process->readAll());

    qDebug() << "reply:"<<reply;


    return reply;

}

QString uploadUtility::uploadVideo(QString filepath, QString outPath)
{
    qDebug()<<"uploadVideo filepath:"<<filepath <<","<<outPath;

    QStringList arguments;

    QString program = QDir::currentPath().append("/TEST.exe");

    QString url = this->getUrl();  //http://125.228.205.202:8080/eye_api

    QString pwd = this->getPwd();   //jihwosh2oh

    QString dataInfo = this->getDataInfo();  //"test_case"

    int timeout = this->getTimeout();  //10

    arguments << url << pwd << dataInfo << filepath <<outPath << QString::number(timeout);

    QString result = this->executeProcess(program,arguments);


    return this->parseResult(result,filepath,outPath);

}

QString uploadUtility::uploadVideo(QStringList filepaths, QString outPath)
{
    QStringList arguments;

    QString program = QDir::currentPath().append("/TEST.exe");

    QString url = this->getUrl();  //http://125.228.205.202:8080/eye_api

    QString pwd = this->getPwd();   //jihwosh2oh

    QString dataInfo = this->getDataInfo();  //"test_case"

    int timeout = this->getTimeout();  //10

    m_eyeDataList.clear();

    m_success_ok = 0;

    m_success_fail = 0;

    m_http500Error = 0;

    m_otherhttpError = 0;

    m_uploadFileCount = filepaths.size();

    for (int i = 0; i<filepaths.size();i++){

        qDebug()<<"uploadVideo filepath:"<<filepaths.at(i) <<","<<outPath;

        arguments.clear();

        arguments << url << pwd << dataInfo << filepaths.at(i) <<outPath << QString::number(timeout);

        QString result = this->executeProcess(program,arguments);

        this->parsebatchResult(result,filepaths.at(i),outPath);
    }

    this->addToExcel(m_eyeDataList);

    QString dataCal="";

    if(m_success_ok != 0)
        dataCal = this->doDataCalculation(m_eyeDataList);


    QString result = QString("上傳檔案: %1筆\n============\n分析成功: %2筆\n分析失敗: %3\n500 Internet error: %4\nother httpError: %5\n============\n%6\n")
            .arg(m_uploadFileCount)
            .arg(m_success_ok)
            .arg(m_success_fail)
            .arg(m_http500Error)
            .arg(m_otherhttpError)
            .arg(dataCal);

    QFile file(outPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << result;
            file.close();
            qDebug() << "結果已寫入" << outPath;
        } else {
            qDebug() << "無法開啟" << outPath;
        }

    return result;

}

void uploadUtility::setUrl(QString url)
{
    qDebug()<<"set url:"<<url;
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

QString uploadUtility::autoProcessVideoToGetROI(QString videoPath)
{
    QString eyeSide = "right" ;
    QString format = "mp4";

    if(videoPath.contains("left")) eyeSide = "left";
    if(videoPath.contains("avi")) format = "avi";
    qDebug()<<videoPath<<","<<eyeSide<<","<<format;

    return this->removeBlink(videoPath,eyeSide,format);
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
    PyObject*  arg3 = PyBytes_FromString(filepath.toUtf8().data());
    PyObject*  arg4 = PyBytes_FromString(outPath.toUtf8().data());
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

QString uploadUtility::parseResult(QString src,QString filepath, QString outPath)
{

    QJsonParseError err_rpt;

    QJsonDocument  root_Doc = QJsonDocument::fromJson(src.toLatin1(), &err_rpt); // 字符串格式化为JSON

    qDebug()<<"root doc";

    QString result,returnTxt;
    QList<EYEData> eyedataList ;
    EYEData data;
    data.videoPath = filepath;
    data.outputTxtPath = outPath;
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
            QString glu = info_Obj.value("glu").toString().remove("[").remove("]");

            qDebug()<<"000";


            if(Situation==0){

                result = QString::fromUtf8("失敗");
            }
            else{
                result = QString::fromUtf8("成功");
            }

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8\n%9")
                    .arg(QString::fromUtf8("分析結果:")+ result)
                    .arg(QString::fromUtf8("血氧值:") + S2.replace("[","").replace("]",""))
                    .arg(QString::fromUtf8("心跳:") + bpm)
                    .arg(QString::fromUtf8("乳酸值:") + LTv)
                    .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                    .arg(QString::fromUtf8("收縮壓:") + bpv1)
                    .arg(QString::fromUtf8("血糖值:") + glu.replace("[","").replace("]",""));

            data.Situation = result;
            data.S2 = S2;
            data.bpm = bpm;
            data.LTv = LTv;
            data.bpv0 = bpv0;
            data.bpv1 = bpv1;
            data.glu = glu;

            eyedataList.append(data);


            qDebug() <<returnTxt ;




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


            if(Situation.contains("0")){

                result = QString::fromUtf8("失敗");
            }
            else{
                result = QString::fromUtf8("成功");
            }

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                    .arg(QString::fromUtf8("分析結果:")+ result)
                    .arg(QString::fromUtf8("血氧值:") + S2.replace("[","").replace("]",""))
                    .arg(QString::fromUtf8("心跳:") + bpm)
                    .arg(QString::fromUtf8("乳酸值:") + LTv)
                    .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                    .arg(QString::fromUtf8("收縮壓:") + bpv1)
                    .arg(QString::fromUtf8("血糖值:") + glu.replace("[","").replace("]",""));

            data.Situation = result;
            data.S2 = S2;
            data.bpm = bpm;
            data.LTv = LTv;
            data.bpv0 = bpv0;
            data.bpv1 = bpv1;
            data.glu = glu;

            eyedataList.append(data);

            qDebug() <<returnTxt ;

        }
    }

    this->addToExcel(eyedataList);

    return returnTxt;



}
QString uploadUtility::parsebatchResult(QString src, QString filepath, QString outPath)
{
    /*
     *
     * m_eyeDataList.clear();
     * m_success_ok = 0;
     * m_success_fail = 0;
     * m_http500Error = 0;
     * m_otherhttpError = 0;
     * m_uploadFileCount = 0;
     *
     */
    QJsonParseError err_rpt;

    QJsonDocument  root_Doc = QJsonDocument::fromJson(src.toLatin1(), &err_rpt); // 字符串格式化JSON

    qDebug()<<"root doc";

    QString result,returnTxt;
    //QList<EYEData> eyedataList ;
    EYEData data;
    data.videoPath = filepath;
    data.outputTxtPath = outPath;
    if(err_rpt.error != QJsonParseError::NoError)

    {

        if(src.contains("500 Server Error"))
        {
            m_http500Error ++;
            this->moveFileToSelectFolder(filepath, "500HttpError");
            return QString::fromUtf8("上傳失敗\n原因:\n%1 :%2").arg("500HttpError").arg(src);
        }
        else
        {
            m_otherhttpError ++;
            this->moveFileToSelectFolder(filepath, "OtherHttpError");
            return QString::fromUtf8("上傳失敗\n原因:\n%1 :%2").arg("OtherHttpError").arg(src);
        }
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
            QString glu = info_Obj.value("glu").toString().remove("[").remove("]");

            qDebug()<<"000";


            if(Situation==0){
                m_success_fail ++;
                this->moveFileToSelectFolder(filepath, "AnalyzeFail");
                result = QString::fromUtf8("失敗");
                return result;
            }
            else{
                m_success_ok++;
                this->moveFileToSelectFolder(filepath, "Success");
                result = QString::fromUtf8("成功");
            }

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8\n%9")
                    .arg(QString::fromUtf8("分析結果:")+ result)
                    .arg(QString::fromUtf8("血氧值:") + S2.replace("[","").replace("]",""))
                    .arg(QString::fromUtf8("心跳:") + bpm)
                    .arg(QString::fromUtf8("乳酸值:") + LTv)
                    .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                    .arg(QString::fromUtf8("收縮壓:") + bpv1)
                    .arg(QString::fromUtf8("血糖值:") + glu.replace("[","").replace("]",""));

            data.Situation = result;
            data.S2 = S2;
            data.bpm = bpm;
            data.LTv = LTv;
            data.bpv0 = bpv0;
            data.bpv1 = bpv1;
            data.glu = glu;

            m_eyeDataList.append(data);


            qDebug() <<returnTxt ;




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


            if(Situation.contains("0")){

                m_success_fail ++;
                result = QString::fromUtf8("失敗");
                this->moveFileToSelectFolder(filepath, "AnalyzeFail");
                return result;
            }
            else{
                m_success_ok ++;
                this->moveFileToSelectFolder(filepath, "Success");
                result = QString::fromUtf8("成功");
            }

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                    .arg(QString::fromUtf8("分析結果:")+ result)
                    .arg(QString::fromUtf8("血氧值:") + S2.replace("[","").replace("]",""))
                    .arg(QString::fromUtf8("心跳:") + bpm)
                    .arg(QString::fromUtf8("乳酸值:") + LTv)
                    .arg(QString::fromUtf8("舒張壓:" )+ bpv0)
                    .arg(QString::fromUtf8("收縮壓:") + bpv1)
                    .arg(QString::fromUtf8("血糖值:") + glu.replace("[","").replace("]",""));

            data.Situation = result;
            data.S2 = S2;
            data.bpm = bpm;
            data.LTv = LTv;
            data.bpv0 = bpv0;
            data.bpv1 = bpv1;
            data.glu = glu;

            m_eyeDataList.append(data);

            qDebug() <<returnTxt ;

        }
    }

    return returnTxt;

}

QString uploadUtility::removeBlink(QString src, QString eyeSide, QString format)
{

    if (!src.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(src);

        qDebug()<< "src:"<<src <<"dir:"<<base.path();

        qDebug()<<src<<","<<eyeSide<<","<<format;

        QStringList arguments;

        arguments << src << eyeSide << format ;

        QString program = QDir::currentPath().append("/firstAdjust-all.exe");

        QString result = this->executeProcess(program,arguments);

        return result; //回應移除後影片path
    }

    return "No file";
}


QString uploadUtility::trackingROIandsave(QString src, QString autoROI) //return roi path
{


    if (!src.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(src);

        qDebug()<< "src:"<<src <<"dir:"<<base.path()<<"src"<<base.fileName();

        QString eyeSide = "right" ;
        QString format = "mp4";

        if(src.contains("left")) eyeSide = "left";
        if(src.contains("avi")) format = "avi";
        qDebug()<<src<<","<<eyeSide<<","<<format;

        QStringList arguments;

        arguments << src << eyeSide << format << autoROI <<"" ;

        QString program = QDir::currentPath().append("/tracking.exe");

        QString result = this->executeProcess(program,arguments);

        return result;

    }
    return "No file";
}

void uploadUtility::splitVideoSegments(QString src,int segments)
{
    if (!src.isEmpty()) {
        // 選擇了文件，可以進行相應的操作

        QFileInfo base(src);

        qDebug()<< "src:"<<src <<"dir:"<<base.path()<<"src"<<base.fileName();

        QString eyeSide = "right" ;
        QString format = "mp4";

        if(src.contains("left")) eyeSide = "left";
        if(src.contains("avi")) format = "avi";
        qDebug()<<src<<","<<eyeSide<<","<<format;

        QStringList arguments;

        arguments << src << eyeSide << format << QString("false") <<QString("s") ;

        QString program = QDir::currentPath().append("/tracking.exe");

        QString result = this->executeProcess(program,arguments);

        return;

    }
    return;
}

void uploadUtility::splitVideoHasOverlapSegments(QString src,int overlap_segments)
{

}

void uploadUtility::batchUpload(QStringList pathList)
{

}

bool uploadUtility::addToExcel(QList<EYEData> data)
{
    qDebug()<<"uploadUtility::addToExcel";

    QString filepath = QDir::currentPath().append("\\EYEAutoGenData.xlsx");
    QFile file(filepath);
    if(!file.exists())
    {
        qDebug()<<"xlsx not exist, need to create !" ;
        QAxObject *excel = new QAxObject(this);
        excel->setControl("Excel.Application");//連接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)","false");//不顯示窗體
        excel->setProperty("DisplayAlerts", false);//不顯示任何警告信息。如果為true那在關閉是会出現類似“文件已修改，是否保存”的提示
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//獲取工作簿集合

        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//獲取當前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//獲取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//獲取工作表集合的工作表1，即sheet1


        QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG,*cellH,*cellI;

        //設置標題
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
        //獲取單元格
        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
        cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
        cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
        cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
        cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
        cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);
        cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);
        //設置單元格的值
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
            QString A="A"+QString::number(cellrow);//設置要操作的單元格，如A1
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

            cellA->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).videoPath));//設置單元格的值
            cellB->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).outputTxtPath));
            cellC->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).Situation));
            cellD->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).S2));//設置單元格的值
            cellE->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpm));
            cellF->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).LTv));
            cellG->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv0));//設置單元格的值
            cellH->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv1));
            cellI->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).glu));

            cellrow++;
        }
        qDebug()<<"SaveAs(const QString&):"<<filepath;
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators將路径中的"/"轉換為"\"，不然一定保存不了。
        qDebug()<<"Close()";
        workbook->dynamicCall("Close()");//關閉工作簿
        qDebug()<<"Quit()";
        excel->dynamicCall("Quit()");//關閉excel
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



        int datasize = data.size();

        qDebug()<<"資料列共"<<iRows<<"要填入:"<<datasize;

        int cellrow = iRows + 1 ;

        for(int i = 0;i<datasize;i++)
        {

            qDebug()<<"填入列"<<cellrow;
            QString A="A"+QString::number(cellrow);//設置要操作的單元格，如A1
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
            qDebug()<<data.at(i).videoPath;
            qDebug()<<data.at(i).outputTxtPath;
            qDebug()<<data.at(i).Situation;
            qDebug()<<data.at(i).S2;
            qDebug()<<data.at(i).bpm;
            qDebug()<<data.at(i).LTv;
            qDebug()<<data.at(i).bpv0;
            qDebug()<<data.at(i).bpv1;
            qDebug()<<data.at(i).glu;
            cellA->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).videoPath));//設置單元格的值
            cellB->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).outputTxtPath));
            cellC->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).Situation));
            cellD->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).S2));//設置單元格的值
            cellE->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpm));
            cellF->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).LTv));
            cellG->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv0));//設置單元格的值
            cellH->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).bpv1));
            cellI->dynamicCall("SetValue(const QVariant&)",QVariant(data.at(i).glu));
            cellrow ++;
        }
        qDebug()<<"Save()";
        workbook->dynamicCall("Save()");
        qDebug()<<"Close()";
        workbook->dynamicCall("Close()");//關閉工作簿
        qDebug()<<"Quit()";
        excel->dynamicCall("Quit()");//關閉excel
        if(excel)
        {
            qDebug()<<"delete excel";
            delete excel;
            excel=NULL;
        }
    }


    return true;
}

QString uploadUtility::doDataCalculation(QList<EYEData> data)
{
    QString returnTxt;

    int dataSize = data.size();

    QList<int> S2;
    QList<int> bpm;
    QList<float> LTv;
    QList<int> bpv0;
    QList<int> bpv1;
    QList<int> glu;

    for(int i = 0; i <dataSize ; i++)
    {
        S2.append(data.at(i).S2.toInt());
        bpm.append(data.at(i).bpm.toInt());
        LTv.append(data.at(i).LTv.toFloat());
        bpv0.append(data.at(i).bpv0.toInt());
        bpv1.append(data.at(i).bpv1.toInt());
        glu.append(data.at(i).glu.toInt());
    }

    // 使用std::sort函数排序
       std::sort(S2.begin(), S2.end());
       std::sort(bpm.begin(), bpm.end());
       std::sort(LTv.begin(), LTv.end());
       std::sort(bpv0.begin(), bpv0.end());
       std::sort(bpv1.begin(), bpv1.end());
       std::sort(glu.begin(), glu.end());

       qDebug()<<S2 ;
       qDebug()<<bpm;
       qDebug()<<LTv;
       qDebug()<<bpv0;
       qDebug()<<bpv1;
       qDebug()<<glu;

    if(dataSize>=12)
    {
        // 刪除最大和最小兩筆
          for (int i = 0; i < 2; i++) {
              S2.removeLast();
              S2.removeFirst();

              bpm.removeLast();
              bpm.removeFirst();

              LTv.removeLast();
              LTv.removeFirst();

              bpv0.removeLast();
              bpv0.removeFirst();

              bpv1.removeLast();
              bpv1.removeFirst();
          }

          // 刪除最大3筆
            for (int i = 0; i < 3; i++) {
                glu.removeLast();
            }
            glu.removeFirst();


          //  計算剩下數值平均
          int sum = 0;
          for (int i : S2) {
              sum += i;
          }
          int averageS2 = sum / S2.size();

          sum = 0;
          for (int i : bpm) {
              sum += i;
          }
          int averageBpm = sum / bpm.size();

          float sumLTv = 0.00 ;
          for (float i : LTv) {
              sumLTv += i;
          }
          float averageLTv = float(sumLTv / LTv.size());

          sum = 0;
          for (int i : bpv0) {
              sum += i;
          }
          int averageBpv0 = sum / bpv0.size();

          sum = 0;
          for (int i : bpv1) {
              sum += i;
          }
          int averageBpv1 = sum / bpv1.size();

          sum = 0;
          for (int i : glu) {
              sum += i;
          }
          int averageGlu = sum / glu.size();

          qDebug()<<"after:"<<averageS2 ;
          qDebug()<<"after:"<<averageBpm;
          qDebug()<<"after:"<<averageLTv;
          qDebug()<<"after:"<<averageBpv0;
          qDebug()<<"after:"<<averageBpv1;
          qDebug()<<"after:"<<averageGlu;


          // 剔除比平均大110%和小於90%的值
            for (int i = 0; i < S2.size(); i++ ) {
                if (S2[i] > averageS2 * 1.1 || S2[i] < averageS2 * 0.9) {
                    S2[i] = 0;
                }
            }

            S2.removeAll(0);

            // 計算剩下數值的平均值
            sum = 0;
            for (int i : S2) {
                sum += i;
            }
            int newAverageS2 = sum / S2.size();

            qDebug() << "剔除後newAverageS2的平均值:" << newAverageS2;

            for (int i = 0; i < bpm.size(); i++) {
                if (bpm[i] > averageBpm * 1.1 || bpm[i] < averageBpm * 0.9) {
                    bpm[i] = 0;
                }
            }

            bpm.removeAll(0);

            // 計算剩下數值的平均值
            sum = 0;
            for (int i : bpm) {
                sum += i;
            }
            int newAverageBpm = sum / bpm.size();

            qDebug() << "剔除後newAverageBpm的平均值:" << newAverageBpm;

            for (int i = 0; i < LTv.size();i++ ) {
                if (LTv[i] > averageLTv * 1.1 || LTv[i] < averageLTv * 0.9) {
                    LTv[i] = 0.00;
                }
            }

            LTv.removeAll(0.00);

            // 计算剩下数值的平均值
            sumLTv = 0.00;
            for (float i : LTv) {
                sumLTv += i;
            }
            float newAverageLTv = float(sumLTv / LTv.size());


            qDebug()<<"sumLTv:"<<sumLTv;
            qDebug()<<"float("<<sumLTv<<" / "<<LTv.size()<<"):"<<averageLTv;


            qDebug() << "剔除後newAverageLTv的平均值:" << newAverageLTv;

            for (int i = 0; i < bpv0.size(); i++) {
                if (bpv0[i] > averageBpv0 * 1.1 || bpv0[i] < averageBpv0 * 0.9) {
                    bpv0[i] = 0;
                }
            }

            bpv0.removeAll(0);

            // 计算剩下数值的平均值
            sum = 0;
            for (int i : bpv0) {
                sum += i;
            }
            int newAverageBpv0 = sum / bpv0.size();

            qDebug() << "剔除後newAveragebpv0的平均值:" << newAverageBpv0;

            for (int i = 0; i < bpv1.size(); i++) {
                if (bpv1[i] > averageBpv1 * 1.1 || bpv1[i] < averageBpv1 * 0.9) {
                    bpv1[i] = 0;
                }
            }

            bpv1.removeAll(0);

            // 计算剩下数值的平均值
            sum = 0;
            for (int i : bpv1) {
                sum += i;
            }
            int newAverageBpv1 = sum / bpv1.size();

            qDebug() << "剔除後newAveragebpv1的平均值:" << newAverageBpv1;

            for (int i = 0; i < glu.size(); i++) {
                if (glu[i] > averageGlu * 1.2 || glu[i] < averageGlu * 0.9) {
                    glu[i] = 0;
                }
            }

            glu.removeAll(0);

            // 计算剩下数值的平均值
            sum = 0;
            for (int i : glu) {
                sum += i;
            }
            int newAverageGlu = sum / glu.size();

            qDebug() << "剔除後newAverageglu的平均值:" << newAverageGlu;

            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                    .arg(QString::fromUtf8("分析統計結果:"))
                    .arg(QString::fromUtf8("血氧值:%1").arg(newAverageS2))
                    .arg(QString::fromUtf8("心跳:%2").arg(newAverageBpm))
                    .arg(QString::fromUtf8("乳酸值:%3").arg(newAverageLTv))
                    .arg(QString::fromUtf8("舒張壓:%4").arg(newAverageBpv0))
                    .arg(QString::fromUtf8("收縮壓:%5").arg(newAverageBpv1))
                    .arg(QString::fromUtf8("血糖值:%6").arg(newAverageGlu));
    }
    else if(dataSize > 4 && dataSize < 14 )
    {
        // 刪除最大和最小兩筆
          for (int i = 0; i < 1; i++) {
              S2.removeLast();
              S2.removeFirst();

              bpm.removeLast();
              bpm.removeFirst();

              LTv.removeLast();
              LTv.removeFirst();

              bpv0.removeLast();
              bpv0.removeFirst();

              bpv1.removeLast();
              bpv1.removeFirst();
          }

          // 刪除最大和最小
            glu.removeLast();

            glu.removeFirst();

            qDebug()<<"after:"<<S2 ;
            qDebug()<<"after:"<<bpm;
            qDebug()<<"after:"<<LTv;
            qDebug()<<"after:"<<bpv0;
            qDebug()<<"after:"<<bpv1;
            qDebug()<<"after:"<<glu;

          //  計算剩下數值平均
          int sum = 0;
          for (int i : S2) {
              sum += i;
          }
          int averageS2 = sum / S2.size();

          sum = 0;
          for (int i : bpm) {
              sum += i;
          }
          int averageBpm = sum / bpm.size();

          float sumLTv = 0.00 ;
          for (float i : LTv) {
              sumLTv += i;
          }
          float averageLTv = float(sumLTv / LTv.size());

          qDebug()<<"sumLTv:"<<sumLTv;
          qDebug()<<"float("<<sumLTv<<" / "<<LTv.size()<<"):"<<averageLTv;


          sum = 0;
          for (int i : bpv0) {
              sum += i;
          }
          int averageBpv0 = sum / bpv0.size();

          sum = 0;
          for (int i : bpv1) {
              sum += i;
          }
          int averageBpv1 = sum / bpv1.size();

          sum = 0;
          for (int i : glu) {
              sum += i;
          }
          int averageGlu = sum / glu.size();
          qDebug()<<"sumGlu:"<<sum;
          qDebug()<<"int("<<sum<<" / "<<glu.size()<<"):"<<averageGlu;

          qDebug()<<"after:"<<averageS2 ;
          qDebug()<<"after:"<<averageBpm;
          qDebug()<<"after:"<<averageLTv;
          qDebug()<<"after:"<<averageBpv0;
          qDebug()<<"after:"<<averageBpv1;
          qDebug()<<"after:"<<averageGlu;



            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                    .arg(QString::fromUtf8("分析統計結果:"))
                    .arg(QString::fromUtf8("血氧值:%1").arg(averageS2))
                    .arg(QString::fromUtf8("心跳:%2").arg(averageBpm))
                    .arg(QString::fromUtf8("乳酸值:%3").arg(averageLTv))
                    .arg(QString::fromUtf8("舒張壓:%4").arg(averageBpv0))
                    .arg(QString::fromUtf8("收縮壓:%5").arg(averageBpv1))
                    .arg(QString::fromUtf8("血糖值:%6").arg(averageGlu));
    }
    else if(dataSize <= 4)
    {

          //  計算剩下數值平均
          int sum = 0;
          for (int i : S2) {
              sum += i;
          }
          int averageS2 = sum / S2.size();

          sum = 0;
          for (int i : bpm) {
              sum += i;
          }
          int averageBpm = sum / bpm.size();

          float sumLTv = 0.00 ;
          for (float i : LTv) {
              sumLTv += i;
          }
          float averageLTv = float(sumLTv / LTv.size());
          qDebug()<<"sumLTv:"<<sumLTv;
          qDebug()<<"float("<<sumLTv<<" / "<<LTv.size()<<"):"<<averageLTv;

          sum = 0;
          for (int i : bpv0) {
              sum += i;
          }
          int averageBpv0 = sum / bpv0.size();

          sum = 0;
          for (int i : bpv1) {
              sum += i;
          }
          int averageBpv1 = sum / bpv1.size();

          sum = 0;
          for (int i : glu) {
              sum += i;
          }
          int averageGlu = sum / glu.size();
          qDebug()<<"sumGlu:"<<sum;
          qDebug()<<"int("<<sum<<" / "<<glu.size()<<"):"<<averageGlu;


          qDebug()<<"after:"<<averageS2 ;
          qDebug()<<"after:"<<averageBpm;
          qDebug()<<"after:"<<averageLTv;
          qDebug()<<"after:"<<averageBpv0;
          qDebug()<<"after:"<<averageBpv1;
          qDebug()<<"after:"<<averageGlu;



            returnTxt = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n")
                    .arg(QString::fromUtf8("分析統計結果:"))
                    .arg(QString::fromUtf8("血氧值:%1").arg(averageS2))
                    .arg(QString::fromUtf8("心跳:%2").arg(averageBpm))
                    .arg(QString::fromUtf8("乳酸值:%3").arg(averageLTv))
                    .arg(QString::fromUtf8("舒張壓:%4").arg(averageBpv0))
                    .arg(QString::fromUtf8("收縮壓:%5").arg(averageBpv1))
                    .arg(QString::fromUtf8("血糖值:%6").arg(averageGlu));
    }

    return returnTxt;

}

bool uploadUtility::moveFileToSelectFolder(QString file, QString folderName)
{
    QString sourceFilePath = file;

    QFileInfo srcInfo(file);

    QString targetFolderPath = QString(srcInfo.path()).append("\\").append(folderName);


    QDir targetDir(targetFolderPath);
        if (!targetDir.exists()) {
            targetDir.mkpath("."); // 建立folder
        }

        QString format ;
        if(file.contains("avi")) format = ".avi";
        else format = ".mp4";
        QString targetFilePath = targetFolderPath + "/" +srcInfo.baseName() + format;
        if (QFile::exists(targetFilePath)) {
            qDebug() << "File already exists in the target folder.";
        } else {
            if (QFile::copy(sourceFilePath, targetFilePath)) {
                qDebug() << sourceFilePath<<" moved to the "<<targetFilePath;
                if (QFile::remove(sourceFilePath)) {

                    qDebug() <<sourceFilePath << " removed.";

                } else {

                    qDebug() << "Failed to remove the original file.";

                }
            } else {
                qDebug() << "Failed to move the file.";
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
