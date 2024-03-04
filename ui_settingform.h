/********************************************************************************
** Form generated from reading UI file 'settingform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_server;
    QPushButton *btn_editServerURL;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pwd;
    QPushButton *btn_editPwd;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_param;
    QPushButton *btn_editParam;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_timeout;
    QPushButton *btn_editTimeout;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_closeSet;

    void setupUi(QDialog *SettingForm)
    {
        if (SettingForm->objectName().isEmpty())
            SettingForm->setObjectName(QStringLiteral("SettingForm"));
        SettingForm->setWindowModality(Qt::NonModal);
        SettingForm->resize(654, 307);
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(9);
        SettingForm->setFont(font);
        verticalLayout_3 = new QVBoxLayout(SettingForm);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_2 = new QGroupBox(SettingForm);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft JhengHei UI"));
        font1.setPointSize(9);
        groupBox_2->setFont(font1);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEdit_server = new QLineEdit(groupBox_2);
        lineEdit_server->setObjectName(QStringLiteral("lineEdit_server"));
        lineEdit_server->setFont(font);

        horizontalLayout->addWidget(lineEdit_server);

        btn_editServerURL = new QPushButton(groupBox_2);
        btn_editServerURL->setObjectName(QStringLiteral("btn_editServerURL"));
        btn_editServerURL->setFont(font1);

        horizontalLayout->addWidget(btn_editServerURL);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_pwd = new QLineEdit(groupBox_2);
        lineEdit_pwd->setObjectName(QStringLiteral("lineEdit_pwd"));
        lineEdit_pwd->setFont(font);
        lineEdit_pwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_pwd);

        btn_editPwd = new QPushButton(groupBox_2);
        btn_editPwd->setObjectName(QStringLiteral("btn_editPwd"));
        btn_editPwd->setFont(font1);

        horizontalLayout_2->addWidget(btn_editPwd);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        lineEdit_param = new QLineEdit(groupBox_2);
        lineEdit_param->setObjectName(QStringLiteral("lineEdit_param"));
        lineEdit_param->setFont(font);

        horizontalLayout_3->addWidget(lineEdit_param);

        btn_editParam = new QPushButton(groupBox_2);
        btn_editParam->setObjectName(QStringLiteral("btn_editParam"));
        btn_editParam->setFont(font1);

        horizontalLayout_3->addWidget(btn_editParam);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox = new QGroupBox(SettingForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        horizontalLayout_4->addWidget(label_4);

        lineEdit_timeout = new QLineEdit(groupBox);
        lineEdit_timeout->setObjectName(QStringLiteral("lineEdit_timeout"));
        lineEdit_timeout->setFont(font);

        horizontalLayout_4->addWidget(lineEdit_timeout);

        btn_editTimeout = new QPushButton(groupBox);
        btn_editTimeout->setObjectName(QStringLiteral("btn_editTimeout"));
        btn_editTimeout->setFont(font1);

        horizontalLayout_4->addWidget(btn_editTimeout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btn_closeSet = new QPushButton(SettingForm);
        btn_closeSet->setObjectName(QStringLiteral("btn_closeSet"));
        btn_closeSet->setFont(font1);

        horizontalLayout_5->addWidget(btn_closeSet);


        verticalLayout_3->addLayout(horizontalLayout_5);


        retranslateUi(SettingForm);

        QMetaObject::connectSlotsByName(SettingForm);
    } // setupUi

    void retranslateUi(QDialog *SettingForm)
    {
        SettingForm->setWindowTitle(QApplication::translate("SettingForm", "\344\270\212\345\202\263\350\250\255\345\256\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SettingForm", "\344\274\272\346\234\215\345\231\250\350\250\255\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("SettingForm", "\344\274\272\346\234\215\345\231\250", Q_NULLPTR));
        lineEdit_server->setText(QString());
        btn_editServerURL->setText(QApplication::translate("SettingForm", "\344\277\256\346\224\271", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingForm", "\345\257\206\347\242\274", Q_NULLPTR));
        lineEdit_pwd->setText(QString());
        btn_editPwd->setText(QApplication::translate("SettingForm", "\344\277\256\346\224\271", Q_NULLPTR));
        label_3->setText(QApplication::translate("SettingForm", "\345\217\203\346\225\270", Q_NULLPTR));
        lineEdit_param->setText(QString());
        btn_editParam->setText(QApplication::translate("SettingForm", "\344\277\256\346\224\271", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SettingForm", "Timeout \350\250\255\345\256\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("SettingForm", "\344\270\212\345\202\263timeout", Q_NULLPTR));
        btn_editTimeout->setText(QApplication::translate("SettingForm", "\344\277\256\346\224\271", Q_NULLPTR));
        btn_closeSet->setText(QApplication::translate("SettingForm", "\351\227\234\351\226\211", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingForm: public Ui_SettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
