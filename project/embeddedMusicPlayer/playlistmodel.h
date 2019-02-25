/**************************************************
 *playlistmodel.h
 *2013.7.31-2013.8.04
 *功能：
 *QP1301_
 **************************************************
 */

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractItemModel>

class QMediaPlaylist;

class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT




public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    PlaylistModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QMediaPlaylist *playlist() const;

    void setPlaylist(QMediaPlaylist *playlist);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);


private slots:
    void beginInsertItems(int start, int end);
    void endInsertItems();
    void beginRemoveItems(int start, int end);
    void endRemoveItems();
    void changeItems(int start, int end);

private:
    QMediaPlaylist *m_playlist;
    QMap<QModelIndex, QVariant> m_data;
};

#endif // PLAYLISTMODEL_H
