#include "ListWidget.h"
#include<QScrollBar>
#include<QPalette>
#include<QColor>
#include<QDebug>
#include<QMouseEvent>
#include<QString>
#include<QUrl>
#include<QListWidget>
#include<QListWidgetItem>
#include<QMenu>
#include<QFileDialog>
#include<QAction>
#include<QCursor>
#include<QDesktopServices>

ListWidget::ListWidget(QWidget *parent):QListWidget(parent), indexInPlayList(-1)
{

    //播放列表水平滑动条
    QScrollBar* horizontalScroll = new QScrollBar(Qt::Horizontal);
    QPalette palette(QColor(70,70,70));
    horizontalScroll->setStyleSheet("QScrollBar::handle{background-color:rgb(110,110,110);}"
                                      "QScrollBar::handle:hover{background-color:rgb(160,160,160);}"
                                       );
    horizontalScroll->setPalette(palette);

    //播放列表竖直滑动条
    QScrollBar* verticalScroll = new QScrollBar(Qt::Vertical);
    QPalette palette2(QColor(70,70,70));
    //scroll->setAutoFillBackground(true);
    verticalScroll->setStyleSheet("QScrollBar::handle{background-color:rgb(110,110,110);}"
                                      "QScrollBar::handle:hover{background-color:rgb(160,160,160);}"
                                       );
    verticalScroll->setPalette(palette2);

    this->setStyleSheet("QListWidget{border:0px; background-color:rgb(33,33,33)}"
                                              "QListWidget::item:hover{color:rgb(180,180,255);background-color:rgb(70,70,70); outline:0px;}"
                                              "QListWidget::item{padding-left:5px; padding-top:5px ; padding-bottom:5px; padding-right:5px;"
                                                                      " background-color:rgb(50,50,50); color:rgb(200,200,200); height:20px}"

                                              "QListWidget::item:selected:!active{color:rgb(180,180,255);background-color:rgb(70,70,70); outline:0px; }"
                                              );
    this->setFocusPolicy(Qt::NoFocus);
    this->setHorizontalScrollBar(horizontalScroll);
    this->setVerticalScrollBar(verticalScroll);
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::ArrowCursor));

}

void ListWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
        if(event->button() == Qt::LeftButton)
        {
            QString name;
            if(this->itemAt(event->pos()))
            {
                 name = (this->itemAt(event->pos()) )->text();
                 emit ItemDoubleClick(name);
            }
        }
}


void ListWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setCurrentRow(indexInPlayList);
    }
}

void ListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCurrentRow(this->getIndex());
}

void ListWidget::contextMenuEvent(QContextMenuEvent *menuEvent)
{
    QMenu * menu = new QMenu(this);
    menu->setStyleSheet(" QMenu{border:none ;} "
                                          "QMenu::item{border:none; color:rgb(30,30,30); background-color:rgb(160,160,160); font-size:13px;  padding-left:20px; "
                                                                   "background-color:white; height:28px; width:120px; }"
                                          "QMenu::item:selected{color:rgb(255,255,255); background-color:rgb(140,140,240)}; "
                        );
    QAction *actionOpen                = menu->addAction("打开");
    QAction *actionPlay                  = menu->addAction("播放");
    QAction *actionOpenDirectory = menu->addAction("打开文件所在目录");
    QAction *actionDelete              = menu->addAction("删除");
    QAction *actionClearValidItem = menu->addAction("删除失效记录");
    QAction *actionClearAll            = menu->addAction("清空列表");

    connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotActionDeleteItem()));
    connect(actionClearAll, SIGNAL(triggered(bool)), this, SLOT(slotActionClearAll()));
    connect(actionClearValidItem,&QAction::triggered, this, &ListWidget::slotActionClearValidItem);
    connect(actionOpen, &QAction::triggered, this, &ListWidget::slotActionOpen);
    connect(actionOpenDirectory, &QAction::triggered, this, &ListWidget::slotActionOpenDirectory);
    connect(actionPlay, &QAction::triggered, this, &ListWidget::slotActionPlay);

    menu->exec(QCursor::pos());
}

void ListWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePos=event->pos();
}

void ListWidget::slotActionOpen()
{
    emit signalActionOpen();

}

//
void ListWidget::slotActionDeleteItem()
{
    int count = this->count();
    if(mousePos.y()<count*30)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item  = this->itemAt(mousePos);
        int row = this->row(item);
        //qDebug()<<item->flags();
        this->setCurrentRow(this->getIndex());

        emit ItemDeleted(row);
    }
}

void ListWidget::slotActionClearValidItem()
{
    emit signalClearValidItem();
}


void ListWidget::slotActionClearAll()
{
    emit signalClearAll();
}

void ListWidget::slotActionPlay()
{
    QString name;
    if(this->itemAt(mousePos))
    {
         name = (this->itemAt(mousePos))->text();
         emit ItemDoubleClick(name);
    }
}

void ListWidget::slotActionOpenDirectory()
{
    int count = this->count();
    if(mousePos.y()<count*30)
    {
        QListWidgetItem * item = new QListWidgetItem;
        item  = this->itemAt(mousePos);
        int row = this->row(item);
        //qDebug()<<item->flags();
        this->setCurrentRow(this->getIndex());
        emit signalOpenDirectory(row);

    }



    //fileDialog.open();
}
