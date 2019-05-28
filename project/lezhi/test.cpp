#include "mainwindow.h"
#include "ui_mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 
    m_bPressed = false;
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉窗口标题栏方式
    //setFixedHeight(30);  //设置菜单高度
    //this->setWindowTitle(QString("简播"));
 
 
    timeClock = new QTimer(this);
    connect(timeClock,SIGNAL(timeout()),this,SLOT(timeDone()));  //定时更新视频进度条
    //timeClock->start(10);
 
    ui->pushButton_6->setIcon(QIcon(":/icon/close_window.png"));
    ui->pushButton_6->setIconSize(QSize(20,20));
    ui->pushButton_6->setStyleSheet("QPushButton{border-radius: 5px;color:rgb(255, 255, 255);font: 75 16pt;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_10->setIcon(QIcon(":/icon/maximize_window.png"));
    ui->pushButton_10->setIconSize(QSize(20,20));
    ui->pushButton_10->setStyleSheet("QPushButton{border-radius: 5px;color:rgb(255, 255, 255);font: 75 16pt;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_11->setIcon(QIcon(":/icon/minimize_window.png"));
    ui->pushButton_11->setIconSize(QSize(20,20));
    ui->pushButton_11->setStyleSheet("QPushButton{border-radius: 5px;color:rgb(255, 255, 255);font: 75 16pt;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    //ui->pushButton_10->setFixedSize(22, 22);  //最大化按键
    //ui->pushButton_11->setFixedSize(22, 22);  //最小化按键
 
    ui->label_3->setPixmap(QPixmap(":/icon/media.png"));  //标题栏图标
    ui->label_3->setScaledContents(true);  //图标自动填充label
    ui->label_4->setStyleSheet("QLabel{border-radius: 10px;color:rgb(255, 255, 255);font: 75 14pt;}");  //标题栏文字说明
 
    mplayerProcess = new QProcess(this);  //新进程
    mplayerProcess->setProcessChannelMode(QProcess::MergedChannels);  //网上说必须设置
 
    ui->horizontalSlider->setStyleSheet("QSlider::groove:horizontal{border: 1px solid #4A708B;\
                                          background:#C0C0C0;\
                                          height:5px;\
                                          border-radius: 1px;\
                                          padding-left:-1px;padding-right:-1px;}"
 
                                          "QSlider::sub-page:horizontal {background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #B1B1B1, stop:1 #c4c4c4);\
                                          background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #5DCCFF, stop: 1 #1874CD);\
                                          border: 1px solid #4A708B;\
                                          height: 10px;\
                                          border-radius: 2px;}"
 
                                          "QSlider::add-page:horizontal{background: #575757;\
                                          border: 0px solid #777;\
                                          height: 10px;\
                                          border-radius: 2px;}"
 
                                          "QSlider::handle:horizontal{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\
                                          width: 11px;\
                                          margin-top: -3px;\
                                          margin-bottom: -3px;\
                                          border-radius: 5px;}"
 
                                          "QSlider::handle:horizontal:hover{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,stop:0.778409 rgba(255, 255, 255, 255));\
                                           width: 11px\
                                           margin-top: -3px;\
                                           margin-bottom: -3px;\
                                           border-radius: 5px;}"
 
                                           "QSlider::sub-page:horizontal:disabled {background: #00009C;\
                                           border-color: #999;}"
 
                                           "QSlider::add-page:horizontal:disabled {background: #eee;\
                                           border-color: #999;}"
 
                                           "QSlider::handle:horizontal:disabled {background: #eee;\
                                           border: 1px solid #aaa;\
                                           border-radius: 4px;}"
                                          );  //设置滑动条的风格
 
    ui->horizontalSlider_2->setStyleSheet("QSlider::groove:horizontal{border: 1px solid #4A708B;\
                                          background:#C0C0C0;\
                                          height:5px;\
                                          border-radius: 1px;\
                                          padding-left:-1px;padding-right:-1px;}"
 
                                          "QSlider::sub-page:horizontal {background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #B1B1B1, stop:1 #c4c4c4);\
                                          background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #5DCCFF, stop: 1 #1874CD);\
                                          border: 1px solid #4A708B;\
                                          height: 10px;\
                                          border-radius: 2px;}"
 
                                          "QSlider::add-page:horizontal{background: #575757;\
                                          border: 0px solid #777;\
                                          height: 10px;\
                                          border-radius: 2px;}"
 
                                          "QSlider::handle:horizontal{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\
                                          width: 11px;\
                                          margin-top: -3px;\
                                          margin-bottom: -3px;\
                                          border-radius: 5px;}"
 
                                          "QSlider::handle:horizontal:hover{background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,stop:0.778409 rgba(255, 255, 255, 255));\
                                           width: 11px\
                                           margin-top: -3px;\
                                           margin-bottom: -3px;\
                                           border-radius: 5px;}"
 
                                           "QSlider::sub-page:horizontal:disabled {background: #00009C;\
                                           border-color: #999;}"
 
                                           "QSlider::add-page:horizontal:disabled {background: #eee;\
                                           border-color: #999;}"
 
                                           "QSlider::handle:horizontal:disabled {background: #eee;\
                                           border: 1px solid #aaa;\
                                           border-radius: 4px;}"
                                          );  //设置滑动条的风格
 
    ui->pushButton_7->setIcon(QIcon(":/icon/media.png"));  //初始化按钮图标
    ui->pushButton_7->setIconSize(QSize(33,33));  //图标大小
    ui->pushButton_7->setStyleSheet("QPushButton{border-radius: 10px;color:rgb(255, 255, 255);font: 75 16pt;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");  //按键风格，鼠标划过变白，点击变绿
 
    ui->pushButton_2->setIcon(QIcon(":/icon/play.png"));  //暂停开始按键
    ui->pushButton_2->setIconSize(QSize(45,45));
    ui->pushButton_2->setStyleSheet("QPushButton{border-radius: 10px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_3->setIcon(QIcon(":/icon/forward.png"));  //快进按键
    ui->pushButton_3->setIconSize(QSize(37,37));
    ui->pushButton_3->setStyleSheet("QPushButton{border-radius: 10px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_4->setIcon(QIcon(":/icon/back.png"));  //后退按键
    ui->pushButton_4->setIconSize(QSize(37,37));
    ui->pushButton_4->setStyleSheet("QPushButton{border-radius: 10px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton->setIcon(QIcon(":/icon/stop.png"));   //停止按键
    ui->pushButton->setIconSize(QSize(37,37));
    ui->pushButton->setStyleSheet("QPushButton{border-radius: 10px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_5->setIcon(QIcon(":/icon/movie.png"));  //打开视频文件按键
    ui->pushButton_5->setIconSize(QSize(53,41));
    ui->pushButton_5->setStyleSheet("QPushButton{border-radius: 10px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_8->setIcon(QIcon(":/icon/music.png"));  //静音按键
    ui->pushButton_8->setIconSize(QSize(20,20));
    ui->pushButton_8->setStyleSheet("QPushButton{border-radius: 5px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_9->setHidden(true);  //按键隐藏
    ui->horizontalSlider->setHidden(true);  //滑动条隐藏
    ui->label->setHidden(true);  //label隐藏
    ui->label_2->setHidden(true);
    ui->label_2->setAlignment(Qt::AlignRight);  //右对齐
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
 
void MainWindow::mousePressEvent(QMouseEvent *event)  //鼠标单击
{
    if(event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}
 
void MainWindow::mouseMoveEvent(QMouseEvent *event)  //鼠标移动
{
    if(m_bPressed)
        move(event->pos() - m_point + pos());
}
 
void MainWindow::mouseReleaseEvent(QMouseEvent *event)  //鼠标释放
{
    Q_UNUSED(event);
    m_bPressed = false;
 
}
void MainWindow::back_message_slots()  //更新视频进度条的槽函数
{
    while(mplayerProcess->canReadLine())
        {
            QByteArray b(mplayerProcess->readLine());
 
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
 
                ui->horizontalSlider->setRange(0,totalTimeNum);
            }
 
            else if (b.startsWith("ANS_TIME_POSITION"))  //输出视频当前时间
            {
                int currentTimeNum = s.mid(18).toFloat();
 
                int currentTimeSec = (int)(currentTimeNum) % 60;
                int currentTimeMin = (int)(currentTimeNum) / 60;
 
                QString currentTime = QString("%1:%2").arg(currentTimeMin).arg(currentTimeSec);
                ui->label->setText(currentTime);
 
                ui->horizontalSlider->setValue(currentTimeNum);
                //qDebug()<<"time"<<currentTimeNum;
            }
 
            else if(b.startsWith("ANS_PERCENT_POSITION"))
            {
                QString currentPercent = s.mid(21);
                //ui->label->setText(currentPercent + "%");  //视频播放进度百分比暂时不出输出
            }
        }
}
 
void MainWindow::timeDone()  //定时槽函数
{
    mplayerProcess->write("get_time_pos\n");  //获得视频当前时间
    mplayerProcess->write("get_percent_pos\n");  //获得视频百分比
    mplayerProcess->write("get_time_length\n");  // 获得视频总时间
 
    connect(mplayerProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(back_message_slots()));  //信号函数与槽函数连接
}
 
///停止键
void MainWindow::on_pushButton_clicked()
{
 
    mplayerProcess->write("quit\n");  //视频停止
    mplayerProcess->kill();
    timeClock->stop();
    //timeClock->disconnect();
    ui->horizontalSlider->setValue(0);
    //ui->label->setText("00:00");
    //ui->label_2->setText("00:00");
 
    ui->pushButton_9->setHidden(true);
    ui->horizontalSlider->setHidden(true);
    ui->label->setHidden(true);
    ui->label_2->setHidden(true);
}
 
///暂停开始键
void MainWindow::on_pushButton_2_clicked()
{
    if(datas::pause == false)
    {
        //ui->pushButton_2->setIcon(QIcon(""));
        ui->pushButton_2->setIcon(QIcon(":/icon/play.png"));
        ui->pushButton_2->setIconSize(QSize(45,45));
        timeClock->stop();
        mplayerProcess->write("pause\n");
        datas::pause = true;
    }
 
    else
    {
        ui->pushButton_2->setIcon(QIcon(":/icon/pause.png"));
        ui->pushButton_2->setIconSize(QSize(45,45));
        timeClock->start(10);
        mplayerProcess->write("pause\n");
        datas::pause = false;
    }
}
 
///快进键10秒
void MainWindow::on_pushButton_3_clicked()
{
    mplayerProcess->write("pausing_keep seek +5 0\n");
}
 
///快退键10秒
void MainWindow::on_pushButton_4_clicked()
{
    mplayerProcess->write("pausing_keep seek -5 0\n");
}
 
///音量+ 暂时舍弃
/*void MainWindow::on_pushButton_6_clicked()
{
    mplayerProcess->write("volume +1 0\n");
}*/
 
///音量- 暂时舍弃
/*void MainWindow::on_pushButton_5_clicked()
{
    mplayerProcess->write("volume -1 0\n");
}*/
 
///屏幕中间打开视频文件按钮
void MainWindow::on_pushButton_7_clicked()
{
    ui->pushButton_2->setIcon(QIcon(":/icon/pause.png"));
    ui->pushButton_2->setIconSize(QSize(45,45));
 
    ui->pushButton_8->setIcon(QIcon(":/icon/music.png"));
    ui->pushButton_8->setIconSize(QSize(20,20));
 
    ui->pushButton_9->setIcon(QIcon(":/icon/expand.png"));
    ui->pushButton_9->setIconSize(QSize(22,22));
    ui->pushButton_9->setStyleSheet("QPushButton{border-radius: 1px;}"
                                    "QPushButton:hover{background-color:white; color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
    ui->pushButton_9->setHidden(false);
    ui->horizontalSlider->setHidden(false);
    ui->label->setHidden(false);
    ui->label_2->setHidden(false);
 
    mplayerProcess = new QProcess(this);
    mplayerProcess->setProcessChannelMode(QProcess::MergedChannels);
 
    timeClock->start(10);
 
    const QString mplayerPath("D:/Mplayer/mplayer.exe");
 
    //QString fileName;
    //fileName=QFileDialog::getOpenFileName(this,tr("打开视频文件"),"",tr("Videos (*.mp4 *.rmvb *.mkv *.avi *.3gp *.mov)"));
 
    QStringList args;
    args << "-slave";
    args << "-quiet";
    args << "-zoom";
    args << "-x";
    args << "871";
    args << "-y";
    args << "381";
    args << "-wid" << QString::number(ui->widget->winId());
    //args << "-vo";
    //args << "x11";
    //args << fileName;
    args << "D:/a.avi";
 
    mplayerProcess->start(mplayerPath,args);  //开始播放视频
 
    //datas::volume = ui->horizontalSlider_2->value();
    mplayerProcess->write(QString("volume %1 2\n").arg(ui->horizontalSlider_2->value()).toUtf8());  //音量初始化50%
    mplayerProcess->write("get_time_length\n");  //获得视频总得时间
 
    if(datas::mute == false)
    {
        ui->pushButton_8->setIcon(QIcon(":/icon/music.png"));
        ui->pushButton_8->setIconSize(QSize(20,20));
        mplayerProcess->write("mute 0\n");  //关闭静音
    }
    else
    {
        ui->pushButton_8->setIcon(QIcon(":/icon/quiet.png"));
        ui->pushButton_8->setIconSize(QSize(20,20));
        mplayerProcess->write("mute 1\n");  //静音
    }
 
    datas::pause = false;  //初始化暂停键中间变量
    datas::screen = false;  //全屏键中间变量
}
 
///静音与关静音
void MainWindow::on_pushButton_8_clicked()
{
    if(datas::mute == false)
    {
        ui->pushButton_8->setIcon(QIcon(":/icon/quiet.png"));
        ui->pushButton_8->setIconSize(QSize(20,18));
 
        mplayerProcess->write("mute 1\n");  //静音
        datas::mute = true;
    }
 
    else
    {
        ui->pushButton_8->setIcon(QIcon(":/icon/music.png"));
        ui->pushButton_8->setIconSize(QSize(20,20));
 
        mplayerProcess->write("mute 0\n");  //关静音
        datas::mute = false;
    }
}
 
///全屏
void MainWindow::on_pushButton_9_clicked()
{
    if(datas::screen == false)
    {
        ui->pushButton_9->setIcon(QIcon(":/icon/collapse.png"));
        ui->pushButton_9->setIconSize(QSize(27,27));
 
        mplayerProcess->write("vo_fullscreen\n");
 
        datas::screen = true;
    }
    else
    {
        ui->pushButton_9->setIcon(QIcon(":/icon/expand.png"));
        ui->pushButton_9->setIconSize(QSize(22,22));
 
        mplayerProcess->write("vo_fullscreen\n");
 
        datas::screen = false;
    }
    //args << "-wid" << GetDesktopWindow();
    //args << "-wid" << QString::number(ui->MainWindow->winId());
}
 
///视频进度水平滑块
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //if(timeClock->isActive())
        //timeClock->stop();
 
    //qDebug()<<value;
 
    /*if(qAbs(value - datas::tempValue)>5)
    {
        timeClock->stop();
        mplayerProcess->write(QString("seek %1 2\n").arg(value).toUtf8());
        QTime reachTime = QTime::currentTime().addMSecs(200);
        while(QTime::currentTime() < reachTime)
            //QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        timeClock->start(10);
    }*/
 
    //datas::tempValue = value;
 
    //timeClock->start(1);
 
}
 
///音量滑块
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    mplayerProcess->write(QString("volume %1 2\n").arg(value).toUtf8());
}
 
///打开视频文件按钮
void MainWindow::on_pushButton_5_clicked()
{
 
 
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,tr("打开视频文件"),"",tr("Medias (*.mp4 *.rmvb *.mkv *.avi *.3gp *.mov)"));
 
    if(!fileName.isEmpty())
    {
        mplayerProcess->write("quit\n");
        timeClock->stop();
        mplayerProcess->kill();
 
        ui->horizontalSlider->setValue(0);
        //ui->label->setText("00:00");
        //ui->label_2->setText("00:00");
 
        mplayerProcess = new QProcess(this);
        mplayerProcess->setProcessChannelMode(QProcess::MergedChannels);
 
        ui->pushButton_2->setIcon(QIcon(":/icon/pause.png"));
        ui->pushButton_2->setIconSize(QSize(45,45));
 
        ui->pushButton_9->setIcon(QIcon(":/icon/expand.png"));
        ui->pushButton_9->setIconSize(QSize(22,22));
        ui->pushButton_9->setStyleSheet("QPushButton{border-radius: 1px;}"
                                        "QPushButton:hover{background-color:white; color: black;}"
                                        "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
 
        ui->pushButton_9->setHidden(false);
        ui->horizontalSlider->setHidden(false);
        ui->label->setHidden(false);
        ui->label_2->setHidden(false);
 
        timeClock->start(10);
 
        const QString mplayerPath("D:/Mplayer/mplayer.exe");
 
        QStringList args;
        args << "-slave";
        args << "-quiet";
        args << "-zoom";
        //args << "-x";
        //args << "731";
        //args << "-y";
        //args << "411";
        args << "-wid" << QString::number(ui->widget->winId());  //视频在指定窗口库播放
        //args << "-vo";
        //args << "x11";
        args << fileName;
        //args << "D:/a.avi";
 
        mplayerProcess->start(mplayerPath,args);  //开始播放视频
 
        //datas::volume = ui->horizontalSlider_2->value();
        mplayerProcess->write(QString("volume %1 2\n").arg(ui->horizontalSlider_2->value()).toUtf8());  //音量初始化
        mplayerProcess->write("get_time_length\n");  //获得视频总得时间
 
        if(datas::mute == false)
        {
            ui->pushButton_8->setIcon(QIcon(":/icon/music.png"));
            ui->pushButton_8->setIconSize(QSize(20,20));
            mplayerProcess->write("mute 0\n");  //关闭静音
        }
        else
        {
            ui->pushButton_8->setIcon(QIcon(":/icon/quiet.png"));
            ui->pushButton_8->setIconSize(QSize(20,20));
            mplayerProcess->write("mute 1\n");  //静音
        }
 
        datas::pause = false;  //初始化暂停键中间变量
        datas::screen = false;  //全屏键中间变量
    }
}
 
///关闭按键
void MainWindow::on_pushButton_6_clicked()
{
    this->window()->close();
}
 
///最大化按键
void MainWindow::on_pushButton_10_clicked()
{
    this->window()->isMaximized() ? this->window()->showNormal() : this->window()->showMaximized();
    //this->window()->showFullScreen();
}
 
///最小化按键
void MainWindow::on_pushButton_11_clicked()
{
    this->window()->showMinimized();
}