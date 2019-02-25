#ifndef CUTSCREEN_H
#define CUTSCREEN_H

#include <QMainWindow>
#include <QMutex>

namespace Ui {
class CutScreen;
}

class CutScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit CutScreen(QWidget *parent = 0);
    ~CutScreen();

private slots:
    void on_cutBt_clicked();

private:
    Ui::CutScreen *ui;
    QMutex mutex;
};

#endif // CUTSCREEN_H
