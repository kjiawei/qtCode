#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QMainWindow>

namespace Ui {
class LoginWin;
}

class LoginWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWin(QWidget *parent = 0);
    ~LoginWin();
    bool check_user_pass(QString user, QString pass);
private slots:
    void on_loginBt_clicked();

private:
    Ui::LoginWin *ui;


};

#endif // LOGINWIN_H
