#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T18:04:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qtclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gstclient.cpp

HEADERS  += mainwindow.h \
    gstclient.h

FORMS    += mainwindow.ui
CONFIG += console
CONFIG -= app_bundle
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-0.10 \

}

