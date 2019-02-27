#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenthread.h"

#include <QDate>
#include <QScreen>
#include <QDebug>
#include <QDateTime>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <windows.h> //使用sleep函数
#include <sys/stat.h>// linux下用sleep

#define wkd_final 5
#define W_UDT 5 //更新天气显示间隔
/*
 * 优化队列
 * 截屏:;
 * 响应式(播放/结束时不挤压控件);
 * 新建并打开TXT:;
1.显隐控件(快进退短提示) 视频列表(+- 本地缓存列表 判断文件是否存在-变色) 鼠标移进才显示控件 播放器路径固定
2.终端工作:请求本地服务器数据(天气) 接收(弹幕 推送紧急信息 新闻等) 发送连接信息给服务端等
*/

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);//this->showFullScreen();//设置背景图     监测版本更新

    ui->textEdit->installEventFilter(this);
    initParams();
    initView();

    versionManager = new QNetworkAccessManager();
    connect(versionManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_appUpdate(QNetworkReply*)));

    timer = new QTimer;//系统时间
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    timer->start(1000);

    playerTimer = new QTimer;
    connect(playerTimer,SIGNAL(timeout()),this,SLOT(playerTime()));

    //tcp与本地服务器通信接口 dmSocket端口9876
    //调试socket端口9875(暂时用做接收紧急信息,后期判断是否被占用)
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_data()));
    socket->connectToHost("192.168.1.105",9875);

    dmSocket = new QTcpSocket();//后期可考虑用定时器模拟按钮被按下事件
    connect(dmSocket,SIGNAL(readyRead()),this,SLOT(read_dmData()));
    dmSocket->connectToHost("192.168.1.105",9876);//连接时机 地址更改使用

    //直接获取网上(本地服务器天气 新闻等)数据
    requestWeatherManager = new QNetworkAccessManager();
    connect(requestWeatherManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_wertherData(QNetworkReply*)));//服务器返回应答包manager会发出finish信号
    QUrl url("http://192.168.1.209/weather");//http://www.cnblogs.com/lechance/p/4373363.html
    QNetworkRequest request(url);
    requestWeatherManager->get(request);
    weatherTimer = new QTimer;//触发天气更新的定时器 问题4:一开始如何显示最新
    connect(weatherTimer,SIGNAL(timeout()),this,SLOT(weatherUpdate()));
    //weatherTimer->start(W_UDT*1000);

    //ui->jinjiNewWidget->setText(jinjiNews);//问题2:获取服务器发来的
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initView()//initParams
{
    /*QPalette pal(ui->videoWidget->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    ui->videoWidget->setAutoFillBackground(true);
    ui->videoWidget->setPalette(pal);*/
    ui->videoWidget->setStyleSheet("background-color:black;");
    //this->setStyleSheet("background:gray");
    this->setStyleSheet("#MainWindow{border-image:url(:/new/prefix1/800480.jpg);}");
    ui->pushButton->setVisible(true);
    /*ui->weatherLabel1->setFrameShape (QFrame::Box);
    ui->weatherLabel2->setFrameShape (QFrame::Box);
    ui->weatherLabel3->setFrameShape (QFrame::Box);*/
    //videoWidget不能设置setFrameShape属性
    //ui->lxLabel->setFrameShape (QFrame::Box);//弹幕区
    //ui->logoLabel->setFrameShape (QFrame::Box);//设置边框 logo二维码区域如何只显示80大小 剩余自己发挥 扫描发弹幕 不拉伸
    //ui->logoLabel->setStyleSheet("QLabel{border-image: url(:/new/prefix2/80.jpg);}");

    weaLabel = new weatherLabel(this);//天气明细框
    weaLabel->setGeometry(0,330,weaLabel->width(), weaLabel->height());

    weaLabel2 = new weatherLabel(this);
    weaLabel2->setGeometry(140,330,weaLabel2->width(), weaLabel2->height());

    weaLabel3 = new weatherLabel(this);
    weaLabel3->setGeometry(280,330,weaLabel3->width(), weaLabel3->height());
    //weaLabel->show();weaLabel2->show();weaLabel3->show();
    weaLabel->setVisible(false);
    weaLabel2->setVisible(false);
    weaLabel3->setVisible(false);
    newsWidth = fontMetrics().width("a");//每个字符宽度
    ui->jinjiNewWidget->setMinimumHeight(40);
    ui->jinjiNewWidget->setMaximumWidth(580);

    //ui->activityLabel->setFrameShape (QFrame::Box);
    //ui->videoWidge
    //ui->newLabel->setFrameShape (QFrame::Box);
    //ui->textEdit->setVisible(false);
    //ui->newLabel->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->voiceSlider->setVisible(false);
}

void MainWindow::initParams()
{
    Flag_isOpen=0;
    video_name="noplaying-";
    player_full="E:/qt/qtCode/project/lezhi/mplayer_exe/mplayer.exe";//默认路径
    tmpVoiceVolume=ui->voiceSlider->value();
    videoIsPlaying = 0;
    newsCurIndex = 0;//"紧急消息"加粗变黑 内容红色,当前角码
    wkDay_num=1;//星期几
    jinjiNews = "测试滚动消息,超过部分不显示,接收服务器推送";
}

void MainWindow::playerTime()
{
    pVideoProcess->write("get_time_pos\n");  //获得视频当前时间
    pVideoProcess->write("get_percent_pos\n");  //获得视频百分比
    pVideoProcess->write("get_time_length\n");  // 获得视频总时间
    connect(pVideoProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(back_message_slots()));
}

void MainWindow::back_message_slots()
{
    while(pVideoProcess->canReadLine())
    {
        QByteArray b(pVideoProcess->readLine());
        b.replace(QByteArray("\n"), QByteArray(""));
        QString s(b);
        if (b.startsWith("ANS_LENGTH"))  //输出视频总时间
        {
            int totalTimeNum = s.mid(11).toFloat();  //直接toInt()不成功，不知道原因
            //int totalTimeDec = (int)(totalTimeNum * 10 % 10);
            int totalTimeSec = (int)(totalTimeNum) % 60;  //提取秒
            int totalTimeMin = (int)(totalTimeNum) / 60;  //提取分钟
            QString totalTime = QString("%1:%2").arg(totalTimeMin).arg(totalTimeSec);  //标准格式输出时间
            ui->label_2->setText(totalTime);
            ui->progressBar->setRange(0,totalTimeNum);
        }else if (b.startsWith("ANS_TIME_POSITION"))  //输出视频当前时间
        {
            int currentTimeNum = s.mid(18).toFloat();
            int currentTimeSec = (int)(currentTimeNum) % 60;
            int currentTimeMin = (int)(currentTimeNum) / 60;
            videoCurrentTime = QString("%1:%2").arg(currentTimeMin).arg(currentTimeSec);
            ui->label->setText(videoCurrentTime);
            ui->progressBar->setValue(currentTimeNum);
            //qDebug()<<"time"<<currentTimeNum;
        }else if(b.startsWith("ANS_PERCENT_POSITION"))
        {
            QString currentPercent = s.mid(21);
            //ui->label->setText(currentPercent + "%");  //视频播放进度百分比暂时不出输出
        }
    }
}

void MainWindow::timerTime()//显示时间 有延时->放到构造函数
{
    QDateTime sysTime = QDateTime::currentDateTime();
    ui->timeLabel->setFrameShape (QFrame::Box);
    ui->timeLabel->setText(sysTime.toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void MainWindow::weatherUpdate()//刷新天气数据
{
    if(wkDay_num<wkd_final)
    {
        if(wkDay_num<wkd_final)
        {
            /*weaLabel->setWeather(weatherList.at(wkDay_num++));//5转1的时候特别慢
            weaLabel2->setWeather(weatherList.at(wkDay_num++));
            weaLabel3->setWeather(weatherList.at(wkDay_num++));*/
        }else{
            wkDay_num=0;
            /*weaLabel->setWeather(weatherList.at(wkDay_num++));
            weaLabel2->setWeather(weatherList.at(wkDay_num++));
            weaLabel3->setWeather(weatherList.at(wkDay_num++));*/
        }
        qDebug()<<wkDay_num;
    }else{
        wkDay_num=1;
    }
}

void MainWindow::read_appUpdate(QNetworkReply*)
{
    qDebug("read_appUpdate");
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
    QString msg = socket->readAll();//接收第三方服务器发来的信息 本地
    qDebug()<<"收到紧急信息:"<<msg;//setJinjiText(msg);//设置紧急信息通知
    //ui->textEdit->clear();
    //ui->textEdit->append(msg);
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
    str = str;
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

void MainWindow::on_pushButton_clicked()
{
    video_full = QFileDialog::getOpenFileName(this,tr("打开视频文件"),"",tr("Medias (*.mp4 *.rmvb *.mkv *.avi *.3gp *.mov)"));
    videoInfo = QFileInfo(video_full);
    video_name = videoInfo.fileName();
    video_path = videoInfo.absolutePath();
    ui->pushButton_3->setDisabled(false);
    //qDebug()<<"video_name:"<<video_name;
    //qDebug()<<"video_path:"<<video_path;
}

void MainWindow::on_pushButton_2_clicked()
{
    player_full = QFileDialog::getOpenFileName(this);
    videoInfo = QFileInfo(player_full);
    player_name = videoInfo.fileName();
    player_path = videoInfo.absolutePath();
    //qDebug()<<"player_name:"<<player_name;
    //qDebug()<<"player_path:"<<player_path;
}

//打开/新建txt
//file io  http://www.cnblogs.com/stones-dream/p/9359889.html
void MainWindow::on_pushButton_12_clicked()
{
    QString txt_full = QFileDialog::getOpenFileName(this,tr("打开文本文件"),"",tr("file (*.txt)"));
    if(txt_full=="") return;
    //txt_file.read()
    QFile txt_file(txt_full);//QIODevice::WriteOnly  |
    if(!txt_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"出错","打开文件失败");
        return;
    }else{
        if(!txt_file.isReadable()) QMessageBox::warning(this,tr("错误"),tr("该文件不可读"));
        else{
            QTextStream textStream(&txt_file);//读取文件，使用QTextStream
            while(!textStream.atEnd())
            {
                ui->textEdit->setPlainText(textStream.readAll());
            }
            ui->textEdit->show();
            txt_file.close();
            Flag_isOpen = 1;
            Last_FileName = txt_full;
            qDebug()<<"Last_FileName:"<<Last_FileName;
        }
    }
}

//保存
//应用场景:1.看视频时输入几个字后点击生成笔记(word/pdf)带图和文字;2.按钮标记时刻
//菜单栏 新建(随机名用视频名-未保存) 生成Word/Pdf
//Ctrl+S保存快捷键,后弹出对话框,选择路径后写入[类似VS Code]
//新旧内容的隔开
void MainWindow::on_pushButton_13_clicked()
{
    QFile txt_file(Last_FileName);
    if(Flag_isOpen==1){
        if(!txt_file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            return;
        }else{
            QTextStream textStream(&txt_file);
            QString str = ui->textEdit->toPlainText();
            textStream<<video_name.left(video_name.length()-4)+" "+videoCurrentTime+":"+str;
            QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
            ui->textEdit->clear();
            /*Last_FileContent = str;
                        Last_FileName = fileName;
                        Flag_IsNew = 0;*/
            txt_file.close();
            Flag_isOpen=0;
        }
    }
}

//保存文档
void MainWindow::saveToFile(){
    //ui->textEdit->
}

void MainWindow::on_pushButton_3_clicked()//播放/暂停
{//https://blog.csdn.net/qq_35759050/article/details/53676081  mplayer例子
    if(videoIsPlaying!=1){
        if(video_full.isEmpty()) {QMessageBox::information(this,"播放失败","请选择视频文件");return;}
        if(player_name.isEmpty()) {QMessageBox::information(this,"播放失败","请选择播放器");return;}
        if(!video_full.isEmpty() && !player_name.isEmpty()){//播放 后期加入服务端的远程控制 如何循环播放 上下切换 降低延时
            on_pushButton_4_clicked();
            ui->pushButton->setVisible(false);
            ui->progressBar->setVisible(true);
            pVideoProcess = new QProcess();//kippprocess waitFor... system("killall mplayer")
            pVideoProcess->setProcessChannelMode(QProcess::MergedChannels);  //网上说必须设置
            playerTimer->start(10);
            QStringList playArg;//#if PC 不同平台
            playArg << "-slave";//调参
            playArg << "-quiet";
            playArg << "-zoom";
            //playArg << "-x";
            //playArg << "731";
            //playArg << "-y";
            //playArg << "411";
            playArg<<"-wid";//嵌入到某个窗口播放的命令
            playArg<<QString::number(ui->videoWidget->winId());//视频在指定窗口库播放
            //playArg << "-vo";
            //playArg << "x11";
            playArg<<video_full;//可选路径 可以是U盘文件 远程推送 目录下的
            qDebug()<<"playArg:"<<playArg;//playArg: ("-wid", "791326", "C:/Users/keji01/Desktop/4008.mp4")
            pVideoProcess->start(player_full,playArg);
            videoIsPlaying = 1;
            //ui->pushButton_3->setDisabled(true);
            ui->pushButton_3->setText("暂停");
        }
    }else if(videoIsPlaying==1){//暂停
        ui->pushButton_3->setText("播放");
        pVideoProcess->write("pause\n");
        videoIsPlaying=2;
    }
}

//结束
void MainWindow::on_pushButton_4_clicked()
{
    if(videoIsPlaying!=0) {
        ui->pushButton->setVisible(true);
        ui->pushButton_3->setText("播放");
        ui->pushButton_3->setDisabled(false);
        ui->progressBar->setValue(0);
        ui->progressBar->setHidden(true);
        pVideoProcess->write("quit\n");//system("killall mplayer");
        playerTimer->stop();
        pVideoProcess->kill();
        videoIsPlaying = 0;
    }
}

//静音
void MainWindow::on_pushButton_8_clicked()
{
    if(videoIsPlaying==1){
        if(voiceMute){
            pVideoProcess->write("mute 0\n");
            ui->pushButton_8->setText("静音");
        }else{
            pVideoProcess->write("mute 1\n");
            ui->pushButton_8->setText("声音");
        }
    }
}

//快退
void MainWindow::on_pushButton_7_clicked()
{
    pVideoProcess->write("pausing_keep seek -5 0\n");
}

//快进
void MainWindow::on_pushButton_6_clicked()
{
    pVideoProcess->write("pausing_keep seek +5 0\n");
}

//音量-
void MainWindow::on_pushButton_10_clicked()
{
    --tmpVoiceVolume;
    ui->voiceSlider->setVisible(true);
    pVideoProcess->write(QString("volume %1 2\n").arg(tmpVoiceVolume).toUtf8());
    ui->voiceSlider->setValue(tmpVoiceVolume);

    Sleep(2000);
    ui->voiceSlider->setVisible(false);
}

//音量+
void MainWindow::on_pushButton_9_clicked()
{//mplayerProcess->write(QString("seek %1 2\n").arg(value).toUtf8());  //视频进度拖放
    //->write("get_time_length\n");  //获得视频总得时间
    ++tmpVoiceVolume;
    ui->voiceSlider->setVisible(true);
    /*if(pVideoProcess->isReadable()){
     * ->write("volume +1 0\n");
    pVideoProcess->write(QString("volume %1 2\n").arg(tmpVoiceVolume).toUtf8());
    }*/
    ui->voiceSlider->setValue(tmpVoiceVolume);

    //Sleep(2000);慎用 比UI先执行的感觉
    //ui->voiceSlider->setVisible(false);
}
//全屏
void MainWindow::on_pushButton_5_clicked()
{
    pVideoProcess->write("vo_fullscreen\n");
}

//截屏
//https://blog.csdn.net/huangqi734044860/article/details/61194287
void MainWindow::on_pushButton_11_clicked()
{
    QScreen *screen=QGuiApplication::primaryScreen();
    QString filePathName = "E:/qt/qtCode/project/lezhi/lezhiClient/" + video_name.left(video_name.length() - 4).append("-");
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    filePathName += ".jpg";
    if(!screen->grabWindow(ui->videoWidget->winId()).save(filePathName, "jpg"))
    {
        qDebug()<<"save full screen failed";
    }

    saveToFile();
    //QPixmap pixmap = QApplication::screens().at(winId())->grabWindow(0,0,0,560,331);//400 400
    //pixmap.save("./screen.jpg");//保存 名字加视频名和视频秒+框里的输入
    //pixmap = pixmap.scaled(ui->label->size());
    //ui->label->setPixmap(pixmap);

    /*//创建线程
    ScreenThread *thread = new ScreenThread();
    thread->set_screen_show(ui->label,&mutex);
    //启动线程
    thread->start();*/
}

//焦点设置
//https://blog.csdn.net/qq_33233768/article/details/80173635
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->textEdit)
    {
        if (event->type()==QEvent::FocusIn)     	// 然后再判断控件的具体事件 (这里指获得焦点事件)
        {
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::green);
            ui->textEdit->setPalette(p);
        }
        else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
        {
            QPalette p=QPalette();
            p.setColor(QPalette::Base,Qt::white);
            ui->textEdit->setPalette(p);
        }
    }
    return QWidget::eventFilter(watched,event);// 最后将事件交给上层对话框
}

//时刻标记
void MainWindow::on_pushButton_14_clicked()
{
    ui->textEdit->append(videoCurrentTime+"  ");
    //ui->textEdit->fo
}
