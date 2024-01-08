#include "dialog.h"
#include "ui_dialog.h"

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

void Dialog::on_btn_ok_clicked()
{
    QWidget::close();
}
