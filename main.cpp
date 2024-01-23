#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

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

    MainWindow w;

    QFont font("微軟正黑體",12);

    w.setFont(font);

    w.show();

    a.setWindowIcon(QIcon("./deepicon.png"));

    return a.exec();
}
