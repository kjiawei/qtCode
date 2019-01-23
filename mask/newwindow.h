#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QObject>

class newWindow : public QObject
{
    Q_OBJECT
public:
    explicit newWindow(QObject *parent = 0);

signals:

public slots:
};

#endif // NEWWINDOW_H
