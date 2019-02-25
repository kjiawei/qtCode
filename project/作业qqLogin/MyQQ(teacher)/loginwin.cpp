#include "loginwin.h"
#include "ui_loginwin.h"
#include <QMessageBox>
#include <qqlist.h>

LoginWin::LoginWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWin)
{
    ui->setupUi(this);
}

LoginWin::~LoginWin()
{
    delete ui;
}


bool LoginWin::check_user_pass(QString user, QString pass)
{
    if(user == "123" && pass == "123")
    {
        return true;
    }else
        return false;
}

void LoginWin::on_loginBt_clicked()
{
    QString user = ui->userinput->text();
    QString pass = ui->passinput->text();
    //判断是否有输入用户或密码
    if(user.isEmpty() || pass.isEmpty())
    {
        //提示输入用户或密码
        QMessageBox::warning(this,"QQ提示","请输入账号或密码");
        return ;
    }
    //判断用户或密码是否正确
    if(!check_user_pass(user, pass))
    {
        //提示输入用户或密码
        QMessageBox::warning(this,"QQ提示","请输入正确的账号或密码");
        return ;
    }
    //跳转到qq列表
    QQList *qqlistwin = new QQList(this);
    qqlistwin->show();
    //this->close();//把登录界面关闭
    this->hide();
}
