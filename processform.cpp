#include "processform.h"
#include "ui_processform.h"
#include <QMovie>
#include <QDebug>
processForm::processForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::processForm)
{
    ui->setupUi(this);

    QMovie* movie = new QMovie("Loading.gif");

    // Make sure the GIF was loaded correctly
    if (!movie->isValid())
    {
        qDebug()<<"movie->isInValid()";
    }
    // Play GIF
    ui->label_gif->setMovie(movie);
    movie->start();
}

processForm::~processForm()
{
    delete ui;
}

void processForm::setHintText(QString hintText)
{
    ui->label_hintText->setText(hintText);

}

void processForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
        switch (e->type())
        {
           case QEvent::LanguageChange:
                qDebug()<<"processForm::LanguageChange";
                //ui->retranslateUi(this);
                //還有其他手工更新界面的內容
            break;
           default:
            break;
        }
}
