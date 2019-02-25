/*********************************************
 *musicList.h
 *功能：
 *2013.7.31-2013.8.04
 *QP1301_
 *********************************************
 */

#ifndef MUSICLIST_H
#define MUSICLIST_H

#include "playlistmodel.h"
#include <QWidget>
#include <QListWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QtWidgets>
#include <QMediaPlaylist>
#include <QStackedWidget>
#include <QAbstractItemModel>
#include <QDesktopWidget>

class MusicList : public QWidget
{
    Q_OBJECT
public:
    PlaylistModel *listModel_0;
    PlaylistModel *listModel_1;

    QListWidget *list_widget;
    QListView *list_0;
    QListView *list_1;

    QDesktopWidget *desk;

    explicit MusicList(QWidget *parent = 0);
    void setPlayList_0(QMediaPlaylist *playlist);
    void setPlayList_1(QMediaPlaylist *playlist);

public slots:
    void show_hide();
    void list_0_current_index(QModelIndex index);
    void list_1_current_index(QModelIndex index);
    void remove_inedx();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);

signals:
    void playlistClean();
    void addMedia();
    void List_0_IndexChange(int);
    void list_1_IndexChange(int);
    void remove_sign();

private slots:
    void addMediaPlay();
    void clearPlaylist();

private:

};

#endif // MUSICLIST_H
