#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QCoreApplication>
#include <QFont>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QTextCodec *pCodec = QTextCodec::codecForName("GBK");
    if(pCodec)
    {
        QTextCodec::setCodecForLocale(pCodec);
    }

    QCoreApplication::setApplicationName("StuTest");

    QApplication a(argc, argv);

    QFile file("../Styles/white.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString style = in.readAll();
        file.close();
        qApp->setStyleSheet(style);
    }

    QFont serifFont("Times", 12, QFont::Thin);
    a.setFont(serifFont);

    MainWindow w;
    w.setWindowTitle(QObject::tr("管理系统"));
    w.show();

    return a.exec();
}
