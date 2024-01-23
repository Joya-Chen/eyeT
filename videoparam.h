#ifndef VIDEOPARAM_H
#define VIDEOPARAM_H

#include <QDialog>

namespace Ui {
class videoParam;
}

class videoParam : public QDialog
{
    Q_OBJECT

public:
    explicit videoParam(QWidget *parent = 0);
    ~videoParam();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::videoParam *ui;
};

#endif // VIDEOPARAM_H
