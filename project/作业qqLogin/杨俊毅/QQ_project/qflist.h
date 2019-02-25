#ifndef QFLIST_H
#define QFLIST_H

#include <QMainWindow>

namespace Ui {
class QFlist;
}

class QFlist : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFlist(QWidget *parent = 0);
    ~QFlist();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::QFlist *ui;
    QStringList friendlist;
    QStringList strangerlist;
    QStringList blacklist;
};

#endif // QFLIST_H
