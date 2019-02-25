#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T18:21:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets sql
CONFIG += c++11
TARGET = 01-22-VideoPlayer
TEMPLATE = app
LIBS += -lshell32

SOURCES += main.cpp\
        Widget.cpp \
    WWWNOTE.cpp \
    VideoWidget.cpp \
    MainSlider.cpp \
    VolumeSlider.cpp \
    ListWidget.cpp \
    BottomWidget.cpp

HEADERS  += Widget.h \
    VideoWidget.h \
    MainSlider.h \
    VolumeSlider.h \
    ListWidget.h \
    BottomWidget.h

FORMS    += Widget.ui

RESOURCES +=
