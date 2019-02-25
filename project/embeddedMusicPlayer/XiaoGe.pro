RC_FILE = XiaoGe.rc
TARGET = MP3


QT += multimedia \
      multimediawidgets \
      widgets

HEADERS += \
    player.h \
    playlistmodel.h \
    musiclist.h \
    mylrc.h

SOURCES += \
    player.cpp \
    main.cpp \
    playlistmodel.cpp \
    musiclist.cpp \
    mylrc.cpp

RESOURCES += \
    images.qrc

OTHER_FILES += \
    XiaoGe.rc
