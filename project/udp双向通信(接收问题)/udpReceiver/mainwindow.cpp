#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QUdpSocket();
    //绑定
    socket->bind(QHostAddress::AnyIPv4,9875);
    //关联读数据信号
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_data()
{
    QByteArray recv;
    recv.resize(socket->bytesAvailable());
    socket->readDatagram(recv.data(),recv.size());
    ui->listWidget->addItem(recv);
}

void MainWindow::on_pushButton_clicked()
{
    //刷新socket->readDatagram();
}

void MainWindow::on_pushButton_2_clicked()
{
    //只能本程序接收数据
    QByteArray sendMsg = ui->textEdit->toPlainText().toUtf8();
    socket->writeDatagram(sendMsg,QHostAddress("192.168.1.255"),9875);
}
