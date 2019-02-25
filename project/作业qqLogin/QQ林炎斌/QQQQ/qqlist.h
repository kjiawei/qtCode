#ifndef QQLIST_H
#define QQLIST_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QMouseEvent>
namespace Ui {
class QQList;
}

class QQList : public QMainWindow
{
    Q_OBJECT

public:
    explicit QQList(QWidget *parent = 0);
    IMClickLabel(QWidget *parent);

    ~QQList();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::QQList *ui;
    //qq列表
    QStringList friendlist;
    QStringList strangerlist;
    QStringList blacklist;
};

#endif // QQLIST_H
