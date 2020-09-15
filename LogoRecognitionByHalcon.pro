#-------------------------------------------------
#
# Project created by QtCreator 2020-09-05T07:57:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogoRecognitionByHalcon
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += D:\MVTec\HALCON-17.12-Progress\include
INCLUDEPATH +=  D:\MVTec\HALCON-17.12-Progress\include\halconcpp

INCLUDEPATH += D:\opencv\opencv4.4.0\build\include\opencv2
INCLUDEPATH += D:\opencv\opencv4.4.0\build\include
LIBS += D:\opencv\opencv4.4.0\build\x64\vc14\lib\opencv_world440.lib

LIBS += D:\MVTec\HALCON-17.12-Progress\lib\x64-win64\*.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    halconcv.cpp

HEADERS  += mainwindow.h \
    halconcv.h

FORMS    += mainwindow.ui
