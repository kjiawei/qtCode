#ifndef SCREENTHREAD_H
#define SCREENTHREAD_H

#include <QThread>
#include <QLabel>
#include <QMutex>

class ScreenThread: public QThread
{
public:
    ScreenThread();
    void run();
    void set_screen_show(QLabel *label, QMutex *mutex);
private:
    QLabel *lab;
    QMutex *mut;
};

#endif // SCREENTHREAD_H
