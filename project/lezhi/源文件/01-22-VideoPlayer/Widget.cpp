#include "Widget.h"
#include "ui_Widget.h"
#include"BottomWidget.h"
#include<VideoWidget.h>
#include <Windows.h>
#include <ShellAPI.h>
#include<QDir>
#include<QString>
#include<QDebug>
#include<QPair>
#include<QPalette>
#include<QVector>
#include<QPushButton>
#include<QMultimedia>
#include<QSize>
#include<QGroupBox>
#include<QMediaPlayer>
#include<QModelIndex>
#include<QVideoWidget>
#include<QLabel>
#include<QScrollBar>
#include<QSizePolicy>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFile>
#include<QMenu>
#include<QAction>
#include<QList>
#include<QListWidget>
#include<QCursor>
#include<QFileDialog>
#include<QMap>
#include<QGridLayout>
#include<QTimer>
#include<iterator>
#include<QMultiMap>
#include<QLabel>
#include<QComboBox>
#include<QDir>
#include<QUrl>
#include<QRect>
#include<QStyle>
#include<QTextCodec>
#include<QMessageBox>
#include<QMediaContent>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QSqlTableModel>
#include <QApplication>
#include<QDesktopWidget>
#include<QTime>
#include<QFileInfo>
#include<QDesktopServices>

QPoint Widget::Position(QPoint(0,0));

Widget::Widget(QWidget *parent) :
    QWidget(parent), PADDING(2), buttonHeight(20),buttonWidth(20), clickCount(1),isLeftPressDown(false),
    dir(NONE),  ui(new Ui::Widget), windowIniWidth((QApplication::desktop()->availableGeometry().width())*29/48),
    playingIndex(-1),                          windowIniHeight((QApplication::desktop()->availableGeometry().height())*20/27),
                                     screenWidth(QApplication::desktop()->availableGeometry().width()),
                                     screenHeight(QApplication::desktop()->availableGeometry().height())

{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    //this->setStyleSheet("QWidget{background-color:rgb(0,91,172);}");
    this->setStyleSheet("QWidget{background-color:rgb(60,65,68);}");
    setWindowOpacity(1);//设置透明度
    this->setMinimumHeight(500);
    this->setMinimumWidth(720);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint); // 设置成无边框对话框
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
    //this->setAcceptDrops(true);    //设置可以接受拖拽

    normalRect.setWidth(windowIniWidth);
    normalRect.setHeight(windowIniHeight);

    setThreeButton();

    volumeWidgetEntered = false;
    playModeWidgetEntered = false;
    isVideoMouseLeftDown=false;


    //左上角的菜单
    menuButton = new QPushButton(this);

    menuButton->setGeometry(10,10,70,23);
    menuButton->setStyleSheet("QPushButton{ border-radius:8px; border: none; background-color:rgb(120,125,128);}"
                                                  "QPushButton:hover{background-color:rgb(200,200,201);} "
                                                  "QPushButton:checked{background-color:rgb(0,0,1);}"
                              );
//90,190,81        0,90,171
    titleLabel = new QLabel(this);
    titleLabel->setGeometry(100,10,500,20);
    titleLabel->setStyleSheet("QLabel{color:rgb(200,200,200); background-color:rgb(60, 65, 68)}");

    menu = new QMenu;
    openAction = menu->addAction("打开");
    menu->setStyleSheet(" QMenu{border:none } "
                        "QMenu::item{border:none; font-size:13px;  padding-left:20px; background-color:white; height:25px; width:50px; }"
                         "QMenu::item:selected{ background-color:rgb(140,140,240)}");

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()));
    menuButton->setMenu(menu);



    groupBox = new QWidget(this);
    groupBox->setGeometry(0,50,normalRect.width()-200, normalRect.height()-49);
    groupBox->setStyleSheet("QWidget{ border-top-left-radius:0px;  border-top-right-radius:0px;  background-color:rgb(0,0,0)}");
    groupBox->setMouseTracking(true);

    //播放窗口
    videoWidget0 = new VideoWidget(groupBox);
    videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());


    //用于放置底部的所有按钮
    bottomWidget = new BottomWidget(this);
    bottomWidget->setFixedHeight(120);
    bottomWidget->setGeometry(0, normalRect.height()-80, normalRect.width()-201, 80);
    //bottomWidget->setStyleSheet("QWidget{background-color:rgba(30,35,38,0.6))}");
    bottomWidget->setStyleSheet("QWidget{background-color:rgb(40,40,40)}");
    bottomWidget->setCursor(QCursor(Qt::ArrowCursor));
    //connect(bottomWidget, &BottomWidget::signalMovePoint, this, &Widget::slotSignalMovePoint );
    connect(bottomWidget, SIGNAL(signalMovePoint(QPoint)), this, SLOT(slotSignalMovePoint(QPoint)));
    connect(bottomWidget, SIGNAL(signalLeftPressDown(bool)), this, SLOT(slotVideoWidgetMouseLeftDown(bool)));

    //播放列表
    listWidget = new ListWidget(this);
    listWidget->installEventFilter(this);
    listWidget->setGeometry(normalRect.width()-201, 50, 200, normalRect.height()-49);

    hideButton = new QPushButton(this);
    //hideButton->setWindowOpacity(0.6);
    hideButton->setGeometry(normalRect.width()-220,(listWidget->height())/2, 20,70);
    hideButton->setStyleSheet("QPushButton{background-color:rgba(80,80,80,0.5);}"
                                                   "QPushButton:hover{background-color:rgba(80,80,80,0.8);}");
    connect(hideButton, &QPushButton::clicked, this, &Widget::slotHideButton);

    //停止按钮
    stopButton = new QPushButton(bottomWidget);
    //stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    //stopButton->setGeometry(20, normalRect.height()-40, 40, 30);
    stopButton->setGeometry(20,25,40,40);
    stopButton->setStyleSheet("QPushButton{image:url(stop.png); border-radius:20px; background-color: rgb(40,40,40)}"
                                                "QPushButton::hover{background-color: rgb(90,90,90);  image:url(stopHovered.png);}");
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(slotStopVideo()));

    //上一曲按钮
    lastVideoButton =  new QPushButton(bottomWidget);
    //lastVideoButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
   // QString name = QDir::currentPath();
    //QPixmap backwardIcon((name+"/backward.png"));
    //lastVideoButton->setIcon(backwardIcon);
    //lastVideoButton->setIconSize(QSize(40,40));

    //lastVideoButton->setGeometry(70,normalRect.height()-40, 40,30);
    lastVideoButton->setGeometry(70, 25, 40, 40);
    lastVideoButton->setStyleSheet("QPushButton{image:url(backward.png);border-radius:20px; background-color: rgb(40,40,40)}"
                                   "QPushButton:hover{background-color: rgb(90,90,90); image:url(backwardHovered.png)}");
    connect(lastVideoButton, SIGNAL(clicked(bool)), this, SLOT(slotLastVideo()));

    //播放按钮
    playButton = new QPushButton(bottomWidget);
    //playButton->setEnabled(false);
    //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setGeometry(120, 20, 50, 50);
    playButton->setStyleSheet("QPushButton{image:url(play.png);  border-radius:25px; background-color: rgb(40,40,40)}"
                                                "QPushButton::hover{background-color: rgb(90,90,90); image:url(playHovered.png)}");
    connect(playButton, SIGNAL(clicked()), this, SLOT(slotPlayOrPause()));

    //下一曲按钮
    nextVideoButton = new QPushButton(bottomWidget);
    //nextVideoButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    nextVideoButton->setGeometry(180, 25, 40, 40);
    nextVideoButton->setStyleSheet("QPushButton{image:url(forward.png);border-radius:20px; background-color: rgb(40,40,40)}"
                                                         "QPushButton::hover{background-color: rgb(90,90,90);  image:url(forwardHovered.png)}");
    connect(nextVideoButton, SIGNAL(clicked(bool)), this, SLOT(slotNextVideo()));

    //滑动条
    slider = new MainSlider(Qt::Horizontal, bottomWidget);
    slider->setRange(0,0);
    slider->setGeometry(10, 7, normalRect.width()-225, 13);
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(slotSetValue(int)));


    //音量按钮
    volumeButton = new QPushButton(bottomWidget);
    volumeButton->setGeometry(bottomWidget->width()-80,35, 30,30);
    volumeButton->setStyleSheet("QPushButton{image:url(volume.png);border-radius:15px; background-color: rgb(40,40,40)}"
                                                         "QPushButton::hover{ image:url(volumeHovered.png);border-color:1px black; background-color:rgb(90,90,90);}");
    volumeButton->installEventFilter(this);
    volumeWidget = new QWidget(this);
    volumeWidget->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint); // 设置成无边框对话框
    volumeWidget->setStyleSheet("background-color:rgb(25, 38, 58)");
    volumeWidget->setFixedWidth(30);
    volumeWidget->installEventFilter(this);   //安装事件过滤器
    volumeSlider = new VolumeSlider(Qt::Vertical, this);
    volumeSlider->setRange(0,100);
    volumeSlider->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *volumeLayout =  new QVBoxLayout;
    volumeLayout->addWidget(volumeSlider);
    volumeWidget->setLayout(volumeLayout);
    volumeWidget->hide();

    //播放模式按钮
    playModeButton = new QPushButton(bottomWidget);
    playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
    playModeButton->setStyleSheet("QPushButton{border-radius:15px; background-color: rgb(40,40,40)}"
                                                         "QPushButton::hover{ background-color:rgb(160,160,245);}");
    playModeButton->installEventFilter(this);

    //播放模式菜单
    playModeListWidget = new QListWidget(this);
    playModeListWidget->addItem(QString("播放一次"));
    playModeListWidget->addItem(QString("单曲循环"));
    playModeListWidget->addItem(QString("顺序播放"));
    playModeListWidget->addItem(QString("列表循环"));
    playModeListWidget->addItem(QString("随机播放"));
    playModeListWidget->installEventFilter(this);
    playModeListWidget->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint); // 设置成无边框对话框
    playModeListWidget->setStyleSheet("QListWidget{border:none;}"
                                                               "QListWidget::item{background-color:white; font-size:25px;"
                                                                                             " padding-top:5px; padding-left:10px; padding-bottom:5px; "
                                                                                             " padding-right:10px; }"
                                                               "QListWidget::item:hover{background-color:rgb(210,210,210); color:rgb(30,30,30)}"
                                                               "QListWidget::item:selected{background-color:rgb(180,180,180); color:black}");
    playModeListWidget->hide();
    connect(playModeListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(slotPlayModeListWidget()));



    //显示时间的标签
    presentTimeLabel = new QLabel(bottomWidget);
    presentTimeLabel->setGeometry(260, 30, 45, 30);
    //presentTimeLabel->setStyleSheet("QLabel{background-color:rgb(190,190,80);}");
    presentTimeLabel->setStyleSheet("QLabel{color:rgb(250,250,250); background-color:rgb(0, 0, 0);}");

    totalTimeLabel = new QLabel(bottomWidget);
    totalTimeLabel->setGeometry(300, 30, 50, 30);
   // totalTimeLabel->setStyleSheet("QLabel{background-color:rgb(190,190,80);}");
    totalTimeLabel->setStyleSheet("QLabel{color:rgb(250,250,250); background-color:rgb(0, 0, 0);}");


    //播放者
    mediaPlayer0 = new QMediaPlayer;
    mediaPlayer0->setVideoOutput(videoWidget0);
    connect(mediaPlayer0, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(slotStateChanged(QMediaPlayer::State)));
    connect(mediaPlayer0, SIGNAL(positionChanged(qint64)), this, SLOT(slotPositionChanged(qint64)));
    connect(mediaPlayer0, SIGNAL(durationChanged(qint64)), this, SLOT(slotDurationChanged(qint64)));
    connect(mediaPlayer0, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(slotHandleError()));

    connect(volumeSlider, SIGNAL(sliderMoved(int)), mediaPlayer0, SLOT(setVolume(int)));//响应声音滑动条的移动
    connect(volumeSlider, SIGNAL(signalPressVolumePosition(qint64)), this, SLOT(slotPressVolumePosition(qint64)));

    connect(slider, SIGNAL(signalPressPosition(qint64)), this, SLOT(slotSignalPressPosition(qint64 )));

    connect(listWidget, SIGNAL(ItemDoubleClick(QString)), this, SLOT(slotListWidgetItemDoubleClick(QString)));
    connect(listWidget, SIGNAL(ItemDeleted(int)), this, SLOT(slotListWidgetItemDeleted(int)));
    connect(listWidget, &ListWidget::signalClearAll, this, &Widget::slotListWidgetClearAll);
    connect(listWidget, &ListWidget::signalActionOpen, this, &Widget::slotListWidgetActionOpen);
    connect(listWidget, &ListWidget::signalClearValidItem, this, &Widget::slotListWidgetClearValidItem);
    connect(listWidget, &ListWidget::signalOpenDirectory, this, &Widget::slotListWidgetOpenDirectory);

    connect(videoWidget0, SIGNAL(signalInBottomRegion()), this, SLOT(slotInBottomRegion()));
    connect(videoWidget0, SIGNAL(signalOutBottomRegion()), this, SLOT(slotOutBottomRegion()));
    connect(videoWidget0, &VideoWidget::signalInRightRegion, this, &Widget::slotInRightRegion);
    connect(videoWidget0, &VideoWidget::signalOutRightRegion, this, &Widget::slotOutRightRegion);
    connect(videoWidget0, SIGNAL(signalMovePoint(QPoint)), this, SLOT(slotSignalMovePoint(QPoint)));
    connect(videoWidget0, SIGNAL(signalLeftPressDown(bool)), this, SLOT(slotVideoWidgetMouseLeftDown(bool)));
    connect(videoWidget0, SIGNAL(doubleClicked()), this, SLOT(slotVideoWidgetDoubleClicked()));
    connect(videoWidget0, &VideoWidget::signalDropedList, this, &Widget::slotVideoWidgetDropedList);
    connect(videoWidget0, &VideoWidget::signalActionOpen, this, &Widget::slotOpenFile);
    connect(videoWidget0, &VideoWidget::signalActionInfo, this, &Widget::slotVideoWidgetActionInfo);

    iniDatabase();
}



Widget::~Widget()
{
    delete ui;
}

void Widget::addFile(const QString fileName)
{
    if(!fileName.isEmpty())
    {
        QString name = getNameFromPath(fileName);   //从路径中获取文件名字
        //titleLabel->setText(name);
        int i;
        for(i=0;i<vector.size();i++)
        {
            if(vector.at(i).first.second == fileName)   //该文件已经存在
            {
                //playList->setCurrentIndex(i);
                playingIndex=i;
                mediaPlayer0 ->setMedia(QUrl::fromLocalFile(fileName));
                mediaPlayer0->play();
                listWidget->setCurrentRow(i);
                listWidget->setIndex(i);
                titleLabel->setText(removeIndexFromAppend(vector.at(i).second));
                break;
            }
        }
        if(i == vector.size())   // 相等说明不存在，则插入
        {
            //qDebug()<<"相等说明不存在，则插入";
            int j=0;
            QString theGoal;
            for(j=0; j<vector.size(); j++)
            {
                //存在不同路径但是有相同名字的name, 则查找nameAppendIndex中最大的序号
                if(name == vector.at(j).first.first)
                {
                      //qDebug()<<" if(vector.at(i).first.first == name)";
                      theGoal = vector.at(j).second;
                }
            }
            if(!theGoal.isEmpty())//theGoal非空， 说明有相同的name，此时要加上序号了
            {
                //qDebug()<<"theGoal非空， 说明有相同的name，此时要加上序号了";
                int n=(theGoal.right(2)).left(1).toInt();   //查找到该序号，即将插入的项序号需要比此序号大一
                QString nameAppend = name+"("+QString::number(n+1)+")";
                QPair<QString, QString>pairFirst(name, fileName);
                QPair<QPair<QString, QString>, QString> pair(pairFirst, nameAppend);
                vector.push_back(pair);


                //qDebug()<<"updatetoBase";
                QSqlTableModel mediaTableModel;
                mediaTableModel.setTable("mediatable");
                mediaTableModel.select();
                //mediaTableModel.clear();
                QSqlRecord record = mediaTableModel.record();

                QString index=QString::number(vector.size()-1);
                record.setValue(0,index);
                record.setValue(1,name);
                record.setValue(2, fileName);
                record.setValue(3, nameAppend);
                mediaTableModel.insertRecord(-1,record);
                mediaTableModel.submitAll();

                QListWidgetItem * item = new QListWidgetItem(nameAppend);
                qDebug()<<"nameAppend:  "<<nameAppend;
                titleLabel->setText(nameAppend);
                listWidget->addItem(item);

            }

            else //说明没有和name一样的，则直接插入
            {
                //qDebug()<<" else //说明没有和name一样的，则直接插入";
                QPair<QString, QString>pairFirst(name, fileName);
                QString nameAppend = name+"(0)";
                QPair<QPair<QString, QString>, QString> pair(pairFirst, nameAppend);
                vector.push_back(pair);


                //qDebug()<<"updatetoBase";
                QSqlTableModel mediaTableModel;
                mediaTableModel.setTable("mediatable");
                mediaTableModel.select();
                //mediaTableModel.clear();
                QSqlRecord record = mediaTableModel.record();
                QString index=QString::number(vector.size()-1);
                 record.setValue(0,index);
                 record.setValue(1,name);
                 record.setValue(2, fileName);
                 record.setValue(3, nameAppend);
                 mediaTableModel.insertRecord(-1,record);
                 mediaTableModel.submitAll();

                QListWidgetItem * item = new QListWidgetItem(name);
                //qDebug()<<"item:  "<<item->text();
                titleLabel->setText(name);
                listWidget->addItem(item);
            }

            if(!playButton->isEnabled())
            {
                playButton->setEnabled(true);
            }
            mediaPlayer0 ->setMedia(QUrl::fromLocalFile(fileName));
            mediaPlayer0->play();
            playingIndex = vector.size()-1;
            volumeSlider->setValue(mediaPlayer0->volume()); //修改声音滑动条
            listWidget->setCurrentRow(playingIndex);
            listWidget->setIndex(playingIndex);

        }
    }
}

//数字显示转换为时间显示
QString Widget::digitalToTime(const int& number)
{
    QString timeString;
    QString minuteString;
    QString secondString;
    int a = number / 60;   //得到分钟数
    int b = number % 60; //得到秒数

    //规整一下秒数,使其为两位数
    if(b<10)
    {
        secondString.append("0");
    }
    secondString.append(QString::number(b));

    //规整一下分钟数,使其为两位数
    if(a<10)
    {
        minuteString.append("0");
    }
    minuteString.append(QString::number(a));

    timeString.append(minuteString).append(":").append(secondString);
    return timeString;

}

//事件过滤器
bool Widget::eventFilter(QObject *target, QEvent *event)
{
    QTimer * volumeTimer     = new QTimer;
    QTimer * playModeTimer = new QTimer;
    //声音按钮
    if(target == volumeButton)
    {
        if(event->type() == QEvent::Enter)
        {
            //相对于整个窗体的坐标
            //qDebug()<<"volume";
            QPoint point = bottomWidget->pos() + volumeButton->pos() - QPoint(0,120);
            volumeWidget->show();
            volumeWidget->setGeometry( point.x(), point.y(), volumeWidget->sizeHint().width(), volumeWidget->height());
            //volumeWidget->setGeometry( 0, 0,  volumeWidget->sizeHint().width(), volumeWidget->height());
        }
        else if(event->type() == QEvent::Leave)
        {
            connect(volumeTimer, SIGNAL(timeout()), this, SLOT(slotVolumeTimer()));
            volumeTimer->setSingleShot(true);
            volumeTimer->start(600);
            volumeWidgetEntered = false;

        }
    }

    //声音控件
    if(target == volumeWidget)
    {
        if(event->type() == QEvent::Enter)
        {
            //qDebug()<<"volumeWidget";
            volumeWidgetEntered = true;

        }
        else if(event->type() == QEvent::Leave)
        {
            volumeWidget->hide();
        }
    }

    //播放模式按钮
    if(target == playModeButton)
    {
        if(event->type() == QEvent::Enter)
        {
            //qDebug()<<"enter";
            QPoint point = bottomWidget->pos() + playModeButton->pos() - QPoint(45,165);
            playModeListWidget->show();
            playModeListWidget->setGeometry( point.x(), point.y(), 80,145);
            playModeListWidget->setCursor(QCursor(Qt::ArrowCursor));
        }
        else if(event->type() == QEvent::Leave)
        {
            connect(playModeTimer, SIGNAL(timeout()), this, SLOT(slotPlayModeTimer()));
            playModeTimer->setSingleShot(true);
            playModeTimer->start(600);
            playModeWidgetEntered = false;

        }
    }

    //播放模式列表控件
    if(target == playModeListWidget)
    {
        if(event->type() == QEvent::Enter)
        {

            playModeWidgetEntered = true;

        }
        else if(event->type() == QEvent::Leave)
        {
            playModeListWidget->hide();
        }
    }

    //离开窗体时自动隐藏bottomWidget
    if(target == this)
    {
        if(event->type() == QEvent::Leave)
        {
            slotOutBottomRegion();
        }
    }

    if(target == listWidget)
    {
        if(event->type() == QEvent::Enter)
        {
            slotOutRightRegion();
        }
    }
}

//从路径中得到文件名字
QString Widget::getNameFromPath(const QString &fileName)
{
    QString name;
    QChar c;
    QString s = fileName.toUtf8().data();
    foreach(c, s)
    {
        if(c =='/')
        {
            name.clear();
            continue;
        }
        name.append(c);
    }
    //name = name.toUtf8().data();     //解决name中文乱码问题
    return name;
}

//使用数据库的数据初始化
void Widget::iniDatabase()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("media.db");
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("localhost");
//    db.setDatabaseName("media");
//    db.setUserName("multin");
//    db.setPassword("drama");


    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),db.lastError().text());
    }
    else
    {


        QSqlQuery query;
        //query.exec("create database media");
        if(!query.exec("CREATE TABLE mediatable(ind VARCHAR(777), name VARCHAR(777), fileName VARCHAR(777), nameAppend VARCHAR(777))"))
        {
            qDebug()<<query.lastError().text();
        }
        if(!query.exec("CREATE TABLE setting(volume VARCHAR(777), playMode VARCHAR(777))"))
        {
            qDebug()<<query.lastError().text();
        }

        QSqlTableModel settingModel;
        settingModel.setTable("setting");
        settingModel.select();
        QSqlRecord record=settingModel.record(0);

        volumeSlider->setValue(record.value(0).toInt());
        playModeListWidget->setCurrentRow(record.value(1).toInt());

        QSqlTableModel mediaTableModel;
        mediaTableModel.setTable("mediatable");
        mediaTableModel.select();
        int ret = mediaTableModel.rowCount();
        for(int i=0; i<ret;i++)
        {
            QSqlRecord record=mediaTableModel.record(i);
            QString name=record.value(1).toString();
            QString fileName = record.value(2).toString();
            QString nameAppend = record.value(3).toString();
            QPair<QString, QString> pair1(name, fileName);
            QPair<QPair<QString, QString>, QString>pair(pair1,nameAppend);
            vector.push_back(pair);
            //playList->addMedia(QUrl::fromLocalFile(fileName));
            listWidget->addItem(removeIndexFromAppend(nameAppend));

            if(vector.isEmpty())
                playButton->setEnabled(false);
            else
                playButton->setEnabled(true);
        }
        //qDebug()<<"inidatabase finished";
    }

}

//得到方向
void Widget::region(const QPoint &cursorGlobalPoint)
{

    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y())
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

//过滤序号
QString Widget::removeIndexFromAppend( QString name)
{
    QString temp = name.right(2);
    temp=temp.left(1);
    if(temp=="0")
    {
        return (name.remove(name.size()-3, 3));
    }
    else
    {
        //qDebug()<<"temp!=0";
        return name;
    }
}

void Widget::enterEvent(QMouseEvent *event)
{
    qDebug()<<"enter";
}

void Widget::leaveEvent(QMouseEvent * event)
{
    qDebug()<<"leave";
    QWidget::leaveEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{

    mouseGlobalPos = event->globalPos();
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown)  //如果左键没有按下，则更新鼠标相对于Widget的位置信息
    {
        this->region(gloPoint);
    }
    else
    {
        if(dir != NONE)
        {
            QRect rMove(tl, rb);

            switch(dir) {   //处于边框拖动的状态
            case LEFT:
              if(rb.x() - gloPoint.x() <= this->minimumWidth())
                   rMove.setX(tl.x());
              else
                  rMove.setX(gloPoint.x());
             //   rMove.setWidth(rb.x()-gloPoint.x());    //以右边界为标准变化， 左边不变，所以不能用
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());

                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());

                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());                   //以上边界为标准变化， 左边不变，所以不能用
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
               rMove.setWidth(gloPoint.x() - tl.x());
               if(rb.y() - gloPoint.y() <= this->minimumHeight())
                   rMove.setY(tl.y());
               else
               rMove.setY(gloPoint.y());    //May change the height, but will never change the bottom edge of the rectangle.

                break;
            case LEFTBOTTOM:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                     rMove.setX(tl.x());
                else
                     rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());

                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        }
        else if(isMaximized())  //处于最大化
        {
            double percent= static_cast<double>(event->globalPos().x() ) / static_cast<double>(screenWidth);
            slotSetButton();
            double repaint = event->globalPos().x() - normalRect.width() * percent;    //重绘窗口的起始X坐标
            if( gloPoint.x() < (normalRect.width() - 100) )  // 靠在左上边窗口
            {
                this->setGeometry(0, 0, normalRect.width(), normalRect.height());
            }
            else if ( screenWidth - normalRect.width()+100<gloPoint.x() )  //靠在右上边窗口
            {
                this->setGeometry( screenWidth - normalRect.width(),  0,  normalRect.width(), normalRect.height() );
            }
            else     //正常情况下居中显示
            {
                this->setGeometry(repaint, 0, normalRect.width(), normalRect.height() );
            }
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();   //紧接着设置新的移动位置
        }
        else
        {
            move(event->globalPos()-dragPosition );
        }
        int a=this->rect().topRight().x();
        normalRect = this->rect();
        //qDebug()<<"normalRect: "<<normalRect;
        menuButton->setGeometry(10,10,70,23);
        closeButton->setGeometry(a-34, 10, 28, 20);     //将关闭按钮放在最右上角
        maximumButton->setGeometry(a-68,10, 28, 20);
        minimumButton->setGeometry(a-102, 10, 28, 20);   //按钮之间间隔6px
        /*
        groupBox->setGeometry(0,50,this->rect().topRight().x()-200,   this->rect().bottomRight().y()-49);    //设置主窗口
        //listWidget->setGeometry(normalRect.width()-201, 50, 200, normalRect.height()-120);
        listWidget->setGeometry(normalRect.width()-201, 50, 200, normalRect.height()-49);

        bottomWidget->setGeometry(0, normalRect.height()-70, normalRect.width()-201, 70);
        slider->setGeometry(10, 10, normalRect.width()-225, 13);
        volumeButton->setGeometry(bottomWidget->width()-80,40, 30,20);
        playModeButton->setGeometry(bottomWidget->width()-45,40, 30,20);   */
        if(listWidget->isVisible())//列表显示
        {
           // videoWidget0->setGeometry(0,  50,  normalRect.topRight().x()-200,   normalRect.bottomRight().y()-49);    //设置主窗口
            groupBox->setGeometry(0,  50,  normalRect.topRight().x()-200,   normalRect.bottomRight().y()-49);    //设置主窗口
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            listWidget->setGeometry(normalRect.width()-201, 50, 200, normalRect.height()-49);
            hideButton->setGeometry(normalRect.width()-220,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, normalRect.height()-80, normalRect.width()-201, 80);
            slider->setGeometry(10, 7, normalRect.width()-225, 13);
            //volumeButton->setGeometry(bottomWidget->width()-80,40, 30,20);
            volumeButton->setGeometry(bottomWidget->width()-80,35, 30,30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
        else//列表隐藏
        {
            //videoWidget0->setGeometry(0,  50,  normalRect.topRight().x(),   normalRect.bottomRight().y()-49);    //设置主窗口
            groupBox->setGeometry(0,  50,  normalRect.topRight().x()-1,   normalRect.bottomRight().y()-49);    //设置主窗口
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(normalRect.width()-20,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, normalRect.height()-80, normalRect.width(), 80);
            slider->setGeometry(10, 7, normalRect.width()-25, 13);
            volumeButton->setGeometry(bottomWidget->width()-80,35, 30,30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    //qDebug()<<isLeftPressDown;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    switch(event->button()) {
    case Qt::LeftButton:
        //slotAction();
        isLeftPressDown = true;
        if(dir != NONE)
        {
            this->mouseGrabber();
        }
        else
        {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    case Qt::RightButton:
        //this->close();
        break;
    default:
       // QMouseEvent::mousePressEvent(event);
        break;
    }
}

//鼠标双击事件
void Widget::mouseDoubleClickEvent(QMouseEvent* event)
{
    slotSetButton();
}

void Widget::slotCloseWidget()
{
    int pointX =this->pos().x();
    int pointY =this->pos().y();
    int temp = normalRect.height();
    this->setMinimumSize(0,0);
    for(int i=0; i<normalRect.height()/2;++i)
    {
        pointY += 10;
        temp -= 20;
        this->setGeometry(pointX, pointY, normalRect.width(), temp);
        groupBox->setGeometry(0,  50, normalRect.width()-200,   temp-49);
        videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
        //videoWidget0->setGeometry(0,  50, normalRect.width()-201,   temp-49);
    }
    this->close();
}

//显示错误
void Widget::slotHandleError()
{
    qDebug()<<"Error:  " << mediaPlayer0->errorString();
}

//设置隐藏按钮
void Widget::slotHideButton()
{
    listWidget->setVisible(!listWidget->isVisible());
    if(!listWidget->isVisible())//隐藏时
    {
        if(this->isMaximized())
        {
            //videoWidget0->setGeometry(0,  50, screenWidth,   screenHeight-49);
            groupBox->setGeometry(0,  50, screenWidth,   screenHeight-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(screenWidth-20,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, screenHeight-80, screenWidth, 80);  //bottomWidget->show();
            slider->setGeometry(10, 7, screenWidth-25, 13);
            volumeButton->setGeometry(bottomWidget->width()-80,35, 30,30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
       else
        {
            //videoWidget0->setGeometry(0,  50, normalRect.width(),   normalRect.height()-49);
            groupBox->setGeometry(0,  50, normalRect.width()-1,   normalRect.height()-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(normalRect.width()-20,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0,  normalRect.height()-80, normalRect.width(), 80);//bottomWidget->show();
            slider->setGeometry(10, 7, normalRect.width()-25, 13);
            volumeButton->setGeometry(bottomWidget->width()-80, 35, 30, 30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
    }
    else//listWidget显示
    {
        if(this->isMaximized())//最大化时
        {
            //videoWidget0->setGeometry(0,  50, screenWidth-201,   screenHeight-49);
            groupBox->setGeometry(0,  50, screenWidth-200,   screenHeight-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(screenWidth-220,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, screenHeight-80, screenWidth-201, 80);
            slider->setGeometry(10, 7, screenWidth-225, 13);
            volumeButton->setGeometry(bottomWidget->width()-80, 35, 30,30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
        else
        {
            //videoWidget0->setGeometry(0,  50, normalRect.width()-201,   normalRect.height()-49);
            groupBox->setGeometry(0,  50, normalRect.width()-200,   normalRect.height()-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(normalRect.width()-220,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0,  normalRect.height()-80, normalRect.width()-201, 80);//bottomWidget->show();
            slider->setGeometry(10, 7, normalRect.width()-225, 13);
            volumeButton->setGeometry(bottomWidget->width()-80,35, 30, 30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
    }


}

//鼠标进入目标区域
void Widget::slotInBottomRegion()
{
    //qDebug()<<"in";
    bottomWidget->show();
    inBottomRegion = true;
}

void Widget::slotInRightRegion()
{
    hideButton->show();
    inRightRegion = true;
}

//使用videoWidget0移动窗体
void Widget::slotSignalMovePoint(QPoint point)
{

    if(this->isMaximized())
    {
        QPoint posi = this->mapToGlobal(this->cursor().pos());
        //qDebug()<<"posi:   "<<posi;
        double percent= static_cast<double>(posi.x() ) / static_cast<double>(screenWidth);
        slotSetButton();
        double repaint = posi.x() - normalRect.width() * percent;    //重绘窗口的起始X坐标
        if( posi.x() < (normalRect.width() - 100) )  // 靠在左上边窗口
        {
            this->setGeometry(0, 0, normalRect.width(), normalRect.height());
        }
        else if ( screenWidth - normalRect.width()+100<posi.x() )  //靠在右上边窗口
        {
            this->setGeometry( screenWidth - normalRect.width(),  0,  normalRect.width(), normalRect.height() );
        }
        else     //正常情况下居中显示
        {
            this->setGeometry(repaint, 0, normalRect.width(), normalRect.height() );
        }
    }
    else
    {
        this->move(point+Position-QPoint(0,0));
    }

}

//鼠标出去目标区域
void Widget::slotOutBottomRegion()
{
    //qDebug()<<"out";
    inBottomRegion = false;
    QTimer * outRegionTimer = new QTimer;
    outRegionTimer->setSingleShot(true);
    connect(outRegionTimer, SIGNAL(timeout()), this, SLOT(slotOutBottomRegionTimer()));
    outRegionTimer->start(1000);
}

void Widget::slotOutRightRegion()
{
    //qDebug()<<"out";
    inRightRegion = false;
    QTimer * outRightRegionTimer = new QTimer;
    outRightRegionTimer->setSingleShot(true);
    connect(outRightRegionTimer, SIGNAL(timeout()), this, SLOT(slotOutRightRegionTimer()));
    outRightRegionTimer->start(1000);
}

//设置是否隐藏bottomWidget
void Widget::slotOutBottomRegionTimer()
{
    if(!inBottomRegion)
    {
        bottomWidget->hide();
    }
}

//设置是否隐藏hideButton
void Widget::slotOutRightRegionTimer()
{
    if(!inRightRegion)
    {
        hideButton->hide();
    }
}

//响应最大化按钮
void Widget::slotSetButton()
{
    if(clickCount == 1)//窗口最大化
    {
        normalRect = this->rect();
        this->showMaximized();
        ++clickCount;
        menuButton->setGeometry(10,10,70,23);
        closeButton->setGeometry(screenWidth-34, 10, 28, 20);     //将关闭按钮放在最右上角
        maximumButton->setGeometry(screenWidth-68,10, 28, 20);
        minimumButton->setGeometry(screenWidth-102, 10, 28, 20);   //按钮之间间隔6px
        if(listWidget->isVisible())  //列表显示
        {
           // videoWidget0->setGeometry(0,  50, screenWidth-201,   screenHeight-49);
            groupBox->setGeometry(0,  50, screenWidth-200,   screenHeight-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            //listWidget->setGeometry(screenWidth-201, 50, 200, screenHeight-120);
            listWidget->setGeometry(screenWidth-201, 50, 200, screenHeight-49);
            hideButton->setGeometry(screenWidth-220,(screenHeight-49)/2+15, 20,70);
            bottomWidget->setGeometry(0, screenHeight-80, screenWidth-201, 80);
            slider->setGeometry(10, 7, screenWidth-225, 13);
            volumeButton->setGeometry(bottomWidget->width()-80,35, 30,30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }
        else//列表隐藏
        {
            groupBox->setGeometry(0, 50, screenWidth-1,   screenHeight-49);
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            //groupBox->setGeometry(0,  50, screenWidth,   screenHeight-49);
            //listWidget->setGeometry(screenWidth-201, 50, 200, screenHeight-120);
            //listWidget->setGeometry(screenWidth-201, 50, 200, screenHeight-49);
            hideButton->setGeometry(screenWidth-20,(screenHeight-49)/2+15, 20,70);
            bottomWidget->setGeometry(0, screenHeight-80, screenWidth-201, 80);
            slider->setGeometry(10, 7, screenWidth-225, 13);
            volumeButton->setGeometry(bottomWidget->width()-80, 35, 30, 30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }

   }
   else//窗口正常显示
   {
       //  qDebug()<<"showMaximized  before changed: "<<this->rect();
         this->showNormal();
         clickCount = 1;
         int a=normalRect.topRight().x();
         menuButton->setGeometry(10,10,70,23);
         closeButton->setGeometry(a-34, 10, 28, 20);     //将关闭按钮放在最右上角
         maximumButton->setGeometry(a-68,10, 28, 20);
         minimumButton->setGeometry(a-102, 10, 28, 20);   //按钮之间间隔6px
        if(listWidget->isVisible())//列表显示
        {
            //videoWidget0->setGeometry(0,  50,  normalRect.topRight().x()-200,   normalRect.bottomRight().y()-49);    //设置主窗口
            groupBox->setGeometry(0,  50,  normalRect.topRight().x()-200,   normalRect.bottomRight().y()-49);    //设置主窗口
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            listWidget->setGeometry(normalRect.width()-201, 50, 200, normalRect.height()-49);
            hideButton->setGeometry(normalRect.width()-220,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, normalRect.height()-80, normalRect.width()-201, 80);
            slider->setGeometry(10, 7, normalRect.width()-225, 13);
            volumeButton->setGeometry(bottomWidget->width()-80, 35, 30, 30);
            playModeButton->setGeometry(bottomWidget->width()-45, 35, 30, 30);
        }
        else//列表隐藏
        {
            //videoWidget0->setGeometry(0,  50,  normalRect.topRight().x(),   normalRect.bottomRight().y()-49);    //设置主窗口
            groupBox->setGeometry(0,  50,  normalRect.topRight().x()-1,   normalRect.bottomRight().y()-49);    //设置主窗口
            videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
            hideButton->setGeometry(normalRect.width()-20,(listWidget->height())/2+15, 20,70);
            bottomWidget->setGeometry(0, normalRect.height()-80, normalRect.width()-201, 80);
            slider->setGeometry(10, 7, normalRect.width()-25, 13);
            volumeButton->setGeometry(bottomWidget->width()-80, 35, 30, 30);
            playModeButton->setGeometry(bottomWidget->width()-45,35, 30,30);
        }


    }


}

//
void Widget::slotListWidgetActionOpen()
{
    slotOpenFile();
}

//双击列表项更换视频
void Widget::slotListWidgetItemDoubleClick(QString name)
{
    qDebug()<<"name:  "<<name;
    int i;
    QString temp = name.append("(0)");
    for(i=0;i<vector.size();i++)
    {
        qDebug()<<"vector:  "<<vector.at(i).second;
        if(vector.at(i).second == name)
        {
            //qDebug()<<"vector.at(i).second:  "<<vector.at(i).second;
            //qDebug()<<"if(vector.at(i).second == name)";
            listWidget->setCurrentRow(i);
            listWidget->setIndex(i);  //为了使鼠标点击一下listWidget后，仍然不改变当前item
            titleLabel->setText(removeIndexFromAppend(vector.at(i).second));
            playingIndex = i;
            qDebug()<<"vector.at(i).first.second:  "<<vector.at(i).first.second;
            mediaPlayer0 ->setMedia(QUrl::fromLocalFile(vector.at(i).first.second));
            mediaPlayer0->play();
            break;
        }

        if(vector.at(i).second ==temp )   //该文件已经存在
        {
            listWidget->setCurrentRow(i);
            listWidget->setIndex(i);  //为了使鼠标点击一下listWidget后，仍然不改变当前item
            titleLabel->setText(removeIndexFromAppend(vector.at(i).second));
            playingIndex = i;
            qDebug()<<"vector.at(i).first.second:  "<<vector.at(i).first.second;
            mediaPlayer0 ->setMedia(QUrl::fromLocalFile(vector.at(i).first.second));
            mediaPlayer0->play();
            break;
        }
    }
    //qDebug()<<"slotListWidgetItemDoubleClick finished";
}

//删除列表项
void Widget::slotListWidgetItemDeleted(int n)
{
    vector.removeAt(n);
    updateToDataBase();

    listWidget->takeItem(n);

    qDebug()<<vector.isEmpty();
    if(vector.isEmpty())
    {
        titleLabel->clear();
        playButton->setEnabled(false);
        playingIndex=0;
        mediaPlayer0->stop();
    }
    else
    {

        if(mediaPlayer0->state()!=QMediaPlayer::StoppedState)
        {
            if(n < playingIndex)  //删除正在播放视频之前的
            {
                qDebug()<<"删除正在播放视频之前的";
                --playingIndex;
                listWidget->setCurrentRow(playingIndex);
                listWidget->setIndex(playingIndex);

            }
            else if(n == playingIndex)    //删除当前视频
            {
                qDebug()<<"删除当前视频";
                if(++playingIndex >= vector.size())
                    playingIndex=0;

                mediaPlayer0 ->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
                mediaPlayer0->play();
                listWidget->setCurrentRow(playingIndex);
                listWidget->setIndex(playingIndex);
            }

            QString name = vector.at(playingIndex).second;
            name=removeIndexFromAppend(name);
            titleLabel->setText(name);
        }
    }

}

//清空列表
void Widget::slotListWidgetClearAll()
{

    mediaPlayer0->stop();
    qDebug()<<"mediaPlayer0->stop() ";
    playingIndex = 0;
    listWidget->clear();
    QSqlTableModel mediaTableModel;
    mediaTableModel.setTable("mediatable");
    mediaTableModel.select();

    for(int i=0;i<vector.size()+1;i++)
    {
        mediaTableModel.removeRow(i);
    }
    mediaTableModel.submitAll();
    vector.clear();
    titleLabel->clear();
    qDebug()<<vector.isEmpty();
}

//清空失效记录
void Widget::slotListWidgetClearValidItem()
{
    int size = vector.size();
    for(int i=0;i<size; ++i)
    {
        QFileInfo fileInfo(vector.at(i).first.second);
        if(fileInfo.exists())
            continue;
        else
        {
            listWidget->takeItem(i);
            vector.removeAt(i);
        }
    }
    if(mediaPlayer0->state() != QMediaPlayer::StoppedState)//if视频出于播放中或暂停中
    {
        if(vector.isEmpty())
        {
            titleLabel->clear();
            playButton->setEnabled(false);
            playingIndex=0;
            mediaPlayer0->stop();
        }
        else
        {
            QString fileName = mediaPlayer0->currentMedia().canonicalUrl().toString();
            for(int i=0;i<vector.size();++i)
            {
                if(fileName == vector.at(i).first.second)
                {
                    playingIndex = i;
                    break;
                }
            }
            listWidget->setCurrentRow(playingIndex);
            listWidget->setIndex(playingIndex);
        }

    }
    if(size != vector.size()) //不相等说明vector发生了变化
        updateToDataBase();
}

void Widget::slotListWidgetOpenDirectory(int n)
{
    QFileInfo info (vector.at(n).first.second);
    qDebug()<<"info.absolutePath():  "<<info.absolutePath();
    qDebug()<<"info.absoluteDir():  "<<info.absoluteDir();
    QDesktopServices::openUrl(QUrl(info.absolutePath(), QUrl::TolerantMode));

}

//响应playModeListWidget
void Widget::slotPlayModeListWidget()
{
    playModeListWidget->hide();
    int row  = playModeListWidget->currentIndex().row();
    QSqlTableModel settingModel;
    settingModel.setTable("setting");
    settingModel.select();
    settingModel.setData(settingModel.index(0,1),row);
    settingModel.submitAll();

    switch(row)
    {
        case 0:
        {
            //playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            playingMode = CurrentItemOnce;
            playModeButton->setStyleSheet("QPushButton{border-radius:15px; image:url(itemOnce.png)}"
                                          "QPushButton:hover{background-color:rgb(90,90,90); }");
            break;
        }
        case 1:
        {
            //playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            playingMode = CurrentItemInLoop;
            playModeButton->setStyleSheet("QPushButton{border-radius:15px; image:url(itemLoop.png)}"
                                          "QPushButton:hover{background-color:rgb(90,90,90); }");
            break;
        }
        case 2:
        {
            playingMode = Sequential;
            playModeButton->setStyleSheet("QPushButton{border-radius:15px; image:url(sequential.png)}"
                                          "QPushButton:hover{background-color:rgb(90,90,90); }");
            break;
        }

        case 3:
        {
            //playList->setPlaybackMode(QMediaPlaylist::Loop);
            playingMode = Loop;
            playModeButton->setStyleSheet("QPushButton{border-radius:15px; image:url(listLoop.png)}"
                                          "QPushButton:hover{background-color:rgb(90,90,90); }");
            break;
        }
        case 4:
        {
            //playList->setPlaybackMode(QMediaPlaylist::Random);
            playingMode = Random;
            playModeButton->setStyleSheet("QPushButton{border-radius:15px; image:url(random.png)}"
                                          "QPushButton:hover{background-color:rgb(90,90,90); }");
            break;
        }
        default:
        {
            qDebug()<<"Error in slotPlayModeListWidget ! !";
            break;
        }
    }
}

//打开文件
void Widget::slotOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "open file", QDir::currentPath());
    addFile(fileName);
 }

//通过滑动条改变当前进度
void Widget::slotSetValue(int value)
{
    mediaPlayer0->setPosition(value);
}

//根据当前状态设置播放按钮的图标
void Widget::slotStateChanged(QMediaPlayer::State state)
{
    //qDebug()<<"state:  "<<state;
    switch(state)
    {
        case QMediaPlayer::PlayingState:
        {
            //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            playButton->setStyleSheet("QPushButton{image:url(pause.png);border-radius:25px; background-color: rgb(40,40,40)}"
                                                        "QPushButton::hover{background-color: rgb(90,90,90);image:url(pauseHovered.png)}");
            break;
        }
        default:
        {
            //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            playButton->setStyleSheet("QPushButton{image:url(play.png);border-radius:25px; background-color: rgb(40,40,40)}"
                                                        "QPushButton::hover{background-color: rgb(90,90,90); image:url(playHovered.png)}");
            break;
        }
    }
}

//响应播放暂停按钮
void Widget::slotPlayOrPause()
{
    qDebug()<<"slotPlayOrPause";
    switch(mediaPlayer0->state())
    {
        case QMediaPlayer::PlayingState:
        {
            mediaPlayer0->pause();
            break;
        }
    case QMediaPlayer::PausedState:
        {
            mediaPlayer0->play();
            break;
        }
    }

}

//下一曲
void Widget::slotNextVideo()
{
    if(!vector.isEmpty())
    {
       // int currentIndex=playList->currentIndex();
        if(++playingIndex == vector.size())
            playingIndex=0;
        //playList->setCurrentIndex(currentIndex);

        listWidget->setIndex(playingIndex);
        mediaPlayer0 ->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
        mediaPlayer0->play();
        listWidget->setCurrentRow(playingIndex);
    }
}

//上一曲
void Widget::slotLastVideo()
{
    if(!vector.isEmpty())
    {
        //int currentIndex=playList->currentIndex();
        if(--playingIndex <= -1)
            playingIndex=vector.size()-1;
        //playList->setCurrentIndex(currentIndex);
        listWidget->setIndex(playingIndex);
        mediaPlayer0 ->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
        mediaPlayer0->play();
        listWidget->setCurrentRow(playingIndex);
    }
}

//停止视频
void Widget::slotStopVideo()
{
    if( (!vector.isEmpty() )&& (mediaPlayer0->state()!=QMediaPlayer::StoppedState))
    {
        mediaPlayer0->stop();
    }

}

//设置主进度条的值
void Widget::slotSignalPressPosition(qint64 position)
{
    mediaPlayer0->setPosition(position);
    slider->setValue(position);
    //qDebug()<<"slotSignalPressPosition:  "<<position;

}

//设置声音进度条的值
void Widget::slotPressVolumePosition(qint64 position)
{
    mediaPlayer0->setVolume(position);
    volumeSlider->setValue(position);
    QSqlTableModel settingModel;
    settingModel.setTable("setting");
    settingModel.select();
    settingModel.setData(settingModel.index(0,0),position);
    settingModel.submitAll();

}

//
void Widget::slotVideoWidgetDropedList(QList<QUrl> urls)
{
    QString fileName;
    for(int i=0;i<urls.size();++i)
    {
        fileName = urls.at(i).toLocalFile();
        qDebug()<<fileName;
        addFile(fileName);
    }

}

//再videoWidget0上按下鼠标左键
void Widget::slotVideoWidgetMouseLeftDown(bool b)
{
        //isVideoMouseLeftDown = b;
        Position=this->pos();
}

//全屏
void Widget::slotVideoWidgetDoubleClicked()
{
    videoWidget0->setFullScreen(!videoWidget0->isFullScreen());
    if(!videoWidget0->isFullScreen())
    {
        videoWidget0->setGeometry(2,0,groupBox->size().width(), groupBox->size().height());
    }
}

void Widget::slotVideoWidgetActionInfo()
{
    QSize size = mediaPlayer0->currentMedia().canonicalResource().resolution();
    qDebug()<<mediaPlayer0->currentMedia().canonicalResource().url();
    qDebug()<<size;
}

//设置右上角的三个按钮
void Widget::setThreeButton()
{
    //设置三个按钮
    closeButton=new QPushButton(this);
    minimumButton = new QPushButton(this);
    maximumButton = new QPushButton(this);
    closeButton->setFixedSize(30,20);
    minimumButton->setFixedSize(30,20);
    maximumButton->setFixedSize(30,20);

   // int a = this->rect().topRight().x();
    int a = normalRect.width();
    closeButton->setGeometry(a-34, 10, 28, 20);     //将关闭按钮放在最右上角
    maximumButton->setGeometry(a-68,10, 28, 20);
    minimumButton->setGeometry(a-102, 10, 28, 20);   //按钮之间间隔6px
    QString name = QDir::currentPath();
   // qDebug()<<"name:    "<<name;
  //  QPixmap closeIcon((name+"/close.png"));
 //   closeButton->setIcon(closeIcon);
  //  QPixmap minimumIcon((name + "/minimize.png"));
 //   minimumButton->setIcon(minimumIcon);
 //   QPixmap maximumIcon((name + "/maximize.png"));
//    maximumButton->setIcon(maximumIcon);
    closeButton->setStyleSheet("QPushButton{image:url(close.png); border-radius:8px; background-color:rgb(60,65,68);}"
                                                  "QPushButton:hover{background-color:rgb(150,150,150);}");
    minimumButton->setStyleSheet("QPushButton{image:url(minimize.png); border-radius:8px; background-color:rgb(60,65,68);}"
                                                         "QPushButton:hover{image:url(minimizeHovered.png); background-color:rgb(120,120,120);}");
    maximumButton->setStyleSheet("QPushButton{image:url(maximize.png); border-radius:8px; background-color:rgb(60,65,68);}"
                                                        "QPushButton:hover{image:url(maximizeHovered.png); background-color:rgb(120,120,120);}");
    closeButton->setToolTip("关闭");
    minimumButton->setToolTip("最小化");
    maximumButton->setToolTip("最大化/还原");
    //connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(slotCloseWidget()));
    connect(minimumButton, SIGNAL(clicked()), this, SLOT(showMinimized()) );
    connect(maximumButton, SIGNAL(clicked()), this, SLOT(slotSetButton()));
}

//响应volumeButton的计时器
void Widget::slotVolumeTimer()
{
   if(volumeWidgetEntered == false)
   {
       volumeWidget->hide();
   }
}


//响应PlayModeButton的计时器
void Widget::slotPlayModeTimer()
{
    if(playModeWidgetEntered == false)
    {
        playModeListWidget->hide();
    }
}

//播放视频时mediaPlayer的响应函数
void Widget::slotPositionChanged(qint64 value)
{
    if(value == slider->maximum())
    {
        presentTimeLabel->setText("00:00"); // 此项设置有延迟，故提前设置会好看点
        //qDebug()<<"value == slider->maximum()";
        switch(playModeListWidget->currentRow())
        {
        case 0:      //CurrentItemOnce:
        {
            break;
        }
        case 1:       //CurrentItemInLoop:
        {
            mediaPlayer0->setPosition(0);
            mediaPlayer0->play();
            break;
        }
        case 2:     //sequence:
        {
            if(++playingIndex != vector.size())
            {
                listWidget->setIndex(playingIndex);
                listWidget->setCurrentRow(playingIndex);
                mediaPlayer0->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
                mediaPlayer0->play();
                mediaPlayer0->setPosition(0);
                break;
            }
            else
            {
                playingIndex=0;
                //slider->setValue(0);
                break;
            }
        }
        case 3:      //Loop:
        {

            if(++playingIndex == vector.size())
            {
                playingIndex=0;
            }
            listWidget->setIndex(playingIndex);
            listWidget->setCurrentRow(playingIndex);
            mediaPlayer0->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
            mediaPlayer0->play();
            break;

        }
        case 4:    //Random:
        {
            QTime time;
            time= QTime::currentTime();
            qsrand(time.msec()+time.second()*1000);

            int x=qrand()%(vector.size())-1 ;
            playingIndex = x;
            listWidget->setIndex(playingIndex);
            listWidget->setCurrentRow(playingIndex);
            mediaPlayer0->setMedia(QUrl::fromLocalFile(vector.at(playingIndex).first.second));
            mediaPlayer0->play();
            break;
        }
        default:
            qDebug()<<"error in slotPositionChanged";
        }
    }
    slider->setValue(value);
    QString presentTime(digitalToTime((value)/1000));
    presentTimeLabel->setText(presentTime);
    //titleLabel->setText(removeIndexFromAppend(vector.at(playingIndex).second));


}

//设置当前视频播放的总时间
void Widget::slotDurationChanged(qint64 value)
{
    //qDebug()<<"duration changed";
    slider->setRange(0, value);
    QString totalTime("/ ");
    totalTime.append(digitalToTime(value/1000));
    totalTimeLabel->setText(totalTime);
    presentTimeLabel->setText("00:00");

}

//使用vector更新database
void Widget::updateToDataBase()
{
    //qDebug()<<"updatetoBase()";
    QSqlTableModel mediaTableModel;
    mediaTableModel.setTable("mediatable");
    mediaTableModel.select();

    for(int i=0;i<vector.size()+1;i++)
    {
        mediaTableModel.removeRow(i);
    }
    //mediaTableModel.submitAll();

    QSqlRecord record = mediaTableModel.record();

    for(int i=0;i<vector.size();i++)
    {
        record.setValue(0,QString::number(i));
        record.setValue(1,vector.at(i).first.first);
        record.setValue(2, vector.at(i).first.second);
        record.setValue(3, vector.at(i).second);
        mediaTableModel.insertRecord(i,record);
    }

    mediaTableModel.submitAll();
    //qDebug()<<"update fished";
}
