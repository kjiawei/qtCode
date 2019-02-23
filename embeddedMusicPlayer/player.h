/***********************************
 *player.h
 *功能：播放器主界面
 *2013.7.31-2013.8.04
 *QP1301_
 ***********************************
 */


#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QtGui>
#include <QMovie>
#include <QMediaPlayer>

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QMediaMetaData>

#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QtWidgets>
#include <qvideowidget.h>


#include "musiclist.h"
#include "mylrc.h"

class player : public QWidget
{
    Q_OBJECT
public:
    enum ListCopy
    {
        List1_No_Copy,
        List1_Yes_Copy,
        List2_No_Copy,
        List2_Yes_Copy
    };

    QMap<qint64,QString> lrcmap;//
    QString sourcename;//
    qint64 Masktime;//
    Mylrc  *lrc;
    int show_lrc;

    explicit player();
    void CopyPlaylist(QMediaPlaylist *dest, QMediaPlaylist *src);
    void resolvelrc();//

public slots:
    void open();
    void play();
    void title();

    void createActions();
    void createTrayIcon();

    void music_write();//
    void music_read();//

    
signals:


protected:
    void closeEvent(QCloseEvent *);

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void updateDurationInfo(qint64 currentInfo);
    void setPosition(int position);
    void muteClicked();
    void playlistPositionChanged(int currentItem);
    void setCurrentList(int currentList);
    void jump(const QModelIndex &index);
    void clearPlayList();
    void setList_0_index(int index);
    void setList_1_index(int index);
    void remove_index();
    void showlrc(void);//

    void quite();

private:
    QMediaPlaylist *addlist;
    QMediaPlaylist *playlist;
    QMediaPlaylist *playlist_0;
    QMediaPlaylist *playlist_1;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;

    QPushButton *stopButton;
    QPushButton *playButton;
    QPushButton *backButton;
    QPushButton *nextButton;

    QPushButton *muteButton;
    QSlider *volumeSlider;

    QLabel *messLabel;
    QPushButton *openButton;
    QPushButton *listButton;
    QPushButton *lrcButton;

    QLabel *topLabel;
    QSlider *positionSlider;
    QLabel *timeLabel;

    bool playerMuted;
    int volume;
    qint64 duration;

    MusicList *list;
    int current_list;
    int copy_list;
    int list_0_index_music;
    int list_1_index_music;

    QSystemTrayIcon *trayIcon;
    QAction *showAction;
    QAction *quitAction;

    QAction *nextAction;
    QAction *backAction;
    QAction *playAction;

    QMenu *trayIconMenu;

    QIcon *iconplay;
    QIcon *iconpause;

};

#endif // PLAYER_H
