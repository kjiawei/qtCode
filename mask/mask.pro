#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T14:13:55
#
#-------------------------------------------------

QT       += core gui
QT       += sql
#QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mask
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maskwindow.cpp \
    gammaramp.cpp \
    screensaver.cpp \
    globalvar.cpp \
    datamanage.cpp \
    newwindow.cpp

HEADERS  += mainwindow.h \
    maskwindow.h \
    screensaver.h \
    globalvar.h \
    datamanage.h \
    newwindow.h
    gammaramp.h

FORMS    += mainwindow.ui \
    maskwindow.ui \
    screensaver.ui

RESOURCES += \
    style.qrc
