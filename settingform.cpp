#include "settingform.h"
#include "ui_settingform.h"
#include <QMessageBox>
#include <QDebug>
SettingForm::SettingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);

    this->initialParam();
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::setDefault(QString url, QString pwd, QString dataInfo, int timeout)
{
    qDebug()<<"SettingForm :"<<"url:"<<url<<"pwd:"<<pwd<<"dataInfo:"<<dataInfo<<"timeout:"<<timeout;
    ui->lineEdit_server->setText(url);
    ui->lineEdit_pwd->setText(pwd);
    ui->lineEdit_param->setText(dataInfo);
    ui->lineEdit_timeout->setText(QString::number(timeout));
}

void SettingForm::on_btn_closeSet_clicked()
{
    //qDebug()<<ui->lineEdit_server->text()<<ui->lineEdit_pwd->text()<<ui->lineEdit_param->text()<<ui->lineEdit_timeout->text();
    if(ui->lineEdit_server->text()=="" ||
            ui->lineEdit_pwd->text()=="" ||
            ui->lineEdit_param->text()=="" ||
            ui->lineEdit_timeout->text() == "")
    {
        QMessageBox::information(this,tr("Info"),tr("請確認設定內容不能空白"),QMessageBox::Ok);

        return;
    }

    //qDebug()<<ui->btn_editServerURL->text()<<ui->btn_editPwd->text()<<ui->btn_editParam->text()<<ui->btn_editTimeout->text();

    if(ui->btn_editServerURL->text()=="確定" ||
            ui->btn_editPwd->text()=="確定" ||
            ui->btn_editParam->text()=="確定" ||
            ui->btn_editTimeout->text()=="確定" )
    {
        QMessageBox::information(this,tr("Info"),tr("修改後需按下確定"),QMessageBox::Ok);

        return;
    }

    emit paramUpdate(ui->lineEdit_server->text(),ui->lineEdit_pwd->text(),ui->lineEdit_param->text(),ui->lineEdit_timeout->text().toInt());

    QWidget::close();
}

void SettingForm::initialParam()
{
    ui->lineEdit_server->setReadOnly(true);
    ui->lineEdit_pwd->setReadOnly(true);
    ui->lineEdit_param->setReadOnly(true);
    ui->lineEdit_timeout->setReadOnly(true);
}

void SettingForm::on_btn_editServerURL_clicked()
{
    if(ui->btn_editServerURL->text()=="修改"){
        ui->lineEdit_server->setReadOnly(false);
        ui->btn_editServerURL->setText("確定");
    }
    else{
        ui->lineEdit_server->setReadOnly(true);
        ui->btn_editServerURL->setText("修改");
    }

}

void SettingForm::on_btn_editPwd_clicked()
{
    if(ui->btn_editPwd->text()=="修改"){
        ui->lineEdit_pwd->setReadOnly(false);
        ui->btn_editPwd->setText("確定");
    }
    else{
        ui->lineEdit_pwd->setReadOnly(true);
        ui->btn_editPwd->setText("修改");
    }
}

void SettingForm::on_btn_editParam_clicked()
{
    if(ui->btn_editParam->text()=="修改"){
        ui->lineEdit_param->setReadOnly(false);
        ui->btn_editPwd->setText("確定");
    }
    else{
        ui->lineEdit_param->setReadOnly(true);
        ui->btn_editParam->setText("修改");
    }
}

void SettingForm::on_btn_editTimeout_clicked()
{
    if(ui->btn_editTimeout->text()=="修改"){
        ui->lineEdit_timeout->setReadOnly(false);
        ui->btn_editTimeout->setText("確定");
    }
    else{
        ui->lineEdit_timeout->setReadOnly(true);
        ui->btn_editTimeout->setText("修改");
    }
}
