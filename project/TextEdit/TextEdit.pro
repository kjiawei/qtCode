# -------------------------------------------------
# Project created by QtCreator 2010-04-17T15:20:51
# -------------------------------------------------
QT += gui widgets printsupport
TARGET = TextEdit
TEMPLATE = app
SOURCES += main.cpp \
    textedit.cpp \
    mdichild.cpp \
    find_replace.cpp
HEADERS += textedit.h \
    mdichild.h \
    find_replace.h
FORMS += textedit.ui \
    find_replace.ui
RESOURCES += resources.qrc
OTHER_FILES += myIcon.rc
RC_FILE += myIcon.rc
