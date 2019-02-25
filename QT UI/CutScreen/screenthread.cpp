#include "screenthread.h"
#ifdef WIN32
        #include <windows.h>
#endif
#include <QApplication>
#include <QPixmap>
#include <QScreen>
#include <QDebug>
ScreenThread::ScreenThread()
{
    this->lab = NULL;
}
void ScreenThread::set_screen_show(QLabel *label, QMutex *mutex)
{
    this->lab = label;
    this->mut = mutex;
}

void ScreenThread::run()
{
    if(this->lab == NULL)
        return;
    while(1)
    {
        //截屏
        QPixmap pixmap = QApplication::screens().at(0)->grabWindow(0,0,0,400,400);
        //pixmap = pixmap.scaled(lab->size());
        mut->lock();
        lab->setPixmap(pixmap);
        mut->unlock();
#ifdef WIN32
        Sleep(200);
#else
        sleep(200);
#endif
    }
}

