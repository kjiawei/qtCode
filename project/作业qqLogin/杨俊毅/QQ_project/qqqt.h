#ifndef QQQT_H
#define QQQT_H

#include <QMainWindow>
#include <QMessageBox>
#include <qflist.h>
#include<QString>
namespace Ui {
class qqQT;
}

class qqQT : public QMainWindow
{
    Q_OBJECT

public:
    explicit qqQT(QWidget *parent = 0);
    ~qqQT();
    bool check_usr_password(QString &usr,QString &password);
private slots:
    void on_outBt_clicked();
    void on_signinBt_clicked();

private:
    Ui::qqQT *ui;
};

#endif // QQQT_H
