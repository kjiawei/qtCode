#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include <qqlist.h>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

//检查密码，用户是否正确
bool login::check_user_pass(QString user,QString pass)
{
    if(user=="ABC" && pass =="abc")
        return true;
    else
        return false;

}
void login::on_loginButton_clicked()
{
    QString user = ui->userinput->text();
    QString pass = ui->passinput->text();
    if(user.isEmpty() || pass.isEmpty())
    {
        //提示用户输入
        QMessageBox::warning(this,"提示","请输入账号与密码");
        return;
    }

    if(!check_user_pass(user,pass))
    {
        QMessageBox::warning(this,"提示","错误");
        QMessageBox::warning(this,"user","ABC");
        QMessageBox::warning(this,"pass","abc");
    }else{

        //跳转到qq列表
        QQList *qqlistwin=new QQList(this);
        //里面必须要有this，不然跳不回去
        qqlistwin->show();
        this->hide();
    }
}

void login::on_xiaoxiaoBt_clicked()
{
    ui->userinput->clear();
    ui->passinput->clear();
}
