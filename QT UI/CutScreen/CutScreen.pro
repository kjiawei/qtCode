#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T14:07:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CutScreen
TEMPLATE = app


SOURCES += main.cpp\
        cutscreen.cpp \
    screenthread.cpp

HEADERS  += cutscreen.h \
    screenthread.h

FORMS    += cutscreen.ui
