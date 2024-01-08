#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QDialog>

namespace Ui {
class SettingForm;
}

class SettingForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = 0);
    ~SettingForm();

    void setDefault(QString url, QString pwd, QString dataInfo, int timeout);

signals:
    void paramUpdate(QString url, QString pwd, QString dataInfo, int timeout);

private slots:


    void on_btn_closeSet_clicked();

    void on_btn_editServerURL_clicked();

    void on_btn_editPwd_clicked();

    void on_btn_editParam_clicked();



    void on_btn_editTimeout_clicked();

private:
    Ui::SettingForm *ui;
    void initialParam();
};

#endif // SETTINGFORM_H
