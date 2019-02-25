#include "qqlist.h"
#include "ui_qqlist.h"
#include <ctime>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <unistd.h>
#include <QString>
#include <QMessageBox>

QQList::QQList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QQList)
{
    ui->setupUi(this);
    friendlist<<"小米"<<"小小"<<"AF"<<"WE"<<"EQ";
    strangerlist<<"小fg米"<<"小gg小"<<"AghjF";
    blacklist<<"米"<<"小"<<"F"<<"E"<<"Q";


    //ui->listWidget->addItems(friendlist);
    //单单加入文字就这样
    ui->listWidget_2->addItems(strangerlist);
    ui->listWidget_3->addItems(blacklist);
    int ran_num;

    for(int i=0;i<friendlist.count();i++)
    {

        ran_num=rand() % 6;
        qDebug()<<ran_num<<" ";
        QString name=":/new/prefix1/";
        QString num=QString::number(ran_num);
        name.append(num+".png");
        qDebug()<<name<<" ";
        srand((unsigned)time(0));
        QIcon icon(name);
        //QIcon icon(":/new/prefix1/2.png");
        //QListWidgetItem *item=new QListWidgetItem(icon,friendlist.at(i));
        //ui->listWidget->addItem(item);
        //匿名对象类
        ui->listWidget->addItem(new QListWidgetItem(icon,friendlist.at(i)));
    }

    //设置头像
    QPixmap pixmap(":/new/prefix1/1.png");//照片路径
    pixmap=pixmap.scaled(ui->label->size());
    ui->label->setPixmap(pixmap);
}
void QQList::on_pushButton_2_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setDirectory(".");

    if(fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        QPixmap pixmap(path);//照片路径
        pixmap=pixmap.scaled(ui->label->size());
        ui->label->setPixmap(pixmap);
    }
    delete fileDialog;
    //下面这个不知道如何delete
    //QString filepath = QFileDialog::getOpenFileName();
    //qDebug()<<filepath<<endl;
    //QPixmap pixmap(filepath);//照片路径
    //qDebug()<<filepath<<endl;
    //pixmap=pixmap.scaled(ui->label->size());
    //ui->label->setPixmap(pixmap);

    //qDebug()<<filepath<<endl;
    //sleep(100000);
}
QQList::~QQList()
{
    delete ui;
}

//注销
void QQList::on_pushButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}


