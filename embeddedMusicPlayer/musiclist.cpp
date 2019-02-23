/*******************************************
 *MusicList.cpp
 *功能：歌曲列表部件的实现
 *QP1301_
 *2013.7.31-2013.8.04
 *******************************************
 */

#include "musiclist.h"

MusicList::MusicList(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("播放列表"));
    // 设置窗口标志，表明它是一个独立窗口且有一个只带有关闭按钮的标题栏
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    // 设置初始大小，并且锁定部件宽度
    resize(200, 240);
    setMaximumWidth(200);
    setMinimumWidth(200);

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/images/ok.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(pal);

    listModel_0 = new PlaylistModel;
    listModel_1 = new PlaylistModel;


    list_0 = new QListView(this);
    list_0->setModel(listModel_0);
    QPalette pal_0 = list_0->palette();
    pal_0.setBrush(QPalette::Base,QBrush(QColor(0,250,255,0)));
    list_0->setPalette(pal_0);


    list_1 = new QListView(this);
    list_1->setModel(listModel_1);
    QPalette pal_1 = list_1->palette();
    pal_1.setBrush(QPalette::Base,QBrush(QColor(0,250,255,0)));
    list_1->setPalette(pal_1);

    list_widget = new QListWidget(this);
    list_widget->setStyleSheet("background-color: rgba(0,0,0,0);borde    r: 2px groove gray;border-top-left-radius:6px;border-top-right-radius:    0px;border-bottom-left-radius:6px;border-bottom-right-radius:0px;paddi    ng-left:15px;padding-right:15px;");
    list_widget->setMaximumSize(45, 1000);
    list_widget->setMinimumHeight(45);
    list_widget->insertItem(0, tr("经典"));
    list_widget->insertItem(1, tr("流行"));

    QStackedWidget *stack = new QStackedWidget;
    stack->addWidget(list_0);
    stack->addWidget(list_1);

    QHBoxLayout *layout_h = new QHBoxLayout(this);
    layout_h->addWidget(list_widget, 0, Qt::AlignLeft);
    layout_h->addWidget(stack, 0, Qt::AlignLeft);
    layout_h->setMargin(0);
    layout_h->setSpacing(0);

    setLayout(layout_h);

    connect(list_widget, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
    connect(list_0, SIGNAL(clicked(QModelIndex)), this, SLOT(list_0_current_index(QModelIndex)));
    connect(list_1, SIGNAL(clicked(QModelIndex)), this, SLOT(list_1_current_index(QModelIndex)));
    connect(list_0, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(list_0_current_index(QModelIndex)));
    connect(list_1, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(list_1_current_index(QModelIndex)));
    connect(list_0, SIGNAL(activated(QModelIndex)), this, SLOT(list_0_current_index(QModelIndex)));
    connect(list_1, SIGNAL(activated(QModelIndex)), this, SLOT(list_1_current_index(QModelIndex)));
    connect(list_0, SIGNAL(pressed(QModelIndex)), this, SLOT(list_0_current_index(QModelIndex)));
    connect(list_1, SIGNAL(pressed(QModelIndex)), this, SLOT(list_1_current_index(QModelIndex)));

    desk = new QDesktopWidget;
    desk = QApplication::desktop();
    move((desk->width() - (this->width()*2)) , (desk->height()/3));

}

// 上下文菜单事件处理函数，当点击鼠标右键时运行一个菜单
void MusicList::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.setIcon(QIcon(":/images/8.png"));
    menu.addAction(QIcon(":/images/gtk-open.png"), tr("添加"), this, SLOT(addMediaPlay()));
    menu.addAction(QIcon(":/images/exit.png"), tr("删除"), this, SLOT(remove_inedx()));
    menu.addSeparator();
    menu.addAction(QIcon(":/images/remove.png"), tr("清空列表"), this, SLOT(clearPlaylist()));
    menu.exec(event->globalPos());
}

// 清空播放列表
void MusicList::clearPlaylist()
{

    // 发射播放列表清空信号
    emit playlistClean();
}

/*******************************************
*功能： 发射添加歌曲信号
*函数名：void addMediaPlay()
*参数类型：无
*返回值：void
********************************************
*/
void MusicList::addMediaPlay()
{
    emit addMedia();
}

// 关闭事件处理函数，如果部件处于显示状态，则使其隐藏
void MusicList::closeEvent(QCloseEvent *event)
{
    if (isVisible())
    {
        hide();
        event->ignore();
    }
}

/*******************************************
*功能：部件状态
*函数名：void show_hide()
*参数类型：无
*返回值：void
********************************************
*/
void MusicList::show_hide()
{
    if(this->isVisible())
    {
        this->hide();
    }
    else
    {
        this->show();
    }

}


/*******************************************
*功能：信号函数
*函数名： void list_0_current_index(QModelIndex index)
*        void list_1_current_index(QModelIndex index)
*        void remove_inedx()
*参数类型： QModelIndex index
*          QModelIndex index
*        无
*返回值：void
********************************************
*/
void MusicList::list_0_current_index(QModelIndex index)
{
    emit List_0_IndexChange(index.row());
}

void MusicList::list_1_current_index(QModelIndex index)
{
    emit list_1_IndexChange(index.row());
}



void MusicList::remove_inedx()
{
    emit remove_sign();
}
/*******************************************
*功能：
*函数名：void setPlayList_1(QMediaPlaylist *playlist)
*       void setPlayList_0(QMediaPlaylist *playlist)
*参数类型：QMediaPlaylist *
*        QMediaPlaylist *
*返回值：void
********************************************
*/
void MusicList::setPlayList_0(QMediaPlaylist *playlist)
{
    listModel_0->setPlaylist(playlist);
}

void MusicList::setPlayList_1(QMediaPlaylist *playlist)
{
    listModel_1->setPlaylist(playlist);
}







