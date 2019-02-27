#ifndef WIDGET_H
#define WIDGET_H

#include"VideoWidget.h"
#include"MainSlider.h"
#include"VolumeSlider.h"
#include"ListWidget.h"
#include <QWidget>
#include<QMouseEvent>
#include<QPoint>
#include<QRect>
#include<QGroupBox>
#include<QString>
#include<QMap>
#include<QPushButton>
#include<QModelIndex>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QComboBox>
#include<QLabel>
#include<QSlider>
#include<QEvent>
#include<QTimer>
#include<QObject>
#include<QMouseEvent>
#include<QMenu>
#include<QVector>
#include<QPair>
#include<QMultiMap>
#include<QListWidget>
#include<QAction>
#include<QSqlTableModel>
#include<QMediaPlaylist>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //inline void getFullScreen(QRect rect) { fullScreen = rect;}

    void region(const QPoint &cursorGlobalPoint);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QMouseEvent *);
    void enterEvent(QMouseEvent *);
    bool eventFilter(QObject* target, QEvent * event);
    void setThreeButton();
    //void getScreenRect(int height, int width);
    //void contextMenuEvent(QContextMenuEvent *);
    int getWindowIniWidth() const {return windowIniWidth;}
    int getWindowIniHeight()const {return windowIniHeight; }
    //void setWindowIniRect(int w,int h){windowIniWidth=w; windowIniHeight=h;normalRect.setWidth(w);normalRect.setHeight(h);}
    QString getNameFromPath(const QString &fileName);
    QString digitalToTime(const int& number);
    QString removeIndexFromAppend( QString name);
    void iniDatabase();
    void updateToDataBase();
    void addFile(const QString fileName);
private:
    Ui::Widget *ui;

    enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
    const int PADDING ;
    const int buttonWidth ;
    const int buttonHeight ;
    const int windowIniWidth;
    const int windowIniHeight;
    static QPoint Position;  //相应videoWidget的

    //窗体
    QRect normalRect;       //保存最大化以前的大小，因为最小化以前this->rect()已经变成了全屏时的rect()
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;    // 窗口移动拖动时需要记住的点
    Direction dir;                // 窗口大小改变时，记录改变方向
    QPushButton * closeButton;
    QPushButton * minimumButton ;
    QPushButton * maximumButton ;
    QWidget  * groupBox;
    QWidget  * bottomWidget;
    ListWidget * listWidget;
    //QMultiMap<QString, QString> multimap;
    QVector<QPair<QPair<QString, QString>, QString > > vector;   //name  fileName  nameAppendIndex
    //QMediaPlaylist * playList;
    const int screenWidth;
    const int screenHeight;
    int clickCount;
    //QRect fullScreen;
    QLabel *  titleLabel;
    bool volumeWidgetEntered;
    bool playModeWidgetEntered;
    bool inBottomRegion;
    bool inRightRegion;
    QListWidget* playModeListWidget;
    QPoint mouseGlobalPos;
    QPushButton * hideButton;

    bool isVideoMouseLeftDown;

    QPoint videoMouseBeforeDragPoint;
    int playingIndex;
    enum PlayingMode{CurrentItemOnce,CurrentItemInLoop, Sequential, Loop,Random};
    PlayingMode playingMode;
    //QSqlDatabase  db;

    //qint64 totalPlayTime;
    //菜单
    QPushButton* menuButton;
    QMenu* menu;
    QAction * openAction;

    //播放器控件
    QMediaPlayer  *  mediaPlayer0;
    //QMediaPlayer  *  mediaPlayerWithList;
    VideoWidget *  videoWidget0;


    QPushButton    *  openButton;
    QPushButton    *  stopButton;
    QPushButton    *  lastVideoButton;
    QPushButton    *  nextVideoButton;
    QPushButton    *  playButton;
    QPushButton    *  playModeButton;
    QPushButton    *  volumeButton;
    QWidget * volumeWidget;
    VolumeSlider * volumeSlider;
    MainSlider * slider;
    QLabel  * totalTimeLabel;
    QLabel  * presentTimeLabel;


    QTimer *mediaTimer;

signals:
    void signalInRegion();
    void signalOutRegion();

public slots:
   void slotSetButton();
   void slotOpenFile();
   void slotSetValue(int value);
   void slotStateChanged(QMediaPlayer::State);
   void slotDurationChanged(qint64);
   void slotPositionChanged(qint64);
   void slotPlayOrPause();
   void slotNextVideo();
   void slotLastVideo();
   void slotStopVideo();
   void slotVolumeTimer();
   void slotPlayModeTimer();
   void slotPlayModeListWidget();
   void slotInBottomRegion();
   void slotOutBottomRegion();
   void slotOutBottomRegionTimer();
   void slotSignalPressPosition(qint64 position);
   void slotPressVolumePosition(qint64 position);
   void slotListWidgetItemDoubleClick(QString name);
   void slotListWidgetItemDeleted(int n);
   void slotSignalMovePoint(QPoint );
   void slotVideoWidgetMouseLeftDown(bool);
   void slotHandleError();
   void slotVideoWidgetDoubleClicked();
   void slotListWidgetClearAll();
   void slotListWidgetActionOpen();
   void slotHideButton();
   void slotInRightRegion();
   void slotOutRightRegion();
   void slotOutRightRegionTimer();
   void slotCloseWidget();
   void slotVideoWidgetDropedList(QList<QUrl>urls);
   void slotListWidgetClearValidItem();
   void slotListWidgetOpenDirectory(int n);
   void slotVideoWidgetActionInfo();

};



#endif // WIDGET_H
