#ifndef QQLIST_H
#define QQLIST_H

#include <QMainWindow>
#include <QList>

namespace Ui {
class QQList;
}

class QQList : public QMainWindow
{
    Q_OBJECT

public:
    explicit QQList(QWidget *parent = 0);
    ~QQList();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QQList *ui;
    //qq列表数据
    QStringList friendlist;
    QStringList strangerlist;
    QStringList blacklist;
};

#endif // QQLIST_H
