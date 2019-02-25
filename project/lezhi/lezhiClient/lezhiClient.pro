#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T14:10:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lezhiClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rolltext.cpp \
    weatherlabel.cpp

HEADERS  += mainwindow.h \
    rolltext.h \
    weatherlabel.h

FORMS    += mainwindow.ui \
    weatherlabel.ui

RESOURCES += \
    resource/pic/pic.qrc \
