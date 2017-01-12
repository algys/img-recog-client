#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T01:28:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    catalog.cpp \
    core.cpp \
    recog.cpp \
    recogwidget.cpp \
    infowidget.cpp \
    childwidget.cpp \
    reciever.cpp

HEADERS  += mainwindow.h \
    catalog.h \
    core.h \
    recog.h \
    recogwidget.h \
    infowidget.h \
    childwidget.h \
    reciever.h


LIBS += /usr/lib/libopencv_core.so \
    /usr/lib/libopencv_features2d.so \
    /usr/lib/libopencv_highgui.so \
    /usr/lib/libopencv_contrib.so \
    /usr/lib/libopencv_flann.so \
    /usr/lib/libopencv_calib3d.so \
    /usr/lib/libopencv_imgproc.so \
    /usr/lib/libopencv_legacy.so \
    /usr/lib/libopencv_nonfree.so

CONFIG += c++11
