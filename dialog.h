#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setVersion(QString version);
protected:
    void changeEvent(QEvent *e) override;

private slots:
    void on_btn_ok_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
