#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建进程
    myprocess = new QProcess();
    //关联读数据信号
    connect(myprocess,SIGNAL(readyRead()),this, SLOT(read_msg()));
    myprocess->start("hostname -i");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setipBT_clicked()
{
    //todo
    //判断是否如何ip地址格式
    QString setip=ui->lineEdit->text();
    qDebug()<<setip;
    QString commond="gksu ifconfig enp8s0 ";
    commond.append(setip);
    system("gksu sudo ifconfig enp8s0 192.168.1.2");
    //调用LINUX C函数库中的system(const char *string);
}

void MainWindow::on_getIpBT_clicked()
{
    //检测进程是否在运行如在运行就咔嚓掉
    if(myprocess->state() == QProcess::Running)
    {
        myprocess->kill();
        myprocess->waitForFinished();
    }
    myprocess->start("hostname -i");

}

void MainWindow::read_msg()
{
    //todo
    //只看到ip地址和硬件设备号
    //读数据
    QString msg = myprocess->readAll();

    ui->textEdit->setText(msg.toUtf8().data());
    QString msg_uf8=msg.toUtf8().data();
    qDebug()<<msg_uf8;
    qDebug()<<"==============+++++++++++";
    QStringList strlist=msg_uf8.split(" ");//将字符串以“；”为界分割成数组形式存到QStringList变量strlist中
    qDebug()<<strlist;
    ui->lineEdit->setText(strlist.at(4));
    //打印出list中的n个元素
    ui->lineEdit_2->setText(strlist.at(5));
     ui->lineEdit_3->setText(strlist.at(6));
    qDebug()<<"==============";


}
