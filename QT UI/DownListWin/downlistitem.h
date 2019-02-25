#ifndef DOWNLISTITEM_H
#define DOWNLISTITEM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class DownListItem;
}

class DownListItem : public QWidget
{
    Q_OBJECT

public:
    explicit DownListItem(QWidget *parent = 0);
    ~DownListItem();

    void set_movie_name(QString name);
    void set_movie_size(double size);
    void set_down_size(int size);
private slots:
    void update_progress();
    void on_selectCb_clicked(bool checked);

private:
    Ui::DownListItem *ui;
    double moviesize;
    QString moviename;
    int downsize;
    QTimer *mtimer;
};

#endif // DOWNLISTITEM_H
