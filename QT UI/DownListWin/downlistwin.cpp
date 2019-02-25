#include "downlistwin.h"
#include "ui_downlistwin.h"
#include <downlistitem.h>

DownListWin::DownListWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownListWin)
{
    ui->setupUi(this);
}

DownListWin::~DownListWin()
{
    delete ui;
}

void DownListWin::on_adddownloadBt_clicked()
{
    //在列表中添加一行下载数据
    DownListItem *rowitem = new DownListItem(ui->listWidget);
    rowitem->set_movie_name("天下第一");
    rowitem->set_movie_size(460);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(rowitem->size());

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, rowitem);
}
