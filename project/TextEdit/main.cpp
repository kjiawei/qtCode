//#include <QtGui/QApplication>
#include <QApplication>
#include "textedit.h"
#include <QTextCodec>
#include <QSplashScreen>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/images/yafeilinux.gif");
    QSplashScreen splash(pixmap);//程序启动画面
    for(qint64 i=5555555*6;i>0;i--)
        splash.show();
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//支持中文显示
    TextEdit w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
