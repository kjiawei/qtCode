#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWindow>
#include <QScreen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("这是用mplayer在播放视频");
    ui->widget->setText("如果不喜欢看可以切换下一个");
    mprocess = new QProcess();
    /*
    QStringList list;
    list<<"-wid";
    qDebug()<<this->winId();
    qDebug()<<ui->widget->winId();
    list<<QString::number(ui->widget_3->winId());
    list<<"E:/GZ1706/c++_Qt/Qt/mplayer/kjwei.avi";
    mprocess->start("C:/mplayer-svn-37931/mplayer.exe",list);
    */

    //mplayer -slave -quiet -geometry 50:50 -zoom -x 400 -y 350 /mnt/mv.wmv
    QString cmd("mplayer -slave -quiet -geometry ");
    cmd.append(QString("%1:%2").arg(QString::number(ui->vplayer->x())).arg(QString::number(ui->vplayer->y())));
    cmd.append(QString(" -zoom -x %1 -y %2 ").arg(QString::number(ui->vplayer->width()))
               .arg(QString::number(ui->vplayer->height())));
    cmd.append("./kjwei.avi");
    mprocess->start(cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
