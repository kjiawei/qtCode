#include "qflist.h"
#include "ui_qflist.h"
#include<QPixmap>
#include<QStringlist>
#include <QListWidget>
#include<QTime>
#include<QDebug>
#include<QDialog>
#include<QFileDialog>
QFlist::QFlist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFlist)
{
    ui->setupUi(this);
    QPixmap pixmap(":/new/prefix1/2");
     pixmap = pixmap.scaled(ui->label->size());
     ui->label->setPixmap(pixmap);
     friendlist<<"小红"<<"小明"<<"小兰"<<"小鱼"<<"老王";
     strangerlist<<"不认识"<<"不知道"<<"不清楚";
     blacklist<<"葬爱摆"<<"葬爱蓝"<<"葬爱宏"<<"野狼网吧";
     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
     int tem;
     for(int i=0;i<friendlist.count();i++)
     {
        while((tem=qrand()%10)>7 || tem<1);
        qDebug()<<tem;
         QString picname=":/new/prefix1/";
         picname.append(QString::number(tem));
         QIcon icon(picname);
         QListWidgetItem *item = new QListWidgetItem(icon, friendlist.at(i));
         ui->listWidget->addItem(item);
     }
     for(int i=0;i<strangerlist.count();i++)
     {
        while((tem=qrand()%10)>7 || tem<1);
        qDebug()<<tem;
         QString picname=":/new/prefix1/";
         picname.append(QString::number(tem));
         QIcon icon(picname);
         QListWidgetItem *item1 = new QListWidgetItem(icon, friendlist.at(i));
         ui->listWidget_3->addItem(item1);
     }
     for(int i=0;i<blacklist.count();i++)
     {
        while((tem=qrand()%10)>7 || tem<1);
        qDebug()<<tem;
         QString picname=":/new/prefix1/";
         picname.append(QString::number(tem));
         QIcon icon(picname);
         QListWidgetItem *item2 = new QListWidgetItem(icon, friendlist.at(i));
         ui->listWidget_4->addItem(item2);
     }
}

QFlist::~QFlist()
{
    delete ui;
}

void QFlist::on_pushButton_clicked()
{
    QString picname=QFileDialog::getOpenFileName();
    QPixmap pic(picname);
    pic=pic.scaled(ui->label->size());
    ui->label->setPixmap(pic);
}

void QFlist::on_pushButton_2_clicked()
{
    this->parentWidget()->show();
    this->close();
}
