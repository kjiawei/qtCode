#include <QTextCodec>
#include <QTime>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTreeWidget>
#include <QHBoxLayout>
#include "SnakeDlg.h"

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForTr (QTextCodec::codecForName ("utf-8"));
    qsrand(QTime::currentTime ().msec ());
    QApplication a(argc, argv);
    QTranslator tr;
    tr.load ("qt_" + QLocale::system ().name (),
             "/usr/share/qt4/translations");
    a.installTranslator (&tr);

    SnakeDlg w;
    w.show();

    return a.exec();
}
