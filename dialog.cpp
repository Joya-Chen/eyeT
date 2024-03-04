#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setVersion(QString version)
{
    ui->label->setText(version);
}

void Dialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type())
        {
           case QEvent::LanguageChange:
                qDebug()<<"dialog::LanguageChange";
                //ui->retranslateUi(this);
                //還有其他手工更新界面的內容
            break;
           default:
            break;
        }
}
void Dialog::on_btn_ok_clicked()
{
    QWidget::close();
}
