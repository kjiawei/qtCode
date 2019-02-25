#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QUdpSocket();
    socket->bind(QHostAddress::AnyIPv4,9875);//为了双向通信
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_data()
{
    //无法收信息
    QByteArray recv;
    recv.resize(socket->bytesAvailable());
    socket->readDatagram(recv.data(),recv.size());
    ui->listWidget->addItem(recv);
}

void MainWindow::on_sendButton_clicked()
{
    //包括长度  50,    QHostAddress::Any
    QByteArray sendMsg = ui->textEdit->toPlainText().toUtf8();
    socket->writeDatagram(sendMsg,QHostAddress("192.168.1.255"),9875);
                                //QHostAddress::Broadcast//255广播地址也可以
                                //224.0.0.100组播地址 joinMulticastGroup加入 退出level
}

void MainWindow::on_refreshButton_clicked()
{
    //QString msg = socket->readDatagram(msg,50,QHostAddress::Any,9875);
    //qDebug()<<msg;
    //ui->listWidget->addItem(msg);
}
