#include "qqqt.h"
#include "ui_qqqt.h"

qqQT::qqQT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qqQT)
{
    ui->setupUi(this);
}

qqQT::~qqQT()
{
    delete ui;
}

void qqQT::on_outBt_clicked()
{
    this->close();
}

void qqQT::on_signinBt_clicked()
{
    QString usrname=ui->usr->text();
    QString password=ui->password->text();
    if(usrname.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"提示","用户名或密码不能为空");
        return;
    }
   if(check_usr_password(usrname,password))
   {
       QFlist *talk=new QFlist(this);
       talk->show();
       this->hide();
   }
   else
   {
       QMessageBox::warning(this,"提示","密码错误，请重新输入");
       ui->usr->setText("");
       ui->password->setText("");
   }
}

bool qqQT::check_usr_password(QString &usr,QString &password)
{
    if(usr=="yang" && password=="123456")
    {
        return true;
    }
    else return false;
}
