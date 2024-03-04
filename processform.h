#ifndef PROCESSFORM_H
#define PROCESSFORM_H

#include <QWidget>

namespace Ui {
class processForm;
}

class processForm : public QWidget
{
    Q_OBJECT

public:
    explicit processForm(QWidget *parent = 0);
    ~processForm();

    void setHintText(QString hintText);

protected:
    void changeEvent(QEvent *e) override;

private:
    Ui::processForm *ui;
};

#endif // PROCESSFORM_H
