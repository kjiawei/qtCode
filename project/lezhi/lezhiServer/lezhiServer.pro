#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T14:09:43
#
#-------------------------------------------------

QT       += core gui network testlib sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lezhiServer
TEMPLATE = app

SOURCES += main.cpp\
        model\globaldata.cpp\
        model\datacenter.cpp \
        view\mainwindow.cpp \
        view\globalwidget.cpp \
        view\componentwidget.cpp \
        view\devicelist.cpp \
        view\weatherlabel.cpp \
        configpage.cpp \
        bluetoothlight.cpp \
        commonfunc.cpp \
        test\unittest.cpp

HEADERS  += view\mainwindow.h \
        model\globaldata.h\
        model\datacenter.h \
        view\globalwidget.h \
        view\componentwidget.h \
        view\devicelist.h \
        view\weatherlabel.h \
        configpage.h \
        bluetoothlight.h \
        commonfunc.h \
        test\unittest.h

    ##system(cd data/./sqlite3;);
    ##system(.tables);

FORMS    += \
            model/datacenter.ui \
            bluetoothlight.ui \
            view/mainwindow.ui \
            view/weatherlabel.ui \
