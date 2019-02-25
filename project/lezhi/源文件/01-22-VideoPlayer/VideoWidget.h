#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include"VolumeSlider.h"
#include"MainSlider.h"
#include<QEvent>
#include<QMouseEvent>
#include <QWidget>
#include<QPoint>
#include<QUrl>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QListWidget>
#include<QPushButton>
#include<QVideoWidget>
#include<QContextMenuEvent>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent * event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent*event);
 //   int getWindowIniWidth() const {return windowIniWidth;}
  //  int getWindowIniHeight()const {return windowIniHeight; }


signals:
    void signalInBottomRegion();
    void signalOutBottomRegion();
    void signalInRightRegion();
    void signalOutRightRegion();
    void signalMovePoint(QPoint);
    void signalLeftPressDown(bool);
    void doubleClicked();
    void signalDropedList(QList<QUrl> urls);
    void signalActionOpen();
    void signalActionInfo();

private:
    enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    const int PADDING ;
    const int buttonWidth ;
    const int buttonHeight ;
    const int windowIniWidth;
    const int windowIniHeight;

    QRect normalRect;       //保存最大化以前的大小，因为最小化以前this->rect()已经变成了全屏时的rect()
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;    // 窗口移动拖动时需要记住的点
    Direction dir;                // 窗口大小改变时，记录改变方向

    int fullScreenWidth;
    int fullScreenHeight;
    int clickCount;
    bool b_fulScreen;





public slots:
};

#endif // MAINWIDGET_H
