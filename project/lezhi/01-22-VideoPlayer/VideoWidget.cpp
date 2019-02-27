#include "VideoWidget.h"

#include<QWidget>
#include<QDebug>
#include<QColor>
#include<QVideoWidget>
#include<QPoint>
#include<QList>
#include<QUrl>
#include<QMenu>
#include<QAction>
#include<QString>
#include<QTimer>
#include<QMimeData>
#include<QCursor>
#include<QVBoxLayout>
#include<QContextMenuEvent>
#include<QDragEnterEvent>
#include<QDropEvent>

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent), PADDING(2), buttonHeight(20),buttonWidth(20),  windowIniHeight(600), windowIniWidth(800),clickCount(1),isLeftPressDown(false),
    dir(NONE),b_fulScreen(false)
{
    this->setMouseTracking(true);
    this->setCursor(QCursor(Qt::ArrowCursor));
    this->setAutoFillBackground(true);
    this->setStyleSheet("QVideoWidget{background-color:rgb(0,0,0);}");
    setWindowOpacity(1);//设置透明度
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint); // 设置成无边框对话框
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAcceptDrops(true);    //设置可以接受拖拽

}
void VideoWidget::contextMenuEvent(QContextMenuEvent * event)
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(" QMenu{border:none ;} "
                                          "QMenu::item{border:none; color:rgb(30,30,30); background-color:rgb(160,160,160); font-size:13px;  padding-left:20px; "
                                                                   "background-color:white; height:28px; width:120px; }"
                                          "QMenu::item:selected{color:rgb(255,255,255); background-color:rgb(140,140,240)}; "
                        );
    QAction *actionOpen =  menu->addAction("打开");
    //QAction *actionFrameCapture = menu->addAction("截图");
   // QAction *actionInfo    =  menu->addAction("媒体信息");
    //QAction *action

    connect(actionOpen, &QAction::triggered, [this](){emit signalActionOpen(); });
    //connect(actionInfo, &QAction::triggered, [this](){emit signalActionInfo(); });

    menu->exec(QCursor::pos());
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{
     //qDebug()<<event->pos();
    //mouseGlobalPos = event->globalPos();
    QPoint topLeftPoint (0, this->height()-140);
    QPoint rightBottomPoint(this->width(), this->height());
    topLeftPoint  = this->mapToGlobal(topLeftPoint);
    rightBottomPoint = this->mapToGlobal(rightBottomPoint);
    QPoint mouseGlobalPoint = this->mapToGlobal(event->pos());

    if(!isLeftPressDown)  //如果左键没有按下，则更新鼠标相对于Widget的位置信息
    {
        //this->region(mouseGlobalPoint);
        //是否到达设定的区域使bottomWidget隐藏
        if(topLeftPoint.y() < mouseGlobalPoint.y())
        {
            //qDebug()<<" emit signalInBottomRegion();";
            emit signalInBottomRegion();
        }
        else
        {
            //qDebug()<<" emit signalOutBottomRegion();";
            emit signalOutBottomRegion();
        }
        //是否到达设定的区域使hideButton隐藏
        if(mouseGlobalPoint.x() > (rightBottomPoint.x()-100))
        {
             //  qDebug()<<" emit signalInRightRegion();";
            emit signalInRightRegion();
        }
        else
        {
            //qDebug()<<" emit signalOutRightRegion();";
            emit signalOutRightRegion();
        }
    }
    else
    {
         emit signalMovePoint(event->globalPos()-dragPosition);
        //qDebug()<<"event->globalPos()-dragPosition:  "<<event->globalPos()-dragPosition;
   }
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
       // emit signalLeftPressDown(false);
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    switch(event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        emit signalLeftPressDown(true);
        if(dir != NONE)
        {
            this->mouseGrabber();
        }
        else
        {
            dragPosition = event->globalPos() ;

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

void VideoWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    //setFullScreen(!isFullScreen());
    //event->accept();
    if(event->button() == Qt::LeftButton)
    {
        emit doubleClicked();
    }

}

void VideoWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void VideoWidget::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return ;
    emit signalDropedList(urls);
}
