# -------------------------------------------------
# Project created by QtCreator 2013-10-04T18:21:49
# -------------------------------------------------
TARGET = Qtreproductor
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    gstmp3.cpp
HEADERS += mainwindow.h \
    gstmp3.h
FORMS += mainwindow.ui
CONFIG += console
CONFIG -= app_bundle
unix { 
    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-0.10 \

}
