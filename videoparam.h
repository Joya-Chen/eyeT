#ifndef VIDEOPARAM_H
#define VIDEOPARAM_H

#include <QWidget>

namespace Ui {
class videoParam;
}

class videoParam : public QWidget
{
    Q_OBJECT

public:
    explicit videoParam(QWidget *parent = 0);
    ~videoParam();

private:
    Ui::videoParam *ui;
};

#endif // VIDEOPARAM_H
