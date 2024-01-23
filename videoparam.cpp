#include "videoparam.h"
#include "ui_videoparam.h"

videoParam::videoParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoParam)
{
    ui->setupUi(this);
}

videoParam::~videoParam()
{
    delete ui;
}
