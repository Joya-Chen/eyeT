#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);

    QApplication a(argc, argv);

    MainWindow w;

    QFont font("微軟正黑體",12);

    w.setFont(font);

    w.show();

    a.setWindowIcon(QIcon("./deepicon.png"));

    return a.exec();
}
