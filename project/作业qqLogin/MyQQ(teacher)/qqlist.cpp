#include "qqlist.h"
#include "ui_qqlist.h"


QQList::QQList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QQList)
{
    ui->setupUi(this);
    friendlist<<"小米"<<"小华"<<"小王"<<"小姐"<<"火影"<<"火花";
    strangerlist<<"王朝"<<"马汉"<<"张龙"<<"赵虎";
    blacklist<<"晓华"<<"苹果";

    //ui->listWidget->addItems(friendlist);
    ui->listWidget_2->addItems(strangerlist);
    ui->listWidget_3->addItems(blacklist);

    for(int i=0; i<friendlist.count(); i++)
    {
        //添加头像图片
        QIcon icon("E:/GZ1706/c++_Qt/Qt/002/code/MyQQ/qq-icon.png");
        QListWidgetItem *item = new QListWidgetItem(icon, friendlist.at(i));
        ui->listWidget->addItem(item);
    }


    QPixmap pixmap("E:/GZ1706/c++_Qt/Qt/002/code/MyQQ/qq-icon.png");
    pixmap = pixmap.scaled(ui->label->size());//设置大小
    ui->label->setPixmap(pixmap);
}

QQList::~QQList()
{
    delete ui;
}

void QQList::on_pushButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}
