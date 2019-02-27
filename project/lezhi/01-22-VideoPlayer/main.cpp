#include "Widget.h"

#include <QApplication>
#include<QDesktopWidget>
#include<QWidget>
#include<QRect>
#include<QDebug>


#include<QString>
#include<QIcon>
#include<QDir>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QString name = QDir::currentPath();
    QPixmap appIcon((name+"/appIcon.png"));
    a.setWindowIcon(appIcon);
    Widget w;
    //w.setWindowIcon(appIcon);
    int width = QApplication::desktop()->availableGeometry().width();
    int height = QApplication::desktop()->availableGeometry().height();
    w.setGeometry((width-w.getWindowIniWidth())/2, (height-w.getWindowIniHeight())/2, w.getWindowIniWidth(), w.getWindowIniHeight());
    w.show();

    return a.exec();
}
