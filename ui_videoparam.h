/********************************************************************************
** Form generated from reading UI file 'videoparam.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPARAM_H
#define UI_VIDEOPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videoParam
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_format;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radio_avi;
    QRadioButton *radio_mp4;
    QGroupBox *groupBox_expose;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radio_expose_auto;
    QRadioButton *radio_expose_4;
    QRadioButton *radio_expose_5;
    QRadioButton *radio_expose_6;
    QLabel *label_exposeValue;
    QGroupBox *groupBox_biterate;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radio_bitra_auto;
    QRadioButton *radio_bitra_2M;
    QRadioButton *radio_bitra_3M;
    QRadioButton *radio_bitra_4M;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radio_roi_crop;
    QRadioButton *radio_roi_no;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_ok;

    void setupUi(QWidget *videoParam)
    {
        if (videoParam->objectName().isEmpty())
            videoParam->setObjectName(QStringLiteral("videoParam"));
        videoParam->resize(638, 489);
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(9);
        videoParam->setFont(font);
        verticalLayout = new QVBoxLayout(videoParam);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_format = new QGroupBox(videoParam);
        groupBox_format->setObjectName(QStringLiteral("groupBox_format"));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft JhengHei UI"));
        font1.setPointSize(9);
        groupBox_format->setFont(font1);
        horizontalLayout = new QHBoxLayout(groupBox_format);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radio_avi = new QRadioButton(groupBox_format);
        radio_avi->setObjectName(QStringLiteral("radio_avi"));
        radio_avi->setFont(font1);
        radio_avi->setChecked(true);

        horizontalLayout->addWidget(radio_avi);

        radio_mp4 = new QRadioButton(groupBox_format);
        radio_mp4->setObjectName(QStringLiteral("radio_mp4"));
        radio_mp4->setFont(font1);

        horizontalLayout->addWidget(radio_mp4);


        verticalLayout->addWidget(groupBox_format);

        groupBox_expose = new QGroupBox(videoParam);
        groupBox_expose->setObjectName(QStringLiteral("groupBox_expose"));
        groupBox_expose->setFont(font1);
        horizontalLayout_6 = new QHBoxLayout(groupBox_expose);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        radio_expose_auto = new QRadioButton(groupBox_expose);
        radio_expose_auto->setObjectName(QStringLiteral("radio_expose_auto"));
        radio_expose_auto->setEnabled(false);
        radio_expose_auto->setFont(font1);

        horizontalLayout_6->addWidget(radio_expose_auto);

        radio_expose_4 = new QRadioButton(groupBox_expose);
        radio_expose_4->setObjectName(QStringLiteral("radio_expose_4"));
        radio_expose_4->setFont(font1);

        horizontalLayout_6->addWidget(radio_expose_4);

        radio_expose_5 = new QRadioButton(groupBox_expose);
        radio_expose_5->setObjectName(QStringLiteral("radio_expose_5"));
        radio_expose_5->setFont(font1);
        radio_expose_5->setChecked(true);

        horizontalLayout_6->addWidget(radio_expose_5);

        radio_expose_6 = new QRadioButton(groupBox_expose);
        radio_expose_6->setObjectName(QStringLiteral("radio_expose_6"));
        radio_expose_6->setFont(font1);

        horizontalLayout_6->addWidget(radio_expose_6);

        label_exposeValue = new QLabel(groupBox_expose);
        label_exposeValue->setObjectName(QStringLiteral("label_exposeValue"));
        label_exposeValue->setFont(font1);

        horizontalLayout_6->addWidget(label_exposeValue);


        verticalLayout->addWidget(groupBox_expose);

        groupBox_biterate = new QGroupBox(videoParam);
        groupBox_biterate->setObjectName(QStringLiteral("groupBox_biterate"));
        groupBox_biterate->setFont(font1);
        horizontalLayout_2 = new QHBoxLayout(groupBox_biterate);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radio_bitra_auto = new QRadioButton(groupBox_biterate);
        radio_bitra_auto->setObjectName(QStringLiteral("radio_bitra_auto"));
        radio_bitra_auto->setEnabled(true);
        radio_bitra_auto->setFont(font1);
        radio_bitra_auto->setChecked(true);

        horizontalLayout_2->addWidget(radio_bitra_auto);

        radio_bitra_2M = new QRadioButton(groupBox_biterate);
        radio_bitra_2M->setObjectName(QStringLiteral("radio_bitra_2M"));
        radio_bitra_2M->setFont(font1);

        horizontalLayout_2->addWidget(radio_bitra_2M);

        radio_bitra_3M = new QRadioButton(groupBox_biterate);
        radio_bitra_3M->setObjectName(QStringLiteral("radio_bitra_3M"));
        radio_bitra_3M->setFont(font1);

        horizontalLayout_2->addWidget(radio_bitra_3M);

        radio_bitra_4M = new QRadioButton(groupBox_biterate);
        radio_bitra_4M->setObjectName(QStringLiteral("radio_bitra_4M"));
        radio_bitra_4M->setFont(font1);

        horizontalLayout_2->addWidget(radio_bitra_4M);


        verticalLayout->addWidget(groupBox_biterate);

        groupBox_3 = new QGroupBox(videoParam);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font1);
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radio_roi_crop = new QRadioButton(groupBox_3);
        radio_roi_crop->setObjectName(QStringLiteral("radio_roi_crop"));
        radio_roi_crop->setFont(font1);

        horizontalLayout_3->addWidget(radio_roi_crop);

        radio_roi_no = new QRadioButton(groupBox_3);
        radio_roi_no->setObjectName(QStringLiteral("radio_roi_no"));
        radio_roi_no->setFont(font1);

        horizontalLayout_3->addWidget(radio_roi_no);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(videoParam);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setEnabled(true);
        groupBox_4->setFont(font1);
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        radioButton_7 = new QRadioButton(groupBox_4);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setFont(font1);

        horizontalLayout_4->addWidget(radioButton_7);

        radioButton_8 = new QRadioButton(groupBox_4);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));
        radioButton_8->setFont(font1);

        horizontalLayout_4->addWidget(radioButton_8);


        verticalLayout->addWidget(groupBox_4);

        line = new QFrame(videoParam);
        line->setObjectName(QStringLiteral("line"));
        line->setFont(font1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btn_ok = new QPushButton(videoParam);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));
        btn_ok->setFont(font1);

        horizontalLayout_5->addWidget(btn_ok);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(videoParam);

        QMetaObject::connectSlotsByName(videoParam);
    } // setupUi

    void retranslateUi(QWidget *videoParam)
    {
        videoParam->setWindowTitle(QApplication::translate("videoParam", "\345\275\261\347\211\207\346\240\274\345\274\217\350\250\255\345\256\232", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        videoParam->setWhatsThis(QApplication::translate("videoParam", "\345\217\257\350\250\255\345\256\232\345\275\261\347\211\207\345\204\262\345\255\230\345\217\203\346\225\270", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        groupBox_format->setTitle(QApplication::translate("videoParam", "\345\275\261\347\211\207\346\240\274\345\274\217", Q_NULLPTR));
        radio_avi->setText(QApplication::translate("videoParam", "avi", Q_NULLPTR));
        radio_mp4->setText(QApplication::translate("videoParam", "mp4", Q_NULLPTR));
        groupBox_expose->setTitle(QApplication::translate("videoParam", "\346\233\235\345\205\211\345\272\246", Q_NULLPTR));
        radio_expose_auto->setText(QApplication::translate("videoParam", "AUTO", Q_NULLPTR));
        radio_expose_4->setText(QApplication::translate("videoParam", "-4", Q_NULLPTR));
        radio_expose_5->setText(QApplication::translate("videoParam", "-5", Q_NULLPTR));
        radio_expose_6->setText(QApplication::translate("videoParam", "-6", Q_NULLPTR));
        label_exposeValue->setText(QString());
        groupBox_biterate->setTitle(QApplication::translate("videoParam", "Biterate\357\274\210\357\274\255\357\274\242\357\274\211", Q_NULLPTR));
        radio_bitra_auto->setText(QApplication::translate("videoParam", "AUTO", Q_NULLPTR));
        radio_bitra_2M->setText(QApplication::translate("videoParam", "2", Q_NULLPTR));
        radio_bitra_3M->setText(QApplication::translate("videoParam", "3", Q_NULLPTR));
        radio_bitra_4M->setText(QApplication::translate("videoParam", "4", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("videoParam", "ROI\346\217\220\345\217\226", Q_NULLPTR));
        radio_roi_crop->setText(QApplication::translate("videoParam", "\350\207\252\345\213\225", Q_NULLPTR));
        radio_roi_no->setText(QApplication::translate("videoParam", "\346\211\213\345\213\225", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("videoParam", "\345\275\261\347\211\207\345\210\207\345\211\262", Q_NULLPTR));
        radioButton_7->setText(QApplication::translate("videoParam", "3S", Q_NULLPTR));
        radioButton_8->setText(QApplication::translate("videoParam", "overlap 2S", Q_NULLPTR));
        btn_ok->setText(QApplication::translate("videoParam", "\347\242\272\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class videoParam: public Ui_videoParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPARAM_H
