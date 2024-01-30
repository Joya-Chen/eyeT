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
    void setDefaultValue(QString file_Code, int expose_value, int bite_rate);
    QString getFileCode();
    int getExposeValue();
    int getBiterate();
signals:
    void paramUpdate(QString file_Code, int expose_value, int bite_rate);

private slots:
    void on_btn_ok_clicked();


private:
    Ui::videoParam *ui;
    void initialCameraParam();
    void setFileCode(QString file_Code);
    void setExposeValue(int expose_value);
    void setBiterate(int bite_rate);
    QString m_video_format;
    int m_expose_value;
    int m_biterate;
};

#endif // VIDEOPARAM_H
