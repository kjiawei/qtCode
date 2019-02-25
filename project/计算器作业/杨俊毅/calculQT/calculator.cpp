#include "calculator.h"
#include "ui_calculator.h"

QString labal;
QString current;
int equwl;
bool over=true;


Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    group=new QButtonGroup;
    calgroup=new QButtonGroup;
    group->addButton(ui->p1,1);
    group->addButton(ui->p2,2);
    group->addButton(ui->p3,3);
    group->addButton(ui->p4,4);
    group->addButton(ui->p5,5);
    group->addButton(ui->p6,6);
    group->addButton(ui->p7,7);
    group->addButton(ui->p8,8);
    group->addButton(ui->p9,9);
    group->addButton(ui->p0,0);
    calgroup->addButton(ui->padd,1);
    calgroup->addButton(ui->psub,2);
    calgroup->addButton(ui->pmul,3);
    calgroup->addButton(ui->pdiv,4);
     QObject::connect(group,SIGNAL(buttonClicked(int)),this,SLOT(button_group(int)));
      QObject::connect(calgroup,SIGNAL(buttonClicked(int)),this,SLOT(cal_group(int)));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::button_group(int sig)
{
    while(over==false)
    {
        current="";
        labal="";
        equwl=0;
        ui->box->setText("");
        ui->cal_text->setText("");
        over=true;
    }
    switch(sig)
    {
        case 1:current.append("1");break;
         case 2:current.append("2");break;
         case 3:current.append("3");break;
         case 4:current.append("4");break;
         case 5:current.append("5");break;
         case 6:current.append("6");break;
         case 7:current.append("7");break;
         case 8:current.append("8");break;
         case 9:current.append("9");break;
         case 0:current.append("0");break;
    }
    ui->box->setText(current);
}


void Calculator::cal_group(int sig)
{
    if(current=="")
    {
           QString::iterator it=labal.end();
           switch(sig)
           {
               case 1: *(it-1)='+';ui->cal_text->setText(labal);break;
               case 2: *(it-1)='-';ui->cal_text->setText(labal);break;
               case 3: *(it-1)='*';ui->cal_text->setText(labal);break;
               case 4: *(it-1)='/';ui->cal_text->setText(labal);break;
           }
            return;
    }
    QString equ;
    switch(sig)
     {
    case 1:
            equwl=equwl+current.toInt();
            equ=QString::number(equwl);
            labal=labal+current+" +";
            ui->box->setText("");
            ui->cal_text->setText(labal);
            current="";
            ui->box->setText(equ);
        break;
    case 2:equwl=equwl-current.toInt();
        equ=QString::number(equwl);
        labal=labal+current+" -";
        ui->box->setText("");
        ui->cal_text->setText(labal);
        current="";
        ui->box->setText(equ);
        break;
    case 3:equwl=equwl*current.toInt();
        equ=QString::number(equwl);
        labal=labal+current+" *";
        ui->box->setText("");
        ui->cal_text->setText(labal);
        current="";
        ui->box->setText(equ);
        break;
    case 4:equwl=equwl/current.toInt();
        equ=QString::number(equwl);
        labal=labal+current+" /";
        ui->box->setText("");
        ui->cal_text->setText(labal);
        current="";
        ui->box->setText(equ);
        break;
    }
}

void Calculator::on_pequal_clicked()
{
    int sig;
    QString::iterator it=labal.end();
    if(*(it-1)=='+')sig=1;
    else if(*(it-1)=='-')sig=2;
    else if(*(it-1)=='*')sig=3;
    else if(*(it-1)=='/')sig=4;
    QString equ;
    switch(sig)
     {
    case 1:
            equwl=equwl+current.toInt();
            equ=QString::number(equwl);
            current="";
            ui->box->setText(equ);
            ui->cal_text->setText("");
        break;
    case 2:   equwl=equwl-current.toInt();
        equ=QString::number(equwl);
        current="";
        ui->box->setText(equ);
        ui->cal_text->setText("");
        break;
    case 3:   equwl=equwl*current.toInt();
        equ=QString::number(equwl);
        current="";
        ui->box->setText(equ);
        ui->cal_text->setText("");
        break;
    case 4:   equwl=equwl/current.toInt();
        equ=QString::number(equwl);
        ui->box->setText(equ);
        ui->cal_text->setText("");
        current="";
        labal="";
        equwl=0;
        break;
    }
    over=false;
}

void Calculator::on_pclear_clicked()
{
    current="";
    labal="";
    equwl=0;
    ui->box->setText("");
    ui->cal_text->setText("");
}
