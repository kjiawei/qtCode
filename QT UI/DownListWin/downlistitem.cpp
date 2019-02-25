#include "downlistitem.h"
#include "ui_downlistitem.h"
#include <QDebug>
DownListItem::DownListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownListItem)
{
    ui->setupUi(this);
    downsize = 0;
    mtimer = new QTimer();
    connect(mtimer,SIGNAL(timeout()),this,SLOT(update_progress()));
}
void DownListItem::set_movie_name(QString name)
{
    ui->moviename->setText(name);
}
void DownListItem::set_movie_size(double size)
{
    ui->moviesize->setText(QString::number(size)+"M");
    int num = (int)size;
    moviesize = num;
    qDebug()<<num;
    ui->progressBar->setMaximum((int)size);
}
void DownListItem::set_down_size(int size)
{
    ui->progressBar->setValue(size);
}


DownListItem::~DownListItem()
{
    delete ui;
}

void DownListItem::update_progress()
{
    if(downsize < moviesize)
    {
        set_down_size(downsize);
    }else
    {
        mtimer->stop();
        downsize = 0;
    }
    downsize++;
}

void DownListItem::on_selectCb_clicked(bool checked)
{
    if(checked)
    {
        mtimer->start(100);
    }else
    {
        mtimer->stop();
    }
}
