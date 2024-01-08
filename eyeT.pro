#-------------------------------------------------
#
# Project created by QtCreator 2023-11-07T19:45:10
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eyeAnalysis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#-------------------------------------------
#DEFINES += SELF_TEST
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    frameHandler/frameutility.cpp \
    uploadHandler/uploadutility.cpp \
    handler/uploadhandler.cpp \
    dialog.cpp \
    settingform.cpp

HEADERS  += mainwindow.h \
    frameHandler/frameutility.h \
    uploadHandler/uploadutility.h \
    handler/uploadhandler.h \
    dialog.h \
    settingform.h

FORMS    += mainwindow.ui \
    dialog.ui \
    settingform.ui

INCLUDEPATH += C:\opencv\build\include
LIBS += C:\opencv\opencv-build\bin\opencv_videoio_ffmpeg481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_videoio481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_video481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_stitching481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_photo481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_objdetect481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_ml481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_imgproc481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_imgcodecs481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_highgui481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_gapi481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_flann481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_features2d481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_dnn481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_core481.dll
LIBS += C:\opencv\opencv-build\bin\libopencv_calib3d481.dll


INCLUDEPATH += $$PWD/../../../../AppData/Local/Programs/Python/Python312-32/include
LIBS += -L$$PWD/../../../../AppData/Local/Programs/Python/Python312-32/libs/ -lpython312

DISTFILES += \
    release/TEST.py \
    release/TEST_2param.py

RESOURCES += \
    icon.qrc
