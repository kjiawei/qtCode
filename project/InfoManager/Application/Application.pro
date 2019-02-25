#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T17:35:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    StuManager.cpp \
    TeacherManager.cpp \
    ../CreateDB/createdb.cpp \
    addstudlg.cpp

HEADERS  += mainwindow.h \
    StuManager.h \
    TeacherManager.h \
    ../CreateDB/createdb.h \
    addstudlg.h

FORMS    += mainwindow.ui \
    StuManager.ui \
    TeacherManager.ui \
    addstudlg.ui

