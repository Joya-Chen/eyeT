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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radio_avi;
    QRadioButton *radio_mp4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
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
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        videoParam->setFont(font);
        verticalLayout = new QVBoxLayout(videoParam);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(videoParam);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radio_avi = new QRadioButton(groupBox);
        radio_avi->setObjectName(QStringLiteral("radio_avi"));

        horizontalLayout->addWidget(radio_avi);

        radio_mp4 = new QRadioButton(groupBox);
        radio_mp4->setObjectName(QStringLiteral("radio_mp4"));

        horizontalLayout->addWidget(radio_mp4);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(videoParam);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        horizontalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        horizontalLayout_2->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        horizontalLayout_2->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(groupBox_2);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));

        horizontalLayout_2->addWidget(radioButton_6);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(videoParam);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox = new QCheckBox(groupBox_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_3->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(videoParam);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        radioButton_7 = new QRadioButton(groupBox_4);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));

        horizontalLayout_4->addWidget(radioButton_7);

        radioButton_8 = new QRadioButton(groupBox_4);
        radioButton_8->setObjectName(QStringLiteral("radioButton_8"));

        horizontalLayout_4->addWidget(radioButton_8);


        verticalLayout->addWidget(groupBox_4);

        line = new QFrame(videoParam);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btn_ok = new QPushButton(videoParam);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));

        horizontalLayout_5->addWidget(btn_ok);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(videoParam);

        QMetaObject::connectSlotsByName(videoParam);
    } // setupUi

    void retranslateUi(QWidget *videoParam)
    {
        videoParam->setWindowTitle(QApplication::translate("videoParam", "Form", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        videoParam->setWhatsThis(QApplication::translate("videoParam", "\345\217\257\350\250\255\345\256\232\345\275\261\347\211\207\345\204\262\345\255\230\345\217\203\346\225\270", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("videoParam", "\345\275\261\347\211\207\346\240\274\345\274\217", Q_NULLPTR));
        radio_avi->setText(QApplication::translate("videoParam", "avi", Q_NULLPTR));
        radio_mp4->setText(QApplication::translate("videoParam", "mp4", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("videoParam", "Biterate", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("videoParam", "\344\270\215\351\231\220\345\210\266", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("videoParam", "2M", Q_NULLPTR));
        radioButton_5->setText(QApplication::translate("videoParam", "3M", Q_NULLPTR));
        radioButton_6->setText(QApplication::translate("videoParam", "4M", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("videoParam", "ROI\346\217\220\345\217\226", Q_NULLPTR));
        checkBox->setText(QApplication::translate("videoParam", "\344\270\215\346\217\220\345\217\226", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("videoParam", "\346\217\220\345\217\226", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("videoParam", "\345\204\262\345\255\230\350\250\255\345\256\232", Q_NULLPTR));
        radioButton_7->setText(QApplication::translate("videoParam", "\344\277\235\347\225\231\346\257\217\345\200\213\345\275\261\347\211\207", Q_NULLPTR));
        radioButton_8->setText(QApplication::translate("videoParam", "\345\203\205\344\277\235\347\225\231\345\267\246\347\234\274\345\217\263\347\234\274\345\220\204\344\270\200", Q_NULLPTR));
        btn_ok->setText(QApplication::translate("videoParam", "\347\242\272\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class videoParam: public Ui_videoParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPARAM_H
