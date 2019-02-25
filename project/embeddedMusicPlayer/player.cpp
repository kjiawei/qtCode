/*******************************************
*player.cpp
*2013.7.31-2013.8.04
*主窗口
*QP1301_
********************************************
*/

#include "player.h"

player::player()
{
    this->setWindowTitle(tr("音乐播放器"));
    this->setWindowIcon(QIcon(":/images/ico.ico"));
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    this->setMaximumSize(240, 120);
    this->setMinimumSize(240, 120);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/images/000.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(palette);

    lrc = new Mylrc(this);
    show_lrc = 0;
    current_list = 0;
    copy_list = 0;

    playlist_0 = new QMediaPlaylist;
    playlist_1 = new QMediaPlaylist;
    playlist = new QMediaPlaylist;
    addlist = new QMediaPlaylist;

    music_read();
    if(playlist_0->mediaCount())
    {
        CopyPlaylist(playlist, playlist_0);
        copy_list = 0;
    }
    else if(playlist_1->mediaCount())
    {
        CopyPlaylist(playlist, playlist_1);
        copy_list = 1;
    }

    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setPlaylist(playlist);

    videoWidget = new QVideoWidget;
    videoWidget->setHidden(true);
    mediaPlayer->setVideoOutput(videoWidget);

    QSpacerItem *hspacer1 = new QSpacerItem(60,20);
    QSpacerItem *hspacer2 = new QSpacerItem(25,20);
    QSpacerItem *hspacer3 = new QSpacerItem(0,15);

    topLabel = new QLabel;
    topLabel->setAlignment(Qt::AlignHCenter);

    positionSlider = new QSlider(Qt::Horizontal);
    positionSlider->setRange(0, mediaPlayer->duration());
    positionSlider->setMinimumWidth(130);
    connect(positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));

    timeLabel = new QLabel(tr("00:00/00:00"));
    timeLabel->setAlignment(Qt::AlignRight);
    timeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout *layout_h1 = new QHBoxLayout;
    layout_h1->addWidget(positionSlider);
    layout_h1->addWidget(timeLabel);

    stopButton = new QPushButton;
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setFlat(true);
    stopButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(stopButton, SIGNAL(clicked()), mediaPlayer, SLOT(stop()));

    backButton = new QPushButton;
    backButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    backButton->setFlat(true);
    backButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(backButton, SIGNAL(clicked()), playlist, SLOT(previous()));

    playButton = new QPushButton;
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setFlat(true);
    playButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));

    nextButton = new QPushButton;
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    nextButton->setFlat(true);
    nextButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(nextButton, SIGNAL(clicked()), playlist, SLOT(next()));

    playerMuted = true;
    muteButton = new QPushButton;
    muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    muteButton->setFlat(true);
    muteButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(100);
    volumeSlider->setMinimumWidth(40);
    connect(volumeSlider, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));

    QHBoxLayout *layout_h2 = new QHBoxLayout;
    layout_h2->addWidget(stopButton);
    layout_h2->addWidget(backButton);
    layout_h2->addWidget(playButton);
    layout_h2->addWidget(nextButton);
    layout_h2->addItem(hspacer2);
    layout_h2->addWidget(muteButton);
    layout_h2->addWidget(volumeSlider);

    list = new MusicList(this);
    list->setPlayList_0(playlist_0);
    list->setPlayList_1(playlist_1);
    list->list_widget->setCurrentRow(0);
    connect(list->list_widget, SIGNAL(currentRowChanged(int)), this, SLOT(setCurrentList(int)));
    connect(list->list_0, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));
    connect(list->list_1, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));
    connect(list, SIGNAL(playlistClean()), this, SLOT(clearPlayList()));
    connect(list, SIGNAL(addMedia()), this, SLOT(open()));
    connect(list, SIGNAL(List_0_IndexChange(int)), this, SLOT(setList_0_index(int)));
    connect(list, SIGNAL(list_1_IndexChange(int)), this, SLOT(setList_1_index(int)));
    connect(list, SIGNAL(remove_sign()), this, SLOT(remove_index()));

    messLabel = new QLabel(tr("清淋之作--QT"));
    messLabel->setAlignment(Qt::AlignLeft);
    messLabel->setMinimumWidth(50);

    openButton = new QPushButton(tr("Open"));
    openButton->setFlat(true);
    openButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    listButton = new QPushButton(tr("list"));
    listButton->setFlat(true);
    listButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(listButton, SIGNAL(clicked()), list, SLOT(show_hide()));

    lrcButton = new QPushButton(tr("LRC"));
    lrcButton->setFlat(true);
    lrcButton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px}");
    connect(lrcButton, SIGNAL(clicked()), this, SLOT(showlrc(void)));

    QHBoxLayout *layout_h3 = new QHBoxLayout;
    layout_h3->addWidget(messLabel);
    layout_h3->addItem(hspacer1);
    layout_h3->addWidget(openButton);
    layout_h3->addWidget(listButton);
    layout_h3->addWidget(lrcButton);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(topLabel);
    main_layout->addLayout(layout_h1);
    main_layout->addItem(hspacer3);
    main_layout->addLayout(layout_h2);
    main_layout->addItem(hspacer3);
    main_layout->addLayout(layout_h3);
    main_layout->addWidget(videoWidget);

    this->setLayout(main_layout);


    connect(mediaPlayer, SIGNAL(metaDataChanged()), this, SLOT(title()));
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(updateDurationInfo(qint64)));
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(playlistPositionChanged(int)));


    QIcon icon = QIcon(":/images/ico.ico");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("a trayicon example");
    createActions();
    createTrayIcon();
    trayIcon->show();
    //    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    //    music_read();
    //    CopyPlaylist(playlist, playlist_0);
}


/*******************************************
*功能：添加歌曲
*函数名：void open()
*参数类型：无
*返回值:void
*******************************************
*/
void player::open()
{
    int exists = 0;

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), "D:/", "MP3 file (*.mp3)");
    foreach (QString const &argument, fileNames)
    {
        QFileInfo fileInfo(argument);
        if (fileInfo.exists())
        {
            QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            if (fileInfo.suffix().toLower() == QLatin1String("m3u"))
            {
                addlist->load(url);
            } else
            {
                addlist->addMedia(url);
            }
            exists = 1;
        } else
        {
            QUrl url(argument);
            if (url.isValid())
            {
                addlist->addMedia(url);
            }
        }

    }
    if(exists == 1)
    {
        if(current_list == 0)
        {
            if(copy_list == 0)
            {
                CopyPlaylist(playlist_0, addlist);
                CopyPlaylist(playlist, addlist);
            }
            else if(copy_list == 1)
            {
                CopyPlaylist(playlist_0, addlist);
            }
            addlist->clear();
        }
        else if(current_list == 1)
        {
            if(copy_list == 1)
            {
                CopyPlaylist(playlist_1, addlist);
                CopyPlaylist(playlist, addlist);
            }
            else if(copy_list == 0)
            {
                if(playlist->mediaCount() == 0)
                {
                    CopyPlaylist(playlist, addlist);
                    copy_list = 1;
                }
                CopyPlaylist(playlist_1, addlist);
            }
            addlist->clear();
        }
    }

}


/*******************************************
*功能：播放器--播放/暂停
*函数名：void play()
*参数类型：无
*返回值：void
********************************************
*/
void player::play()
{
    switch (mediaPlayer->state())
    {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

/*******************************************
*功能：播放与暂停功能的相互转换
*函数名：void mediaStateChanged(QMediaPlayer::State state)
*参数类型：QMediaPlayer::State state
*返回值：void
********************************************
*/
void player::mediaStateChanged(QMediaPlayer::State state)
{
    switch (state)
    {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playAction->setIcon(*iconpause);
        playAction->setText(tr("暂停"));
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playAction->setIcon(*iconplay);
        playAction->setText(tr("播放"));
        break;
    }
}

/********************************************
*功能：播放歌曲时 实现在播放器上方显示歌曲信息
*函数名：void title()
*参数类型：无
*返回值：void
*********************************************
*/
void player::title()
{
    QString titl = mediaPlayer->currentMedia().canonicalUrl().toString();
    topLabel->setText(titl.section('/', -1));

}


/********************************************
*功能：获取歌曲总时间
*函数名：void durationChanged(qint64 duration)
*参数类型：qint64
*返回值：void
*********************************************
*/
void player::durationChanged(qint64 duration)
{
    positionSlider->setRange(0, duration);
    this->duration = duration;
    resolvelrc();//
}


/********************************************
*功能：设置进度条位置
*函数名：
*参数类型：qint64
*返回值：void
********************************************
*/
void player::positionChanged(qint64 position)
{
    positionSlider->setValue(position);
}


/********************************************
*功能：播放歌曲时时间的动态显示与歌词的显示
*函数名：void updateDurationInfo(qint64 currentInfo)
*参数类型：qint64
*返回值：void
********************************************
*/
void player::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || duration)
    {
        QTime currentTime(0, (currentInfo/60000)%60, (currentInfo/1000)%60);
        QTime totalTime(0, (duration/60000)%60, (duration/1000)%60);
        tStr = currentTime.toString("mm:ss") + "/" + totalTime.toString("mm:ss");
    }
    timeLabel->setText(tStr);



    if(!lrcmap.isEmpty())//
    {
        qint64 previous = 0;
        qint64 later = 0;

        foreach(qint64 value,lrcmap.keys())//把歌词对应的时间标签赋值给变量value
        {
            if (currentInfo >= value)
            {
                previous = value;
                // qDebug("灯前currentinfo_value = %d",currentInfo);
                //qDebug("歌词对应value = %d",value);

            }
            else
            {
                later = value;
                // qDebug("later_value = %d",later);
                break;
            }
        }

        if (later == 0)
        {
            later = duration;
            //qDebug("总时间later_duration = %d",later);
        }
        QString currentlrc = lrcmap.value(previous);
        //qDebug("当前时间previous = %d",previous);
        //获取当前时间对应的歌词内容
        //lrc.setText(currentlrc);
        if (currentlrc.length() < 2)
        {
            lrc->setText("清淋之作---Linux!");
        }
        if(currentlrc != lrc->text())
        {

            lrc->setText(currentlrc);
            qint64 intervaltime = later - previous;
            Masktime = intervaltime;
            lrc->startLrcMask(intervaltime);
        }
    }
    else
    {
        lrc->setText("清淋之作---Linux");
    }
}


/*********************************************
*功能：播放进度
*函数名：void setPosition(int position)
*参数类型：int
*返回值：void
**********************************************
*/
void player::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

/*********************************************
*功能：复制歌曲列表
*函数名：void CopyPlaylist(QMediaPlaylist *dest, QMediaPlaylist *src)
*参数类型：QMediaPlaylist *dest, QMediaPlaylist *src
*返回值：void
**********************************************
*/
void player::CopyPlaylist(QMediaPlaylist *dest, QMediaPlaylist *src)
{
    int i = 0;
    int num = src->mediaCount();
    for(i = 0; i < num; i++)
    {
        dest->addMedia(src->media(i).canonicalUrl());
    }
}



/*********************************************
*功能：开启声音与静音
*函数名：void muteClicked()
*参数类型：无
*返回值：void
**********************************************
*/
void player::muteClicked()
{
    if(playerMuted == true)
    {
        muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        playerMuted = false;
        volume = mediaPlayer->volume();
        mediaPlayer->setVolume(0);
        volumeSlider->setEnabled(false);
    }
    else if(playerMuted == false)
    {
        muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        playerMuted = true;
        mediaPlayer->setVolume(volume);
        volumeSlider->setEnabled(true);
    }
}


/*********************************************
*功能：上一曲/下一曲时列表中图标跟着动态移动
*函数名：void playlistPositionChanged(int currentItem)
*参数类型：int
*返回值：void
**********************************************
*/
void player::playlistPositionChanged(int currentItem)
{
    if(copy_list == 0)
    {
        list->list_0->setCurrentIndex(list->listModel_0->index(currentItem, 0));
    }
    else if(copy_list == 1)
    {
        list->list_1->setCurrentIndex(list->listModel_1->index(currentItem, 0));
    }
    lrc->stopLrcMask();//
    resolvelrc();//
}


/*********************************************
*功能：获取当前操作歌曲列表
*函数名：void setCurrentList(int currentList)
*参数类型：int
*返回值：void
*********************************************
*/
void player::setCurrentList(int currentList)
{
    current_list = currentList;
}



/*********************************************
*功能：对 双击歌曲列表信号  处理
*函数名：void jump(const QModelIndex &index)
*参数类型：const QModelIndex &index
*返回值：void
**********************************************
*/
void player::jump(const QModelIndex &index)
{
    if (index.isValid())
    {
        if(current_list == 0)
        {
            if(copy_list == 1)
            {
                playlist->clear();
                CopyPlaylist(playlist, playlist_0);
                copy_list = 0;
            }
        }
        else if(current_list == 1)
        {
            if(copy_list == 0)
            {
                playlist->clear();
                CopyPlaylist(playlist, playlist_1);
                copy_list = 1;
            }
        }
        playlist->setCurrentIndex(index.row());
        mediaPlayer->play();
        resolvelrc();//
    }
}


/*********************************************
*功能：清楚整个歌曲列表---------
*函数名：void clearPlayList()
*参数类型：无
*返回值：void
************************************************
*/
void player::clearPlayList()
{
    if(current_list == 0)
    {
        if(copy_list == 0)
        {
            playlist_0->clear();
            playlist->clear();
            CopyPlaylist(playlist, playlist_1);
            copy_list = 1;
        }
        else if(copy_list == 1)
        {
            playlist_0->clear();
        }
    }
    else if(current_list == 1)
    {
        if(copy_list == 1)
        {
            playlist_1->clear();
            playlist->clear();
            CopyPlaylist(playlist, playlist_0);
            copy_list = 0;
        }
        else if(copy_list == 0)
        {
            playlist_1->clear();
        }
    }
}


/*********************************************
*功能：获取鼠标点击位置---------
*函数名：void remove_index()
*参数类型：无
*返回值：void
************************************************
*/
void player::setList_0_index(int index)
{
    list_0_index_music = index;
    //messLabel->setText(QString::number(list_0_index_music, 10));
}
void player::setList_1_index(int index)
{
    list_1_index_music = index;
}


/*********************************************
*功能：删除歌曲列表中的歌曲---------
*函数名：void remove_index()
*参数类型：无
*返回值：void
************************************************
*/
void player::remove_index()
{
    if(current_list == 0)
    {
        if(copy_list == 0)
        {
            playlist->removeMedia(list_0_index_music);
        }
        playlist_0->removeMedia(list_0_index_music);
    }
    else if(current_list == 1)
    {
        if(copy_list == 1)
        {
            playlist->removeMedia(list_1_index_music);
        }
        playlist_1->removeMedia(list_1_index_music);
    }
}

/*************************************************
*功能：显示歌词显示部件
*函数名：void showlrc(void)
*参数类型：void
*返回值：void
**************************************************
*/
void player::showlrc(void)//
{
    if(show_lrc == 0)
    {
        lrc->show();
        show_lrc = 1;
    }
    else if(show_lrc == 1)
    {
        lrc->hide();
        show_lrc = 0;
    }
}
/************************************************/



/*********************************************
*功能：创建托盘菜单各选项---------
*函数名：void createTrayIcon()
*参数类型：无
*返回值：void
***********************************************
*/
void player::createActions()
{

    iconpause = new QIcon(":/images/pause.png");
    iconplay = new QIcon(":/images/play.png");

    showAction = new QAction(QIcon(":/images/list.png"), tr("显示"), this);
    connect(showAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    backAction = new QAction(QIcon(":/images/previous.png"), tr("上一曲"),this);
    connect(backAction, SIGNAL(triggered()), playlist, SLOT(previous()));

    nextAction = new QAction(QIcon(":/images/next.png"), tr("下一曲"),this);
    connect(nextAction, SIGNAL(triggered()), playlist, SLOT(next()));

    playAction = new QAction(*iconplay, tr("播放"),this);
    connect(playAction, SIGNAL(triggered()), this, SLOT(play()));

    quitAction = new QAction(QIcon(":/images/lrc.png"), tr("退出"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quite()));
}


/*********************************************
*功能：创建托盘菜单---------
*函数名：void createTrayIcon()
*参数类型：无
*返回值：void
*********************************************
*/
void player::createTrayIcon()

{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(backAction);
    trayIconMenu->addAction(nextAction);
    trayIconMenu->addAction(playAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

//关闭到托盘---------

void player::closeEvent(QCloseEvent *e)
{

    //    music_write();

    e->ignore();

    this->hide();

}

/*************************************************
*功能：文件操作歌词目录保存（打开文件写入歌词路径）
*函数名：void musicin(void)
*参数类型：void
*返回值：void
***********************************************
*/
void player::music_write(void)//
{
    QFile file0("./music0");
    QFile file1("./music1");
    file0.remove();
    file1.remove();
    if (!file0.open(QIODevice::WriteOnly))
    {
        qDebug("music1不存在");
    }
    if (!file1.open(QIODevice::WriteOnly))
    {
        qDebug("music2不存在");
    }
    int count_0 = playlist_0->mediaCount();
    int count_1 = playlist_1->mediaCount();

    int i, j;
    QTextStream out0(&file0);
    QTextStream out1(&file1);

    //out1.setCodec(QTextCodec::codecForName("GB2312"));
    //out2.setCodec(QTextCodec::codecForName("GB2312"));
    for(i = 0; i < count_0; i++)
    {
        QString musicpath0 = playlist_0->media(i).canonicalUrl().toString();
        musicpath0 = musicpath0.remove(musicpath0.left(8));
        out0<< musicpath0<< '\n';
    }
    for(j = 0; j < count_1; j++)
    {
        QString musicpath1 = playlist_1->media(j).canonicalUrl().toString();
        musicpath1 = musicpath1.remove(musicpath1.left(8));
        out1<< musicpath1<< '\n';
    }
    file0.close();
    file1.close();
}

/**********************************************
*功能：文件操作歌词路径保存（打开文件读出文件信息）
*函数名：void showlrc(void)
*参数类型：void
*返回值：void
************************************************
*/
void player::music_read(void)//
{
    QFile file0("./music0");
    QFile file1("./music1");
    if (!file0.open(QIODevice::ReadOnly)) qDebug("music1打开失败");
    if (!file1.open(QIODevice::ReadOnly)) qDebug("music2打开失败");
    QTextStream in0(&file0);
    QTextStream in1(&file1);
    in0.setCodec(QTextCodec::codecForName("GB2312"));
    in1.setCodec(QTextCodec::codecForName("GB2312"));
    while(!in0.atEnd())
    {
        QString path0;
        path0 = in0.readLine();
        QFileInfo fileInfo(path0);
        QUrl url0 = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
        playlist_0->addMedia(url0);
    }

    while(!in1.atEnd())
    {
        QString path1;
        path1 = in1.readLine();
        QFileInfo fileInfo(path1);

        QUrl url1 = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
        playlist_1->addMedia(url1);
    }
    file0.close();
    file1.close();
}

/************************************************
*功能：歌词解析函数
*函数名：void resolvelrc()
*参数类型：无参数
*返回值：void
*************************************************
*/
void player::resolvelrc()//
{
    lrcmap.clear();//清除以前的内容
    sourcename = mediaPlayer->currentMedia().canonicalUrl().toString();
    /*File *fp;
    file.open(fp, QIODevice::WriteOnly);
    file.write(sourcename, qstrlen(sourcename));        // write to stderr
    file.close();
    */
    if(sourcename.isEmpty())
    {
        return;
    }
    //吧歌曲后缀改为歌词.lrc为后缀的歌词文本
    QString lrcfilename = sourcename.remove(sourcename.right(3)) + "lrc";
    QString lrcname = lrcfilename.remove(lrcfilename.left(8));

    //lrc.setText(lrcname);
    //打开歌词文件
    QFile file(lrcname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        lrc->setText(tr("未找到歌词文件！"));
        return;
    }
    //设置字符串编码(可以显示中文)
    QTextStream all(&file);
    all.setCodec(QTextCodec::codecForName("GB2312"));
    QString allText = all.readAll();//获取歌词文本信息

    //lrc.setText(allText);
    file.close();
    //按行吧歌词分解为歌词列表
    QStringList lines = allText.split("\n");
    //使用正则表达式吧时间标签和歌词分隔开
    QRegExp rx("\\[\\d{2}\\:\\d{2}\\.\\d{2}\\]");//
    //QString qq = rx.cap(0)测试代码：查看获取的时间是否正确;
    //topLabel->setText(qq);
    // qDebug("qq = %s",qq);
    foreach(QString oneline,lines)
    {
        QString temp = oneline;
        temp.replace(rx,"");

        int pos = rx.indexIn(oneline,0);
        //讲时间标签转换为以毫秒为单位的整形时间
        while (pos != -1)
        {
            QString cap = rx.cap(0);
            /*char buf[100] = {'\0'};
        strcpy(buf,cap.toLatin1().data());
        qDebug("cap = %s",buf);*/
            QRegExp regexep;
            regexep.setPattern("\\d{2}(?=\\:)");
            regexep.indexIn(cap);
            int minute = regexep.cap(0).toInt();
            // qDebug("minute = %d",minute);

            regexep.setPattern("\\d{2}(?=\\.)");
            regexep.indexIn(cap);

            int second = regexep.cap(0).toInt();
            /*8QString mm = regexep.cap(0);
        char b[100] = {'\0'};
        strcpy(b, mm.toLatin1().data());
        qDebug("second = %s",b);
        */
            regexep.setPattern("\\d{2}(?=\\])");
            regexep.indexIn(cap);
            int millisecond = regexep.cap(0).toInt();
            //qDebug("millisecond = %d",millisecond);
            qint64 totalTime = minute * 60000 + second *1000 + millisecond * 10;
            //qDebug("位保存之前歌词对应时间 totalTime = %d",totalTime);
            //把获取的时间与对应的歌词插入到lrcmap中保存
            lrcmap.insert(totalTime,temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline,pos);
        }
    }

    if(lrcmap.isEmpty())
    {
        lrc->setText(tr("歌词文件错误"));
        return;
    }
}

void player::quite()
{
    music_write();
    qApp->quit();
}
