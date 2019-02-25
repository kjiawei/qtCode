#ifndef LOGIN_H
#define LOGIN_H

#include <QList>
#include <QString>
#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_loginButton_clicked();
    bool check_user_pass(QString user,QString pass);

    void on_xiaoxiaoBt_clicked();

private:
    Ui::login *ui;


};

#endif // LOGIN_H
