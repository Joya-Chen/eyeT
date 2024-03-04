#include "videoparam.h"
#include "ui_videoparam.h"
#include <QDebug>
videoParam::videoParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videoParam)
{
    ui->setupUi(this);

    ui->groupBox_biterate->setVisible(false);
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);


}

videoParam::~videoParam()
{
    delete ui;
}

void videoParam::setDefaultValue(QString file_Code, int expose_value, int bite_rate)
{
    if(file_Code == "avi")
        ui->radio_avi->setCheckable(true);
    else
        ui->radio_mp4->setChecked(true);
    //-------------------------------------------//
    if(expose_value == 1)
        ui->radio_expose_auto->setChecked(true);
    else if(expose_value == -4)
        ui->radio_expose_4->setChecked(true);
    else if(expose_value == -5)
        ui->radio_expose_5->setChecked(true);
    else if(expose_value == -6)
        ui->radio_expose_6->setChecked(true);
    //-------------------------------------------//
    if(bite_rate == 0)
        ui->radio_bitra_auto->setChecked(true);
    else if(bite_rate == 2)
        ui->radio_bitra_2M->setChecked(true);
    else if(bite_rate == 3)
        ui->radio_bitra_3M->setChecked(true);
    else if(bite_rate == 4)
        ui->radio_bitra_4M->setChecked(true);
    //-------------------------------------------//
    this->setFileCode(file_Code);
    this->setExposeValue(expose_value);
    this->setBiterate(bite_rate);
}

QString videoParam::getFileCode()
{
    return m_video_format;
}

int videoParam::getExposeValue()
{
    return m_expose_value;
}

int videoParam::getBiterate()
{
    return m_biterate;
}

void videoParam::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type())
        {
           case QEvent::LanguageChange:
                qDebug()<<"videoParam::LanguageChange";
                //ui->retranslateUi(this);
                //還有其他手工更新界面的內容
            break;
           default:
            break;
        }
}

void videoParam::setFileCode(QString file_Code)
{
    m_video_format = file_Code;
}

void videoParam::setExposeValue(int expose_value)
{
    m_expose_value = expose_value;
}

void videoParam::setBiterate(int bite_rate)
{
    m_biterate = bite_rate;
}

void videoParam::on_btn_ok_clicked()
{
    QString format ;
    QString expose_value;
    QString bitrate;
    //
    foreach (QRadioButton *radioButton, ui->groupBox_format->findChildren<QRadioButton*>()) {
        if (radioButton->isChecked()) {
           format = radioButton->text();
            // 使用value做進一步的處理
        }
    }
    foreach (QRadioButton *radioButton, ui->groupBox_expose->findChildren<QRadioButton*>()) {
        if (radioButton->isChecked()) {
           expose_value = radioButton->text();
            // 使用value做進一步的處理
        }
    }
    foreach (QRadioButton *radioButton, ui->groupBox_biterate->findChildren<QRadioButton*>()) {
        if (radioButton->isChecked()) {
           bitrate = radioButton->text();
            // 使用value做進一步的處理
        }
    }
    qDebug()<<"format:"<<format<<", expose_value:"<<expose_value<<", bitrate:"<<bitrate;

    if(expose_value == "AUTO") expose_value = "1";
    if(bitrate == "AUTO") bitrate = "0";

    emit paramUpdate(format, expose_value.toInt(), bitrate.toInt() );

    this->setFileCode(format);
    this->setExposeValue(expose_value.toInt());
    this->setBiterate(bitrate.toInt());
    QWidget::close();
}

void videoParam::initialCameraParam()
{

}
