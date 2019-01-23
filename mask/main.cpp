#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.installEventFilter(&w);//mainWindow事件处理

    return a.exec();
}
