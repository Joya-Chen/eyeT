#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile logFile("./log.txt");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&logFile);
        switch (type) {
        case QtDebugMsg:
            stream << "Debug: " << msg << endl;
            break;
        case QtInfoMsg:
            stream << "Info: " << msg << endl;
            break;
        case QtWarningMsg:
            stream << "Warning: " << msg << endl;
            break;
        case QtCriticalMsg:
            stream << "Critical: " << msg << endl;
            break;
        case QtFatalMsg:
            stream << "Fatal: " << msg << endl;
            abort();
        }
    }
}

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
#ifdef SELF_TEST
    qInstallMessageHandler(customMessageHandler);
#endif
    QApplication a(argc, argv);


    if (CLS_GLOBAL::translator != NULL)
    {
        qApp->removeTranslator(CLS_GLOBAL::translator);
        delete CLS_GLOBAL::translator;
        CLS_GLOBAL::translator = NULL;
    }
    CLS_GLOBAL::translator = new QTranslator;
    CLS_GLOBAL::translator->load("./Language/eyeT_en.qm");
    a.installTranslator(CLS_GLOBAL::translator);

    MainWindow w;

    //QFont font("Roboto",9);

    //w.setFont(font);

    w.setAttribute(Qt::WA_DeleteOnClose);

    w.show();

    a.setWindowIcon(QIcon("./deepicon.png"));

    int result = a.exec();

    a.quit();

    return result;
}
