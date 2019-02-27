#include "textedit.h"
#include "ui_textedit.h"
#include "mdichild.h"
#include "find_replace.h"
#include "ui_find_replace.h"//加此文件才能操作ui

#include <QtGui>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QMessageBox>

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    // Q_FOREACH (QTabBar* tab, ui->mdiArea->findChildren())//QMdiArea tabs with close button
    // {
    //QTabBar* tab;
    //   tab->setTabsClosable(true);
    //   connect(tab, SIGNAL(tabCloseRequested(int)),
    //              this, SLOT(closeTab(int)));
    //}

    findReplace = new Find_Replace(this);//查找替换
    /**查找替换相关的关联**/
    connect(findReplace->ui->cancleButtonF,SIGNAL(clicked()),findReplace,SLOT(close()));
    connect(findReplace->ui->nextButtonF,SIGNAL(clicked()),this,SLOT(findNextF()));//关联查找
    connect(findReplace->ui->cancleButtonR,SIGNAL(clicked()),findReplace,SLOT(close()));
    connect(findReplace->ui->nextButtonR,SIGNAL(clicked()),this,SLOT(findNextR()));
    connect(findReplace->ui->pushButtonReplace,SIGNAL(clicked()),this,SLOT(replace()));
    connect(findReplace->ui->pushButtonReplaceAll,SIGNAL(clicked()),this,SLOT(replaceAll()));

    readSettings();//读取上次关闭窗口时窗口的大小与位置
    //this->setCentralWidget(ui->mdiArea);//将多文档区部件设为中心部件 限定只能显示主要控件

    videoViewInit();//

    ui->mdiArea->setViewMode(QMdiArea::TabbedView);//设为标签栏显示模式
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateMenus()));

    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);//定时器开始计时，其中1000表示1000ms即1秒

    actGrp = new QActionGroup(this);//更改对齐方式
    left = new QAction(QIcon(":/images/textleft.png"),tr("左对齐"),actGrp);
    left->setCheckable(true);
    center = new QAction(QIcon(":/images/textcenter.png"),tr("居中对齐"),actGrp);
    center->setCheckable(true);
    right = new QAction(QIcon(":/images/textright.png"),tr("右对齐"),actGrp);
    right->setCheckable(true);
    justify = new QAction(QIcon(":/images/textjustify.png"),tr("两端对齐"),actGrp);
    justify->setCheckable(true);

    toolBar = new QToolBar(this);//新建工具条
    this->addToolBar(toolBar);
    toolBar->addActions(actGrp->actions());//加入工具条内
    ui->menu_O->addSeparator();
    ui->menu_O->addActions(actGrp->actions());//加入“格式”菜单栏

    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(slotAlignment(QAction*)));//关联对齐方式的修改

    //文本排序
    QLabel *listAlign = new QLabel(tr("排序："));
    listBox = new QComboBox(toolBar);
    //插入可选的排序方式
    listBox->addItem(tr("Standard"));
    listBox->addItem(tr("Bullet List (Disc)"));
    listBox->addItem(tr("Bullet List (Circle)"));
    listBox->addItem(tr("Bullet List (Square)"));
    listBox->addItem(tr("1 2 3 ... (Decimal)"));
    listBox->addItem(tr("a b c ... (Alpha lower)"));
    listBox->addItem(tr("A B C ... (Alpha upper)"));
    listBox->addItem(tr("   ...(Roman lower)"));
    listBox->addItem(tr("Ⅰ Ⅱ Ⅲ ... (Roman upper)"));
    toolBar->addSeparator();
    toolBar->addWidget(listAlign);
    toolBar->addWidget(listBox);

    connect(listBox,SIGNAL(activated(int)),this,SLOT(slotList(int)));//关联排序

    actViewMode = new QActionGroup(this);//视图模式
    tabbedView = new QAction(tr("标签模式(&T)"),actViewMode);
    tabbedView->setCheckable(true);
    tabbedView->setChecked(true);//默认选择为标签模式
    windowView = new QAction(tr("窗口模式(&W)"),actViewMode);
    windowView->setCheckable(true);
    ui->menu_ViewMode->addActions(actViewMode->actions());
    connect(actViewMode,SIGNAL(triggered(QAction*)),this,SLOT(slotViewMode(QAction*)));

    windowMapper = new QSignalMapper(this);//信号翻译转发器
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));
    connect(ui->menu_SelectW,SIGNAL(aboutToShow()),this,SLOT(updateMenu_SelectW()));//更新“选择窗口”菜单

    for(int i = 0; i < MaxRecentFiles; i++)//插入最近打开文件列表
    {
        recentFileActs[i] = new QAction(this);
        ui->menu_RecentFile->addAction(recentFileActs[i]);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }
    updateRecentFiles();//更新最近打开文件列表

    init_statusBar();//初始化状态栏
    updateMenus();//更新菜单栏等
    //this->setGeometry(250,100,820,600);
}

TextEdit::~TextEdit()
{
    delete ui;
}

void TextEdit::videoViewInit()
{
    videoIsPlaying=0;
    video_name="noplaying-";
    cutScreenPath="E:/qt/qtCode/project/TextEdit/";
    ui->videoWidget->setStyleSheet("background-color:black;");
    playerTimer = new QTimer;
    connect(playerTimer,SIGNAL(timeout()),this,SLOT(playerTime()));
}

void TextEdit::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TextEdit::slotViewMode(QAction *a)//视图模式
{
    if(a == tabbedView)
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);//设为标签栏显示模式
    if(a == windowView)
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);//设为窗口显示模式
    //只有在窗口模式下平铺和层叠才起作用
    bool isSubWindowView = (activeMdiChild() && ui->mdiArea->viewMode() == QMdiArea::SubWindowView);
    ui->action_Cascade->setEnabled(isSubWindowView);
    ui->action_Tile->setEnabled(isSubWindowView);
}

void TextEdit::openRecentFile()//打开最近文件列表指定文件
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(action)
    {
        QString canonicalFilePath = QFileInfo(action->data().toString()).canonicalFilePath();
        bool hasOpened = false;//是否已经打开该文件
        foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
            if( mdiChild->currentFile() == canonicalFilePath)
            {
                hasOpened = true;
                ui->mdiArea->setActiveSubWindow(window);
                continue;
            }
        }
        if(!hasOpened)//如果未打开则打开该文件
        {
            MdiChild *child = new MdiChild;
            ui->mdiArea->addSubWindow(child);
            if(child->loadFile(action->data().toString()))
            {
                child->setVisible(true);
                second_statusLabel->setText(tr("打开成功"));
                iniConnect();//初始化关联
            }
        }
    }
}

void TextEdit::updateRecentFiles()//更新最近打开文件列表
{
    QSettings settings("QT","MDI example");
    QStringList files = settings.value("recentFiles").toStringList();

    int numRecentFiles = qMin(files.size(),(int)MaxRecentFiles);
    for(int i= 0;i < numRecentFiles;i++)
    {
        QString text = tr("&%1 %2").arg(i+1).arg(files[i]);
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for(int i = numRecentFiles;i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);

}
void TextEdit::updateMenus()//更新菜单栏和标题的显示状态等
{
    bool hasMdiChild = (activeMdiChild() != 0);
    ui->action_AllSelect->setEnabled(hasMdiChild);
    ui->action_Asave->setEnabled(hasMdiChild);
    ui->action_Clear->setEnabled(hasMdiChild);
    ui->action_Find->setEnabled(hasMdiChild);
    ui->action_Font->setEnabled(hasMdiChild);
    ui->action_FontColor->setEnabled(hasMdiChild);
    ui->action_Paste->setEnabled(hasMdiChild);
    ui->action_Undo->setEnabled(hasMdiChild && activeMdiChild()->document()->isUndoAvailable());
    ui->action_Redo->setEnabled(hasMdiChild && activeMdiChild()->document()->isRedoAvailable());
    ui->action_Save->setEnabled(hasMdiChild);
    ui->action_PDF->setEnabled(hasMdiChild);
    ui->action_Print->setEnabled(hasMdiChild);
    ui->action_PrintPreview->setEnabled(hasMdiChild);
    ui->action_Switch->setEnabled(hasMdiChild);
    ui->action_HighLightShow->setEnabled(hasMdiChild);
    ui->action_AllClose->setEnabled(hasMdiChild);
    ui->action_Close->setEnabled(hasMdiChild);
    ui->action_Replace->setEnabled(hasMdiChild);
    ui->action_zoomIn->setEnabled(hasMdiChild);
    ui->action_zoomOut->setEnabled(hasMdiChild);
    actGrp->setEnabled(hasMdiChild);//对齐方式
    listBox->setEnabled(hasMdiChild);//排序
    ui->menu_SelectW->setEnabled(hasMdiChild);//“选择窗口”菜单
    first_statusLabel->setText(hasMdiChild? first_statusLabel->text():tr("欢迎使用多文档文本编辑器"));
    second_statusLabel->setText(hasMdiChild? second_statusLabel->text():tr("yafeilinux制作"));

    bool hasSelection = (activeMdiChild() &&
                         activeMdiChild()->textCursor().hasSelection());
    ui->action_Copy->setEnabled(hasSelection);
    ui->action_Cut->setEnabled(hasSelection);
    ui->action_Del->setEnabled(hasSelection);

    bool isSubWindowView = (activeMdiChild() && ui->mdiArea->viewMode() == QMdiArea::SubWindowView);
    ui->action_Cascade->setEnabled(isSubWindowView);//只有在窗口模式下平铺和层叠才起作用
    ui->action_Tile->setEnabled(isSubWindowView);

    ui->action_PreviousW->setEnabled(ui->mdiArea->subWindowList().count() > 1);//窗口数大于1时可用
    ui->action_NextW->setEnabled(ui->mdiArea->subWindowList().count() > 1);

    if(hasMdiChild)
    {
        this->setWindowTitle(ui->mdiArea->currentSubWindow()->windowTitle());//更新标题栏的显示
        if(!activeMdiChild()->extraSelections().empty())//判断当前的文档是否高亮显示
            ui->action_HighLightShow->setChecked(true);
        else
            ui->action_HighLightShow->setChecked(false);

        if(activeMdiChild()->wordWrapMode() == QTextOption::WrapAnywhere)//判断当前的文档是否自动换行
            ui->action_Switch->setChecked(true);
        else
            ui->action_Switch->setChecked(false);
    }

}

void TextEdit::updateMenu_SelectW()//更新“选择窗口”菜单
{
    //在菜单栏"选择窗口"显示当前打开的窗口
    ui->menu_SelectW->clear();//每次更新前清空
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    for (int i = 0; i < windows.size(); ++i) {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());
        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                    .arg(child->windowTitle().remove("[*]"));
        } else {
            text = tr("%1 %2").arg(i + 1)
                    .arg(child->windowTitle().remove("[*]"));
        }
        QAction *action  = ui->menu_SelectW->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void TextEdit::init_statusBar()//初始化状态栏
{
    QStatusBar* bar = ui->statusBar; //获取状态栏
    first_statusLabel = new QLabel; //新建标签
    first_statusLabel->setMinimumSize(200,20); //设置标签最小尺寸
    first_statusLabel->setFrameShape(QFrame::WinPanel); //设置标签形状
    first_statusLabel->setFrameShadow(QFrame::Sunken); //设置标签阴影

    second_statusLabel = new QLabel; //2
    second_statusLabel->setMinimumSize(200,20);
    second_statusLabel->setFrameShape(QFrame::WinPanel);
    second_statusLabel->setFrameShadow(QFrame::Sunken);

    third_statusLabel = new QLabel;//3
    third_statusLabel->setMinimumSize(200,20);
    third_statusLabel->setFrameShape(QFrame::WinPanel);
    third_statusLabel->setFrameShadow(QFrame::Sunken);

    bar->addWidget(first_statusLabel);
    bar->addWidget(second_statusLabel);
    bar->addWidget(third_statusLabel);

    first_statusLabel->setText(tr("欢迎使用多文档文本编辑器")); //初始化内容
    second_statusLabel->setText(tr("yafeilinux制作"));
    third_statusLabel->setText(tr("0000-00-00 00:00::00 星期 "));
}

void TextEdit::timerUpDate()//定时器更新时间的显示
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");//设置系统时间显示格式
    third_statusLabel->setText(str); //在标签上显示时间
}

void TextEdit::do_cursorChanged()//获取光标位置，并显示在状态栏
{
    QTextCursor cursor = activeMdiChild()->textCursor();
    //cursor.select(QTextCursor::LineUnderCursor);
    int rowNum = cursor.blockNumber(); //获取光标所在行的行号
    int colNum = cursor.columnNumber(); //获取光标所在列的列号
    first_statusLabel->setText(tr("%1行 %2列").arg(rowNum+1).arg(colNum+1));//在状态栏显示光标位置

    //更改对齐按钮的状态
    if(activeMdiChild()->alignment() == (Qt::AlignLeft | Qt::AlignAbsolute) )
        left->setChecked(true);
    if(activeMdiChild()->alignment() == Qt::AlignHCenter)
        center->setChecked(true);
    if(activeMdiChild()->alignment() == Qt::AlignJustify)
        justify->setChecked(true);
    if(activeMdiChild()->alignment() == (Qt::AlignRight | Qt::AlignAbsolute) )
        right->setChecked(true);

    highlightCurrentLine(); //关联鼠标位置与高亮的显示
}

void TextEdit::documentWasModified()//文档正在被修改
{
    second_statusLabel->setText(tr("正在修改"));
}

void TextEdit::slotAlignment(QAction *a)//更改对齐方式
{
    if(a == left)
        activeMdiChild()->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == center)
        activeMdiChild()->setAlignment(Qt::AlignHCenter);
    else if (a == right)
        activeMdiChild()->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == justify)
        activeMdiChild()->setAlignment(Qt::AlignJustify);
}

void TextEdit::slotList(int index)//文本排序
{
    QTextCursor cursor =  activeMdiChild()->textCursor();
    if(index != 0)
    {
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch(index)
        {
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style = QTextListFormat::ListUpperRoman;
            break;
        }
        cursor.beginEditBlock();//与end之间的所有操作相当于一个动作
        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;
        if (cursor.currentList())//是否已排序
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);//在当前段落缩进的基础上加1
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void TextEdit::on_action_New_triggered()//新建
{
    MdiChild *child = new MdiChild;
    ui->mdiArea->addSubWindow(child);
    child->newFile();
    child->setVisible(true);
    second_statusLabel->setText(tr("新建成功"));
    iniConnect();//初始化关联
}

void TextEdit::on_actionOpen_triggered()
{
    //qDebug()<<"make sense";
    video_full = QFileDialog::getOpenFileName(this,tr("打开视频文件"),"",tr("Medias (*.mp4 *.rmvb *.mkv *.avi *.3gp *.mov)"));
    videoInfo = QFileInfo(video_full);
    video_name = videoInfo.fileName();
    video_path = videoInfo.absolutePath();
}

void TextEdit::on_actionPlayer_triggered()
{
    player_full = QFileDialog::getOpenFileName(this);
    videoInfo = QFileInfo(player_full);
    player_name = videoInfo.fileName();
    player_path = videoInfo.absolutePath();
}

void TextEdit::on_actionPlay_triggered()
{
    if(videoIsPlaying!=1){
        if(video_full.isEmpty()) {QMessageBox::information(this,"播放失败","请选择视频文件");return;}
        if(player_name.isEmpty()) {QMessageBox::information(this,"播放失败","请选择播放器");return;}
        if(!video_full.isEmpty() && !player_name.isEmpty()){//播放 后期加入服务端的远程控制 如何循环播放 上下切换 降低延时
            on_actionStop_triggered();
            //ui->pushButton->setVisible(false);
            //ui->progressBar->setVisible(true);
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
            //ui->pushButton_3->setText("暂停");
        }
    }
}

void TextEdit::playerTime()
{
    pVideoProcess->write("get_time_pos\n");  //获得视频当前时间
    pVideoProcess->write("get_percent_pos\n");  //获得视频百分比
    pVideoProcess->write("get_time_length\n");  // 获得视频总时间
    connect(pVideoProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(back_message_slots()));
}

void TextEdit::back_message_slots()
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
            //ui->label_2->setText(totalTime);
            //ui->progressBar->setRange(0,totalTimeNum);
        }else if (b.startsWith("ANS_TIME_POSITION"))  //输出视频当前时间
        {
            int currentTimeNum = s.mid(18).toFloat();
            int currentTimeSec = (int)(currentTimeNum) % 60;
            int currentTimeMin = (int)(currentTimeNum) / 60;
            videoCurrentTime = QString("%1:%2").arg(currentTimeMin).arg(currentTimeSec);
            //ui->label->setText(videoCurrentTime);
            //ui->progressBar->setValue(currentTimeNum);
            //qDebug()<<"time"<<currentTimeNum;
        }else if(b.startsWith("ANS_PERCENT_POSITION"))
        {
            QString currentPercent = s.mid(21);
            //ui->label->setText(currentPercent + "%");  //视频播放进度百分比暂时不出输出
        }
    }
}

void TextEdit::on_actionPause_triggered()
{
    if(videoIsPlaying==1){//暂停
        //ui->pushButton_3->setText("播放");
        pVideoProcess->write("pause\n");
        videoIsPlaying=2;
    }
}
void TextEdit::on_actionStop_triggered()
{
    if(videoIsPlaying!=0) {
        /*ui->pushButton->setVisible(true);
        ui->pushButton_3->setText("播放");
        ui->pushButton_3->setDisabled(false);
        ui->progressBar->setValue(0);
        ui->progressBar->setHidden(true);*/
        pVideoProcess->write("quit\n");//system("killall mplayer");
        playerTimer->stop();
        pVideoProcess->kill();
        videoIsPlaying = 0;
    }
}
void TextEdit::on_actionQuickFast_triggered(){

}
void TextEdit::on_actionQuickBack_triggered(){

}
void TextEdit::on_actionMute_triggered(){

}
void TextEdit::on_action_2_triggered(){

}
void TextEdit::on_action_triggered(){

}

void TextEdit::on_action_Open_triggered()//打开
{
    QString fileName = QFileDialog::getOpenFileName//获得要打开的文件名
            (this,"open file",NULL,"(*.txt)"";;All File(*.*)"";;(*.html)");
    QFileInfo fi = QFileInfo(fileName);//file_name = fi.fileName();
    cutScreenPath = fi.absolutePath();
    if(!fileName.isEmpty())
    {
        QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
        bool hasOpened = false;//是否已经打开该文件
        foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
            if( mdiChild->currentFile() == canonicalFilePath)
            {
                hasOpened = true;
                ui->mdiArea->setActiveSubWindow(window);
                continue;
            }
        }
        if(!hasOpened)
        {
            MdiChild *child = new MdiChild;
            ui->mdiArea->addSubWindow(child);
            if(child->loadFile(fileName))
            {
                child->setVisible(true);
                second_statusLabel->setText(tr("打开成功"));
            }
            else
                child->close();

            QSettings settings("QT","MDI example");
            QStringList files = settings.value("recentFiles").toStringList();
            files.removeAll(fileName);
            files.prepend(fileName);
            while(files.size() > MaxRecentFiles)
                files.removeLast();
            settings.setValue("recentFiles",files);
            updateRecentFiles();
            iniConnect();//初始化关联
        }
    }
}

void TextEdit::on_action_Save_triggered()//保存
{
    if(activeMdiChild() && activeMdiChild()->save())
    {
        second_statusLabel->setText(tr("保存成功"));
    }
}

MdiChild *TextEdit::activeMdiChild()//返回激活状态的子窗口指针
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

void TextEdit::on_action_Asave_triggered()//另存为
{
    if (activeMdiChild() && activeMdiChild()->saveAs())
    {
        second_statusLabel->setText(tr("另存为成功"));
    }
}

void TextEdit::on_action_Quit_triggered()//退出
{
    qApp->closeAllWindows();
}

void TextEdit::on_action_Font_triggered()//字体设置
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,activeMdiChild()->font(),this,"font");
    if(ok)
    {
        activeMdiChild()->setCurrentFont(font);//current可以undo
    }
}

void TextEdit::on_action_FontColor_triggered()//字体颜色设置
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        activeMdiChild()->setTextColor(color);
    }
}

void TextEdit::on_action_Print_triggered()//打印文档
{
    QPrinter printer;
    QPrintDialog dlg(&printer,ui->mdiArea->activeSubWindow());
    if(dlg.exec() == QDialog::Accepted)
    {
        /****/
    }
}

void TextEdit::on_action_PrintPreview_triggered()//打印预览
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
            SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void TextEdit::printPreview(QPrinter *printer)//打印预览
{
#ifdef QT_NO_PRINTER
    Q_UNUSEd(printer);
#else
    // MdiChild *child = qobject_cast<MdiChild *>(ui->mdiArea->activeSubWindow()->widget());
    //child->print(printer);
    activeMdiChild()->print(printer);
#endif
}

//https://blog.csdn.net/u012234115/article/details/43603923 实例
void TextEdit::on_action_PDF_triggered()//输出PDF文档
{
    if(activeMdiChild())
    {
        QString fileName = QFileDialog::getSaveFileName(
                    this, "Export PDF",activeMdiChild()->curFile + ".pdf","*.pdf");
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(".pdf");
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            activeMdiChild()->document()->print(&printer);
            second_statusLabel->setText(tr("输出PDF文档成功"));
        }
    }
}

void TextEdit::on_action_Undo_triggered()//撤销
{
    activeMdiChild()->undo();
}

void TextEdit::on_action_Redo_triggered()//重复
{
    activeMdiChild()->redo();
}

void TextEdit::on_action_Cut_triggered()//剪切
{
    activeMdiChild()->cut();
}

void TextEdit::on_action_Copy_triggered()//复制
{
    activeMdiChild()->copy();
}

void TextEdit::on_action_Paste_triggered()//粘贴
{
    activeMdiChild()->paste();
}

void TextEdit::on_action_Del_triggered()//删除选中的内容
{
    activeMdiChild()->textCursor().removeSelectedText();
}

void TextEdit::on_action_AllSelect_triggered()//全选
{
    activeMdiChild()->selectAll();
}

void TextEdit::on_action_Clear_triggered()//清空
{
    activeMdiChild()->clear();
}

void TextEdit::on_action_Switch_triggered(bool checked)//是否自动换行
{
    if(checked == true)
        activeMdiChild()->setWordWrapMode(QTextOption::WrapAnywhere);
    else
        activeMdiChild()->setWordWrapMode(QTextOption::NoWrap);
}


void TextEdit::on_action_ToobarShow_triggered(bool checked)//是否显示工具栏
{
    if(checked == true)
    {
        ui->mainToolBar->show();
        toolBar->show();
    }
    else
    {
        ui->mainToolBar->hide();
        toolBar->hide();
    }
}

void TextEdit::on_action_StatusBarShow_triggered(bool checked)//是否显示状态栏
{
    if(checked == true)
        ui->statusBar->show();
    else
        ui->statusBar->hide();
}

void TextEdit::on_action_HighLightShow_triggered(bool checked)//是否高亮显示当前编辑的行
{
    if(checked == true)
        highlightCurrentLine();
    else
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        activeMdiChild()->setExtraSelections(extraSelections);
        activeMdiChild()->extraSelections().clear();
    }
}

void TextEdit::highlightCurrentLine()//高亮显示当前编辑的行
{
    if(ui->action_HighLightShow->isChecked() == true)//是否选中高亮显示
    {
        QList<QTextEdit::ExtraSelection> extraSelections;

        if (!activeMdiChild()->isReadOnly()) {
            QTextEdit::ExtraSelection selection;

            QColor lineColor = QColor(Qt::yellow).lighter(160);

            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = activeMdiChild()->textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }
        activeMdiChild()->setExtraSelections(extraSelections);
    }
}


void TextEdit::on_action_Tile_triggered()//平铺
{
    ui->mdiArea->tileSubWindows();
}

void TextEdit::on_action_Cascade_triggered()//层叠
{
    ui->mdiArea->cascadeSubWindows();
}

void TextEdit::on_action_NextW_triggered()//下一窗口
{
    ui->mdiArea->activateNextSubWindow();
}

void TextEdit::on_action_PreviousW_triggered()//前一窗口
{
    ui->mdiArea->activatePreviousSubWindow();
}

void TextEdit::on_action_Close_triggered()//关闭当前窗口
{
    ui->mdiArea->closeActiveSubWindow();
}

void TextEdit::on_action_AllClose_triggered()//关闭所有窗口
{
    ui->mdiArea->closeAllSubWindows();
}

void TextEdit::on_action_About_triggered()//关于
{
    QMessageBox box;
    box.setWindowTitle(tr("关于"));
    box.setIcon(QMessageBox::Information);
    box.setText(tr("本软件由yafeilinux制作，是开源、共享、自由软件\n可以在网上传播、交流和下载，但请不要用作商业用途!\n\n多文档文本编辑器V1.0 Beta\n问题交流与BUG报告请联系：www.yafeilinux.com"));
    box.addButton(tr("确定"),QMessageBox::AcceptRole);//加入自定义的按钮
    if(box.exec() == QMessageBox::Accepted)
        box.close();
}

void TextEdit::on_action_AboutQt_triggered()//关于Qt
{
    QMessageBox::aboutQt(this,tr("关于Qt"));
}

void TextEdit::setActiveSubWindow(QWidget *window)//激活窗口
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void TextEdit::readSettings()//读取主窗口的大小、位置信息
{
    QSettings settings("yafeilinux", "MDI Example");
    QPoint pos = settings.value("pos", QPoint(250, 100)).toPoint();
    QSize size = settings.value("size", QSize(820, 600)).toSize();
    move(pos);
    resize(size);
}

void TextEdit::writeSettings()//记录主窗口的大小、位置信息
{
    QSettings settings("yafeilinux","MDI Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void TextEdit::closeEvent(QCloseEvent *event)//重写关闭事件
{
    ui->mdiArea->closeAllSubWindows();
    if (ui->mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}

void TextEdit::doFind(QString findText)//查找的实现函数
{
    if( (!senceF) && (!upFindF) )//不区分大小写，向后查找
    {
        if(!activeMdiChild()->find(findText))
        {
            QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
        }
    }
    else if( senceF && (!upFindF) )//区分大小写，向后查找
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindCaseSensitively))
        {
            QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
        }
    }
    else if( (!senceF) && upFindF )//不区分大小写，向前查找
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindBackward))
        {
            QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
        }
    }
    else if( senceF && upFindF)//区分大小写，向前查找
    {
        if(!activeMdiChild()->find(findText, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward))
        {
            QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));
        }
    }
}

void TextEdit::on_action_Find_triggered()//显示查找对话框
{
    findReplace->show();
    findReplace->ui->tabWidget->setCurrentWidget(findReplace->ui->find);//显示查找页面
    findReplace->ui->lineEditF->setFocus();
    second_statusLabel->setText(tr("正在查找"));

}

void TextEdit::findNextF()//“查找”的“查找下一个”
{
    QString findText = findReplace->ui->lineEditF->text();
    senceF = findReplace->ui->checkBoxSenceF->isChecked();//是否区分大小写，1区分 0不区分
    upFindF = findReplace->ui->radioButtonUpF->isChecked();//向前还是向后查找，1向前 0向后

    doFind(findText);

}

void TextEdit::on_action_Replace_triggered()//显示替换对话框
{
    findReplace->show();
    findReplace->ui->tabWidget->setCurrentWidget(findReplace->ui->replace);//显示替换页面
    findReplace->ui->lineEditR->setFocus();
    second_statusLabel->setText(tr("正在替换"));
}

void TextEdit::findNextR()//“替换”的“查找下一个”
{
    QString findText = findReplace->ui->lineEditR->text();
    senceF = findReplace->ui->checkBoxSenceR->isChecked();//是否区分大小写，1区分 0不区分
    upFindF = findReplace->ui->radioButtonUpR->isChecked();//向前还是向后查找，1向前 0向后

    doFind(findText);
}

void TextEdit::replace()//替换
{   
    QString findText = findReplace->ui->lineEditR->text();//要查找的内容
    QString replaceText = findReplace->ui->lineEditreplace->text();//要替换的内容
    if(activeMdiChild()->textCursor().selectedText() == findText)
    {
        QTextCursor textCursor = activeMdiChild()->textCursor();
        textCursor.insertText(replaceText);
    }
    findNextR();//“替换”的“查找下一个”
}

void TextEdit::replaceAll()//全部替换
{
    QTextCursor textCursor = activeMdiChild()->textCursor();
    textCursor.setPosition(0,QTextCursor::MoveAnchor);//先让光标跳到文章的最开始
    activeMdiChild()->setTextCursor(textCursor);
    findReplace->ui->radioButtonUpR->setChecked(false);//确定向后查找
    senceF = findReplace->ui->checkBoxSenceR->isChecked();//是否区分大小写，1区分 0不区分

    QString findText = findReplace->ui->lineEditR->text();//要查找的内容
    QString replaceText = findReplace->ui->lineEditreplace->text();//要替换的内容

    while(doReplaceAllFind(findText))//循环替换
    {
        if(activeMdiChild()->textCursor().selectedText().toLower() == findText.toLower())
        {
            QTextCursor textCursor = activeMdiChild()->textCursor();//和上面的textCursor不一样
            textCursor.insertText(replaceText);
        }
    }
}
bool TextEdit::doReplaceAllFind(QString findText)//全部替换的查找实现函数
{
    if( (!senceF) && (!upFindF) )//不区分大小写，向后查找
    {
        if(!activeMdiChild()->find(findText))
        {
            return false;
        }
    }
    else if( senceF && (!upFindF) )//区分大小写，向后查找
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindCaseSensitively))
        {
            return false;
        }
    }
    return true;
}

void TextEdit::on_action_zoomIn_triggered()//放大，对图片、更改了字体的内容没有效果！
{
    activeMdiChild()->zoomIn(2);
}

void TextEdit::on_action_zoomOut_triggered()//缩小
{
    activeMdiChild()->zoomOut(2);
}

void TextEdit::dragEnterEvent(QDragEnterEvent *e)//拖进事件
{
    if(e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void TextEdit::dropEvent(QDropEvent *event)//放下事件
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
    {
        return;
    }
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    bool hasOpened = false;//是否已经打开该文件
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if( mdiChild->currentFile() == canonicalFilePath)
        {
            hasOpened = true;
            ui->mdiArea->setActiveSubWindow(window);
            continue;
        }
    }
    if(!hasOpened)
    {
        MdiChild *child = new MdiChild;
        ui->mdiArea->addSubWindow(child);
        if(child->loadFile(fileName))
        {
            child->setVisible(true);
            second_statusLabel->setText(tr("打开成功"));
            iniConnect();
            QSettings settings("QT","MDI example");
            QStringList files = settings.value("recentFiles").toStringList();
            files.removeAll(fileName);
            files.prepend(fileName);
            while(files.size() > MaxRecentFiles)
                files.removeLast();
            settings.setValue("recentFiles",files);
            updateRecentFiles();
        }
        else
            child->close();
    }
}

void TextEdit::iniConnect()//初始化关联
{
    connect(activeMdiChild(),SIGNAL(cursorPositionChanged()),this,SLOT(do_cursorChanged()));//关联鼠标位置
    connect(activeMdiChild()->document(),SIGNAL(contentsChanged()),SLOT(documentWasModified()));
    connect(activeMdiChild()->document(),SIGNAL(undoAvailable(bool)),ui->action_Undo,SLOT(setEnabled(bool)));
    connect(activeMdiChild()->document(),SIGNAL(redoAvailable(bool)),ui->action_Redo,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Copy,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Cut,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Del,SLOT(setEnabled(bool)));
    /**用于实现自定义右键菜单**/
    connect(activeMdiChild(),SIGNAL(fontChang()),SLOT(on_action_Font_triggered()));
    connect(activeMdiChild(),SIGNAL(fontColor()),SLOT(on_action_FontColor_triggered()));
    connect(activeMdiChild(),SIGNAL(Del()),SLOT(on_action_Del_triggered()));
}

void TextEdit::contextMenuEvent(QContextMenuEvent *event)
{

}

//标记时刻
void TextEdit::on_pushButton_clicked()
{
    activeMdiChild()->append(videoCurrentTime+"  ");
    //ui->textEdit->append(videoCurrentTime+"  ");
}

//截屏
void TextEdit::on_pushButton_2_clicked()
{
    QScreen *screen=QGuiApplication::primaryScreen();//"E:/qt/qtCode/project/TextEdit/"
    qDebug()<<"cutScreenPath:"<<cutScreenPath;
    QString filePathName = cutScreenPath + "/" + video_name.left(video_name.length() - 4).append("-");
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    filePathName += " " + videoCurrentTime;
    filePathName += ".jpg";
    activeMdiChild()->save();
    if(!screen->grabWindow(ui->videoWidget->winId()).save(filePathName, "jpg"))
    {
        qDebug()<<"save full screen failed";
    }
}
