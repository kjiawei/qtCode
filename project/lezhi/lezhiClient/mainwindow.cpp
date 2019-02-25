#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QDateTime>
#include <QPainter>
#include <QTimer>
#include <windows.h> //使用sleep函数
#include <sys/stat.h>// linux下用sleep

//终端工作:请求本地服务器数据(天气) 接收(弹幕 推送紧急信息 新闻等) 发送连接信息给服务端等

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*********************UI初始化区 this->showFullScreen();*******************************/
    //设置背景图 (测试加边框)     监测版本更新
    versionManager = new QNetworkAccessManager();
    connect(versionManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_appUpdate(QNetworkReply*)));
    //this->setStyleSheet("background:gray");
    this->setStyleSheet("#MainWindow{border-image:url(:/new/prefix1/800480.jpg);}");

    ui->weatherLabel1->setFrameShape (QFrame::Box);
    ui->weatherLabel2->setFrameShape (QFrame::Box);
    ui->weatherLabel3->setFrameShape (QFrame::Box);
    //videoWidget不能设置setFrameShape属性

    //弹幕区
    ui->lxLabel->setFrameShape (QFrame::Box);
    //logo二维码区域如何只显示80大小 剩余自己发挥 扫描发弹幕 不拉伸
    ui->logoLabel->setFrameShape (QFrame::Box);//设置边框
    ui->logoLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix2/80.jpg);}");

    //"紧急消息"加粗变黑 内容红色
    newsCurIndex = 0;//当前角码
    jinjiNews = "紧aaaaaaabbbbbbbbbccccccccc急消eeeeeeee息,项目要ddddddddd提前交啦!再不做完就拜拜啦123456789123546798abcdefghijklmnopqrstuvwxyz";
    //超过部分不显示6
    newsWidth = fontMetrics().width("a");//每个字符宽度
    ui->jinjiNewWidget->setMinimumHeight(40);
    ui->jinjiNewWidget->setMaximumWidth(580);
    ui->jinjiNewWidget->setText(jinjiNews);//问题2:获取服务器发来的

    //触发滚动消息
    //timerNews = new QTimer;
    //connect(timerNews, &QTimer::timeout, this, &MainWindow::updateIndex);
    //timerNews->start(200);

    ui->activityLabel->setFrameShape (QFrame::Box);
    ui->newLabel->setFrameShape (QFrame::Box);

    //播放视频 后期加入服务端的远程控制 如何循环播放 上下切换 问题3:降低延时
    process = new QProcess();//kippprocess waitFor... system("killall mplayer")

    //#if PC 不同平台
    QStringList playArg;
    playArg<<"-wid";//嵌入到某个窗口播放的命令
    playArg<<QString::number(ui->videoWidget->winId());
    playArg<<"C:/Users/newuser/Desktop/QT/kjwcbz.avi";//可以是U盘文件 远程推送 目录下的
    process->start("C:/Users/newuser/Desktop/QT/mplayer-svn-37931/mplayer.exe",playArg);//

    //更新时间定时器 降低延时
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    timer->start(1000);

    //触发天气更新的定时器 问题4:一开始如何显示最新
    werTimer = new QTimer;
    connect(werTimer,SIGNAL(timeout()),this,SLOT(wertherUpdate()));
    werTimer->start(8000);

    /********************功能初始化区********************************/
    //tcp与本地服务器通信接口 dmSocket端口9876
    //调试socket端口9875(暂时用做接收紧急信息,后期判断是否被占用)
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
    socket->connectToHost("192.168.1.105",9875);
    //后期可考虑用定时器模拟按钮被按下事件
    dmSocket = new QTcpSocket();
    connect(dmSocket,SIGNAL(readyRead()),this,SLOT(read_dmData()));
    dmSocket->connectToHost("192.168.1.105",9876);//连接时机 地址更改使用

    //http与本地服务器进行通信 获取(天气 新闻等)数据 最近一周
    requestWeatherManager = new QNetworkAccessManager();
    connect(requestWeatherManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_wertherData(QNetworkReply*)));//服务器返回应答包manager会发出finish信号
    QUrl url("http://192.168.1.209/weather");
    //http://www.cnblogs.com/lechance/p/4373363.html
    QNetworkRequest request(url);
    requestWeatherManager->get(request);

    i=0;day = 5;//控制天气更新
    weaLabel = new weatherLabel(this);
    weaLabel->setGeometry(0,330,weaLabel->width(), weaLabel->height());
    weaLabel->show();
    weaLabel2 = new weatherLabel(this);
    weaLabel2->setGeometry(140,330,weaLabel2->width(), weaLabel2->height());
    weaLabel2->show();
    weaLabel3 = new weatherLabel(this);
    weaLabel3->setGeometry(280,330,weaLabel3->width(), weaLabel3->height());
    weaLabel3->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTime()//显示时间 有延时->放到构造函数
{
    QDateTime sysTime = QDateTime::currentDateTime();
    ui->timeLabel->setFrameShape (QFrame::Box);
    ui->timeLabel->setText(sysTime.toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void MainWindow::wertherUpdate()//刷新天气数据
{
    if(i<day)
    {
        if(i<day)
        {
            weaLabel->setWeather(weatherList.at(i++));//5转1的时候特别慢
        }else{
            i=0;
            weaLabel->setWeather(weatherList.at(i++));
        }

        if(i<day)
        {
            weaLabel2->setWeather(weatherList.at(i++));
        }else{
            i=0;
            weaLabel2->setWeather(weatherList.at(i++));
        }

        if(i<day)
        {
            weaLabel3->setWeather(weatherList.at(i++));
        }else{
            i=0;
            weaLabel3->setWeather(weatherList.at(i++));
        }

        qDebug()<<i;
    }else{
        i=0;
    }
}

void MainWindow::read_appUpdate(QNetworkReply*)
{

}

void MainWindow::read_wertherData(QNetworkReply* reply)//读取天气(本地)
{
    QString msg = reply->readAll();
    weatherList.clear();
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject obj = doc.object();
    obj = obj.value("data").toObject();
    QJsonArray array = obj.value("forecast").toArray();//需要的天气数据
    for(int i=0; i<array.count(); i++)
    {
        QJsonValue value = array.at(i);
        QJsonObject tmp = value.toObject();
        _Weather w;//天气类对象
        w.riqi = tmp.value("date").toString();
        w.fengli = tmp.value("fengli").toString();
        w.fx = tmp.value("fengxiang").toString();
        w.gaowen = tmp.value("high").toString();
        w.diwen = tmp.value("low").toString();
        w.tianqi = tmp.value("type").toString();
        weatherList.append(w);
    }
}

void MainWindow::read_data()//紧急
{
    //接收第三方服务器发来的信息 本地
    QString msg = socket->readAll();
    //setJinjiText(msg);//设置紧急信息通知
    qDebug()<<"收到紧急信息:"<<msg;
    ui->textEdit->clear();
    ui->textEdit->append(msg);
}

void MainWindow::read_dmData()//接收弹幕
{
    QString msg=dmSocket->readAll();
    qDebug()<<"收到弹幕:"<<msg;
    ui->danmuWidget->setText(msg);
}

void setJinjiText(QString str)
{
    //jinjiNews = str ;
}

//滚动字幕原实现
//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    //__super::paintEvent(event);
//    //问题:超过时间显示区域,首字一到边就全没了
//    QPainter painter(this);//750, 435
//    //painter.drawText(201, 460, jinjiNews.mid(0));//newsCurIndex
//    painter.drawText(width() - newsWidth*newsCurIndex, 460, jinjiNews.left(jinjiNews.length()));//newsCurIndex 10秒左右显示一次
//}

//void MainWindow::updateIndex()
//{
//    update();
//    newsCurIndex++;
//    if (newsCurIndex*newsWidth > width())
//        newsCurIndex = 0;
//}
