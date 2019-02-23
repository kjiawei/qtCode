/*************************************************
 *2013.7.31-2013.8.04
 *mylrc.h
 *QP1301_
 *功能:对歌词显示模块各变量的声明
 *************************************************
 */

#ifndef MYLRC_H
#define MYLRC_H

#include <QLabel>
#include <QDesktopWidget>//

class Mylrc : public QLabel
{
    Q_OBJECT
public:
    explicit Mylrc(QWidget *parent = 0);
    void startLrcMask(qint64 intervalTime);
    void stopLrcMask();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void contextMenuEvent(QContextMenuEvent *ev);


    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
    QFont font;
    QTimer *timer;
    qreal lrcMaskWidth;
    qreal lrcMaskWidthInterval;
    QPoint offset;
    QDesktopWidget *desk;//

public slots:
    void outtime();

};

#endif // MYLRC_H
