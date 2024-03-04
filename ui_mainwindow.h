/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action30s;
    QAction *action_about;
    QAction *action10s_2;
    QAction *action20s_2;
    QAction *action30s_2;
    QAction *action_default;
    QAction *action_set;
    QAction *action_upload_set;
    QAction *actio_video_set;
    QAction *actionchinese;
    QAction *actionEnglish;
    QAction *actionShowDetail;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox_camList;
    QPushButton *btnRefresh;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_camName;
    QPushButton *btnEditCamName;
    QLabel *right_label;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QTextEdit *textEdit_testerNo;
    QPushButton *btnBuildTester;
    QPushButton *btnCameraStart_r;
    QPushButton *btnCameraStart_l;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_showInfo;
    QPushButton *btn_cancelWriteVideo;
    QPushButton *btn_tester_finish;
    QPushButton *btnOpenFolder;
    QPushButton *btnVideoSelUpload;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *txtShow;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_logo;
    QLabel *label_version;
    QPushButton *btnCameraStart;
    QPushButton *btnCameraStop;
    QPushButton *btnVideoSetting;
    QPushButton *btnVideoSelTest;
    QPushButton *btnROINUpload;
    QPushButton *btn_roiAuto;
    QPushButton *btnVideoSeltoCanny;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1246, 928);
        MainWindow->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft JhengHei UI"));
        font.setPointSize(9);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/deepicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setIconSize(QSize(453, 106));
        action30s = new QAction(MainWindow);
        action30s->setObjectName(QStringLiteral("action30s"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        action_about->setIcon(icon);
        action_about->setFont(font);
        action10s_2 = new QAction(MainWindow);
        action10s_2->setObjectName(QStringLiteral("action10s_2"));
        action20s_2 = new QAction(MainWindow);
        action20s_2->setObjectName(QStringLiteral("action20s_2"));
        action30s_2 = new QAction(MainWindow);
        action30s_2->setObjectName(QStringLiteral("action30s_2"));
        action_default = new QAction(MainWindow);
        action_default->setObjectName(QStringLiteral("action_default"));
        action_set = new QAction(MainWindow);
        action_set->setObjectName(QStringLiteral("action_set"));
        action_upload_set = new QAction(MainWindow);
        action_upload_set->setObjectName(QStringLiteral("action_upload_set"));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        action_upload_set->setFont(font1);
        actio_video_set = new QAction(MainWindow);
        actio_video_set->setObjectName(QStringLiteral("actio_video_set"));
        actio_video_set->setEnabled(true);
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(9);
        actio_video_set->setFont(font2);
        actionchinese = new QAction(MainWindow);
        actionchinese->setObjectName(QStringLiteral("actionchinese"));
        actionchinese->setCheckable(false);
        actionchinese->setFont(font);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionEnglish->setCheckable(false);
        actionEnglish->setFont(font);
        actionShowDetail = new QAction(MainWindow);
        actionShowDetail->setObjectName(QStringLiteral("actionShowDetail"));
        actionShowDetail->setCheckable(false);
        actionShowDetail->setFont(font2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(632, 30));
        label->setMaximumSize(QSize(632, 30));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        label->setFont(font3);

        verticalLayout->addWidget(label);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        comboBox_camList = new QComboBox(centralWidget);
        comboBox_camList->setObjectName(QStringLiteral("comboBox_camList"));
        comboBox_camList->setEnabled(true);
        comboBox_camList->setMinimumSize(QSize(0, 30));
        QFont font4;
        font4.setFamily(QStringLiteral("Segoe UI"));
        font4.setPointSize(9);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        comboBox_camList->setFont(font4);
        comboBox_camList->setEditable(false);

        horizontalLayout_5->addWidget(comboBox_camList);

        btnRefresh = new QPushButton(centralWidget);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));
        btnRefresh->setMinimumSize(QSize(90, 30));
        btnRefresh->setMaximumSize(QSize(90, 30));
        btnRefresh->setFont(font4);

        horizontalLayout_5->addWidget(btnRefresh);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_camName = new QLineEdit(centralWidget);
        lineEdit_camName->setObjectName(QStringLiteral("lineEdit_camName"));
        lineEdit_camName->setEnabled(true);
        lineEdit_camName->setMinimumSize(QSize(0, 30));
        QFont font5;
        font5.setFamily(QStringLiteral("Segoe UI"));
        font5.setPointSize(9);
        font5.setItalic(false);
        lineEdit_camName->setFont(font5);

        horizontalLayout->addWidget(lineEdit_camName);

        btnEditCamName = new QPushButton(centralWidget);
        btnEditCamName->setObjectName(QStringLiteral("btnEditCamName"));
        btnEditCamName->setMinimumSize(QSize(90, 30));
        btnEditCamName->setFont(font4);

        horizontalLayout->addWidget(btnEditCamName);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        right_label = new QLabel(centralWidget);
        right_label->setObjectName(QStringLiteral("right_label"));
        right_label->setMinimumSize(QSize(640, 480));
        right_label->setMaximumSize(QSize(640, 480));
        right_label->setBaseSize(QSize(640, 480));

        verticalLayout_2->addWidget(right_label);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(40, 50));
        label_2->setMaximumSize(QSize(100, 50));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial Black"));
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setWeight(75);
        label_2->setFont(font6);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_2);

        textEdit_testerNo = new QTextEdit(centralWidget);
        textEdit_testerNo->setObjectName(QStringLiteral("textEdit_testerNo"));
        textEdit_testerNo->setMinimumSize(QSize(260, 35));
        textEdit_testerNo->setMaximumSize(QSize(200, 35));
        QFont font7;
        font7.setFamily(QStringLiteral("Segoe UI"));
        font7.setPointSize(9);
        font7.setBold(false);
        font7.setWeight(50);
        font7.setKerning(true);
        font7.setStyleStrategy(QFont::PreferAntialias);
        textEdit_testerNo->setFont(font7);
        textEdit_testerNo->setLayoutDirection(Qt::LeftToRight);
        textEdit_testerNo->setFrameShape(QFrame::Box);
        textEdit_testerNo->setFrameShadow(QFrame::Plain);

        horizontalLayout_4->addWidget(textEdit_testerNo);

        btnBuildTester = new QPushButton(centralWidget);
        btnBuildTester->setObjectName(QStringLiteral("btnBuildTester"));
        btnBuildTester->setMinimumSize(QSize(90, 35));
        btnBuildTester->setFont(font1);

        horizontalLayout_4->addWidget(btnBuildTester);

        btnCameraStart_r = new QPushButton(centralWidget);
        btnCameraStart_r->setObjectName(QStringLiteral("btnCameraStart_r"));
        btnCameraStart_r->setMinimumSize(QSize(90, 35));
        btnCameraStart_r->setFont(font1);

        horizontalLayout_4->addWidget(btnCameraStart_r);

        btnCameraStart_l = new QPushButton(centralWidget);
        btnCameraStart_l->setObjectName(QStringLiteral("btnCameraStart_l"));
        btnCameraStart_l->setMinimumSize(QSize(90, 35));
        btnCameraStart_l->setFont(font1);

        horizontalLayout_4->addWidget(btnCameraStart_l);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_showInfo = new QLabel(centralWidget);
        label_showInfo->setObjectName(QStringLiteral("label_showInfo"));
        label_showInfo->setMinimumSize(QSize(308, 35));
        label_showInfo->setMaximumSize(QSize(308, 35));
        label_showInfo->setFont(font1);
        label_showInfo->setMidLineWidth(0);
        label_showInfo->setScaledContents(false);
        label_showInfo->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_showInfo);

        btn_cancelWriteVideo = new QPushButton(centralWidget);
        btn_cancelWriteVideo->setObjectName(QStringLiteral("btn_cancelWriteVideo"));
        btn_cancelWriteVideo->setMinimumSize(QSize(90, 35));
        btn_cancelWriteVideo->setFont(font1);

        horizontalLayout_3->addWidget(btn_cancelWriteVideo);

        btn_tester_finish = new QPushButton(centralWidget);
        btn_tester_finish->setObjectName(QStringLiteral("btn_tester_finish"));
        btn_tester_finish->setMinimumSize(QSize(90, 35));
        btn_tester_finish->setFont(font1);

        horizontalLayout_3->addWidget(btn_tester_finish);

        btnOpenFolder = new QPushButton(centralWidget);
        btnOpenFolder->setObjectName(QStringLiteral("btnOpenFolder"));
        btnOpenFolder->setMinimumSize(QSize(90, 35));
        btnOpenFolder->setFont(font1);

        horizontalLayout_3->addWidget(btnOpenFolder);

        btnVideoSelUpload = new QPushButton(centralWidget);
        btnVideoSelUpload->setObjectName(QStringLiteral("btnVideoSelUpload"));
        btnVideoSelUpload->setMinimumSize(QSize(90, 35));
        btnVideoSelUpload->setFont(font1);

        horizontalLayout_3->addWidget(btnVideoSelUpload);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout_4);

        txtShow = new QPlainTextEdit(centralWidget);
        txtShow->setObjectName(QStringLiteral("txtShow"));
        txtShow->setFont(font2);

        horizontalLayout_6->addWidget(txtShow);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_logo = new QLabel(centralWidget);
        label_logo->setObjectName(QStringLiteral("label_logo"));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/deepLogo_s.png")));
        label_logo->setScaledContents(true);

        horizontalLayout_2->addWidget(label_logo);

        label_version = new QLabel(centralWidget);
        label_version->setObjectName(QStringLiteral("label_version"));
        QPalette palette;
        QBrush brush(QColor(90, 90, 90, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_version->setPalette(palette);
        QFont font8;
        font8.setFamily(QStringLiteral("Segoe UI"));
        font8.setPointSize(8);
        font8.setBold(false);
        font8.setItalic(true);
        font8.setWeight(50);
        label_version->setFont(font8);
        label_version->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_version);

        btnCameraStart = new QPushButton(centralWidget);
        btnCameraStart->setObjectName(QStringLiteral("btnCameraStart"));
        btnCameraStart->setEnabled(true);
        btnCameraStart->setFont(font2);

        horizontalLayout_2->addWidget(btnCameraStart);

        btnCameraStop = new QPushButton(centralWidget);
        btnCameraStop->setObjectName(QStringLiteral("btnCameraStop"));
        btnCameraStop->setFont(font2);

        horizontalLayout_2->addWidget(btnCameraStop);

        btnVideoSetting = new QPushButton(centralWidget);
        btnVideoSetting->setObjectName(QStringLiteral("btnVideoSetting"));
        btnVideoSetting->setEnabled(true);
        btnVideoSetting->setFont(font2);

        horizontalLayout_2->addWidget(btnVideoSetting);

        btnVideoSelTest = new QPushButton(centralWidget);
        btnVideoSelTest->setObjectName(QStringLiteral("btnVideoSelTest"));
        btnVideoSelTest->setEnabled(true);
        btnVideoSelTest->setFont(font2);

        horizontalLayout_2->addWidget(btnVideoSelTest);

        btnROINUpload = new QPushButton(centralWidget);
        btnROINUpload->setObjectName(QStringLiteral("btnROINUpload"));
        btnROINUpload->setEnabled(true);
        btnROINUpload->setFont(font2);

        horizontalLayout_2->addWidget(btnROINUpload);

        btn_roiAuto = new QPushButton(centralWidget);
        btn_roiAuto->setObjectName(QStringLiteral("btn_roiAuto"));
        btn_roiAuto->setMinimumSize(QSize(0, 0));
        btn_roiAuto->setFont(font2);

        horizontalLayout_2->addWidget(btn_roiAuto);

        btnVideoSeltoCanny = new QPushButton(centralWidget);
        btnVideoSeltoCanny->setObjectName(QStringLiteral("btnVideoSeltoCanny"));
        btnVideoSeltoCanny->setEnabled(true);
        btnVideoSeltoCanny->setFont(font2);

        horizontalLayout_2->addWidget(btnVideoSeltoCanny);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_5, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1246, 26));
        menuBar->setFont(font2);
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu->setFont(font1);
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_2->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menu_2->sizePolicy().hasHeightForWidth());
        menu_2->setSizePolicy(sizePolicy);
        menu_2->setFont(font2);
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_3->setFont(font2);
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_4->setFont(font2);
        menu_5 = new QMenu(menu_4);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_5->setFont(font2);
        menu_6 = new QMenu(menu_4);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        menu_6->setFont(font2);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFont(font2);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setFont(font2);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action_upload_set);
        menu_2->addAction(actio_video_set);
        menu_3->addAction(action_about);
        menu_4->addAction(menu_5->menuAction());
        menu_4->addAction(menu_6->menuAction());
        menu_5->addAction(actionchinese);
        menu_5->addAction(actionEnglish);
        menu_6->addAction(actionShowDetail);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EyeAnalysis", Q_NULLPTR));
        action30s->setText(QApplication::translate("MainWindow", "30s", Q_NULLPTR));
        action_about->setText(QApplication::translate("MainWindow", " \351\227\234\346\226\274eyeAnalysis", Q_NULLPTR));
        action10s_2->setText(QApplication::translate("MainWindow", "10s", Q_NULLPTR));
        action20s_2->setText(QApplication::translate("MainWindow", "20s", Q_NULLPTR));
        action30s_2->setText(QApplication::translate("MainWindow", "30s", Q_NULLPTR));
        action_default->setText(QApplication::translate("MainWindow", "\351\240\220\350\250\255", Q_NULLPTR));
        action_set->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236", Q_NULLPTR));
        action_set->setIconText(QApplication::translate("MainWindow", "\344\277\256\346\224\271", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_set->setToolTip(QApplication::translate("MainWindow", "\344\277\256\346\224\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_upload_set->setText(QApplication::translate("MainWindow", "\350\250\255\345\256\232", Q_NULLPTR));
        actio_video_set->setText(QApplication::translate("MainWindow", "\350\250\255\345\256\232", Q_NULLPTR));
        actionchinese->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\207", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        actionShowDetail->setText(QApplication::translate("MainWindow", "\351\241\257\347\244\272\344\270\212\345\202\263\347\255\206\346\225\270", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\224\235\345\275\261\346\251\237\351\201\270\345\226\256", Q_NULLPTR));
        btnRefresh->setText(QApplication::translate("MainWindow", "refresh", Q_NULLPTR));
        btnEditCamName->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\347\233\270\346\251\237\345\220\215", Q_NULLPTR));
        right_label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "No", Q_NULLPTR));
        btnBuildTester->setText(QApplication::translate("MainWindow", "\345\273\272\347\253\213\346\226\260\346\216\241\346\250\243\346\270\254\350\251\246", Q_NULLPTR));
        btnCameraStart_r->setText(QApplication::translate("MainWindow", "\346\223\267\345\217\226\345\217\263\347\234\274\345\275\261\345\203\217", Q_NULLPTR));
        btnCameraStart_l->setText(QApplication::translate("MainWindow", "\346\223\267\345\217\226\345\267\246\347\234\274\345\275\261\345\203\217", Q_NULLPTR));
        label_showInfo->setText(QString());
        btn_cancelWriteVideo->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210\346\223\267\345\217\226", Q_NULLPTR));
        btn_tester_finish->setText(QApplication::translate("MainWindow", "\346\216\241\346\250\243\347\265\220\346\235\237", Q_NULLPTR));
        btnOpenFolder->setText(QApplication::translate("MainWindow", "\351\226\213\345\225\237\350\263\207\346\226\231\345\244\276", Q_NULLPTR));
        btnVideoSelUpload->setText(QApplication::translate("MainWindow", "\351\201\270\346\223\207\346\252\224\346\241\210\344\270\212\345\202\263", Q_NULLPTR));
        label_logo->setText(QString());
        label_version->setText(QApplication::translate("MainWindow", "V2024.01.03.7", Q_NULLPTR));
        btnCameraStart->setText(QApplication::translate("MainWindow", "\351\226\213\345\247\213\346\223\267\345\217\226\345\275\261\345\203\217", Q_NULLPTR));
        btnCameraStop->setText(QApplication::translate("MainWindow", "camera stop", Q_NULLPTR));
        btnVideoSetting->setText(QApplication::translate("MainWindow", "\350\256\200\345\217\226\347\233\270\346\251\237\350\263\207\350\250\212", Q_NULLPTR));
        btnVideoSelTest->setText(QApplication::translate("MainWindow", "\346\240\241\346\255\243/\347\247\273\351\231\244\347\234\250\347\234\274", Q_NULLPTR));
        btnROINUpload->setText(QApplication::translate("MainWindow", "ROI\346\217\220\345\217\226(\346\211\213\345\213\225)", Q_NULLPTR));
        btn_roiAuto->setText(QApplication::translate("MainWindow", "ROI\346\217\220\345\217\226(\350\207\252\345\213\225)", Q_NULLPTR));
        btnVideoSeltoCanny->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262\345\275\261\347\211\207(3s)", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\344\270\212\345\202\263\350\250\255\345\256\232", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\275\261\347\211\207\346\240\274\345\274\217", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\350\252\252\346\230\216", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\205\266\344\273\226\350\250\255\345\256\232", Q_NULLPTR));
        menu_5->setTitle(QApplication::translate("MainWindow", "\350\252\236\350\250\200", Q_NULLPTR));
        menu_6->setTitle(QApplication::translate("MainWindow", "\346\225\270\346\223\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
