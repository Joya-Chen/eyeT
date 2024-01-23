#include "videoparam.h"
#include "ui_videoparam.h"

videoParam::videoParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoParam)
{
    ui->setupUi(this);
}

videoParam::~videoParam()
{
    delete ui;
}

void videoParam::on_btn_ok_clicked()
{
    QWidget::close();
}
