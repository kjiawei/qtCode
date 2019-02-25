#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_setipBT_clicked();

    void on_getIpBT_clicked();
    void read_msg();

private:
    Ui::MainWindow *ui;
    QProcess *myprocess;
};

#endif // MAINWINDOW_H
