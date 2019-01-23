#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QWidget>
#include "mainwindow.h"


namespace Ui {
class ScreenSaver;
}

class ScreenSaver : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenSaver(QWidget *parent = 0);
    ~ScreenSaver();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ScreenSaver *ui;
};

#endif // SCREENSAVER_H
