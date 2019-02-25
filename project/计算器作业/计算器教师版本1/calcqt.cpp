#include "calcqt.h"
#include "ui_calcqt.h"
#include <QDebug>
CalcQt::CalcQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalcQt)
{
    ui->setupUi(this);

    //出时候化按钮组
    group = new QButtonGroup();
    group->addButton(ui->num1Bt,1);
    group->addButton(ui->num2Bt,2);
    group->addButton(ui->num3Bt,3);
    group->addButton(ui->num4Bt,4);
    group->addButton(ui->num5Bt,5);
    group->addButton(ui->num6Bt,6);
    group->addButton(ui->num7Bt,7);
    group->addButton(ui->num8Bt,8);
    group->addButton(ui->num9Bt,9);
    //当按钮组中的某一个按钮按下，这个按钮组group就会发送一个信号
    connect(group,SIGNAL(buttonClicked(int)),this, SLOT(button_num(int)));
}

CalcQt::~CalcQt()
{
    delete ui;
}

void CalcQt::button_num(int i)
{
    if(ui->changBt->text() == "num1")
    {
        QString str = ui->firstNum->text();
        str.append(QString::number(i));
        ui->firstNum->setText(str);
    }else
    {
        QString str = ui->secondNum->text();
        str.append(QString::number(i)); //在str原先的基础上追加字符串
        ui->secondNum->setText(str);
    }
}

void CalcQt::on_calcBt_clicked()
{
    ui->calcChar->setText("+");

    QString num1=ui->firstNum->text();
    QString num2=ui->secondNum->text();
    //把字符串转数
    double dnum1 = num1.toDouble();
    double dnum2 = num2.toDouble();
    double dresult = dnum1+dnum2;

    //把结果显示在界面上
    //把数转字符串
    QString result = QString::number(dresult);
    ui->resultNum->setText(result);
}

void CalcQt::on_subBt_clicked()
{
    ui->calcChar->setText("-");

    QString num1=ui->firstNum->text();
    QString num2=ui->secondNum->text();
    //把字符串转数
    double dnum1 = num1.toDouble();
    double dnum2 = num2.toDouble();
    double dresult = dnum1-dnum2;

    //把结果显示在界面上
    //把数转字符串
    QString result = QString::number(dresult);
    ui->resultNum->setText(result);
}

void CalcQt::on_changBt_clicked()
{
    if(ui->changBt->text() == "num1")
    {
        ui->changBt->setText("num2");
    }else
    {
        ui->changBt->setText("num1");
    }
}

void CalcQt::on_chBt_clicked()
{
    ui->calcChar->setText("*");

    QString num1=ui->firstNum->text();
    QString num2=ui->secondNum->text();
    //把字符串转数
    double dnum1 = num1.toDouble();
    double dnum2 = num2.toDouble();
    double dresult = dnum1*dnum2;

    //把结果显示在界面上
    //把数转字符串
    QString result = QString::number(dresult);
    ui->resultNum->setText(result);
}

void CalcQt::on_deBt_clicked()
{
    ui->calcChar->setText("/");

    QString num1=ui->firstNum->text();
    QString num2=ui->secondNum->text();
    //把字符串转数
    double dnum1 = num1.toDouble();
    double dnum2 = num2.toDouble();
    double dresult = dnum1/dnum2;

    //把结果显示在界面上
    //把数转字符串
    QString result = QString::number(dresult);
    ui->resultNum->setText(result);
}
