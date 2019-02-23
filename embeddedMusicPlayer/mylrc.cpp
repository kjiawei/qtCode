#include "mylrc.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QApplication>

/*********************************************
*功能：歌词显示部件初始化及歌词显示的效果
*函数名：Mylrc::mylrc(QLabel *)
*参数：QLabel *
*返回值：无
**********************************************
*/
Mylrc::Mylrc(QWidget *parent) :
    QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    setText(tr("Mp3>MusicPlayer ---小超 中举linux作品"));
    // 固定部件大小
    setMaximumSize(800, 60);
    setMinimumSize(800, 60);

    // 歌词的线性渐变填充
    linearGradient.setStart(0, 10);
    linearGradient.setFinalStop(0, 40);
    linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    // 遮罩的线性渐变填充
    maskLinearGradient.setStart(0, 10);
    maskLinearGradient.setFinalStop(0, 40);
    maskLinearGradient.setColorAt(0.1, QColor(222, 54, 4));
    maskLinearGradient.setColorAt(0.5, QColor(255, 72, 16));
    maskLinearGradient.setColorAt(0.9, QColor(222, 54, 4));
    // 设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);
    setAlignment(Qt::AlignCenter);
    // 设置定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(outtime()));

    //设置歌词位置
    desk = new QDesktopWidget;
    desk = QApplication::desktop();
    move(((desk->width()/2) - (this->width()/3)) , (desk->height() - this->height()) - 15);

}
/********************************************/
/*******************************************
*功能：设置歌词限制效果
*函数名：void paintEvent(QPaintEvent *)
*参数：QPaintEvent *
*返回值：void
********************************************
*/
void Mylrc::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setFont(font);
    // 先绘制底层文字，作为阴影
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(1, 1, 800, 60, Qt::AlignLeft, text());
    // 再在上面绘制渐变文字
    painter.setPen(QPen(linearGradient, 0));
    painter.drawText(0, 0, 800, 60, Qt::AlignLeft, text());

    // 设置歌词遮罩
    painter.setPen(QPen(maskLinearGradient, 0));
    painter.drawText(0, 0, lrcMaskWidth, 60, Qt::AlignLeft, text());
}
/*******************************************/
/*******************************************
*功能：开启遮罩，需要指定当前歌词开始与结束之间的时间间隔
*函数名：void startLrcMask(qint64 intervalTime)
*参数：qint64 类型
*返回值：void
********************************************
*/
void Mylrc::startLrcMask(qint64 intervalTime)
{
    //qDebug("Time = %d\n", intervalTime);
   // 这里设置每隔30毫秒更新一次遮罩的宽度，因为如果更新太频繁
   // 会增加CPU占用率，而如果时间间隔太大，则动画效果就不流畅了
   qreal count = intervalTime / 30;
   // 获取遮罩每次需要增加的宽度，这里的200是部件的固定宽度
   lrcMaskWidthInterval = 800 / count;
   lrcMaskWidth = 0;
   timer->start(30);
}
/*******************************************/
/*******************************************
*功能：实现歌词显示部件鼠标右键隐藏
*函数名：void contextMenuEvent(QContextMenuEvent *)
*参数：QContextMenuEvent *
*返回值：void
********************************************
*/
void Mylrc::contextMenuEvent(QContextMenuEvent *ev)
{
   QMenu menu;
   menu.addAction(tr("隐藏"),this,SLOT(hide()));
   menu.exec(ev->globalPos());
}
/*******************************************/
/*******************************************
*功能：停止遮罩
*函数名：void stopLrcMask()
*参数：无
*返回值：void
********************************************
*/
void Mylrc::stopLrcMask()
{
   timer->stop();
   lrcMaskWidth = 0;
   update();
}
/*******************************************/
/*******************************************
*功能：两个鼠标事件处理函数实现了部件的拖动
*函数名：void mousePressEvent(QMouseEvent *)
*      void mouseMoveEvent(QMouseEvent *)
*参数：QMouseEvent *
*返回值：void
********************************************
*/
void Mylrc::mousePressEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
   offset = event->globalPos() - frameGeometry().topLeft();
}
void Mylrc::mouseMoveEvent(QMouseEvent *event)
{
   if (event->buttons() & Qt::LeftButton)
   {
      setCursor(Qt::PointingHandCursor);
      move(event->globalPos() - offset);
   }
}
/*******************************************/
/*******************************************
*功能：定时器溢出时增加遮罩的宽度，并更新显示
*函数名：void timeout(void)
*参数：void
*返回值：void
********************************************
*/
void Mylrc::outtime()
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();
}
/******************************************/
