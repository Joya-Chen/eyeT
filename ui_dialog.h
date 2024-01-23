/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *btn_ok;
    QLabel *label;
    QLabel *label_version;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(431, 276);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(10);
        font.setStyleStrategy(QFont::PreferAntialias);
        Dialog->setFont(font);
        Dialog->setContextMenuPolicy(Qt::DefaultContextMenu);
        btn_ok = new QPushButton(Dialog);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));
        btn_ok->setGeometry(QRect(340, 219, 80, 41));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 311, 51));
        label->setPixmap(QPixmap(QString::fromUtf8(":/deepLogo_s.png")));
        label_version = new QLabel(Dialog);
        label_version->setObjectName(QStringLiteral("label_version"));
        label_version->setGeometry(QRect(20, 90, 391, 111));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\351\227\234\346\226\274eyeAnalysis", Q_NULLPTR));
        btn_ok->setText(QApplication::translate("Dialog", "OK", Q_NULLPTR));
        label->setText(QString());
        label_version->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
