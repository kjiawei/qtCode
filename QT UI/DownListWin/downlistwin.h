#ifndef DOWNLISTWIN_H
#define DOWNLISTWIN_H

#include <QMainWindow>

namespace Ui {
class DownListWin;
}

class DownListWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit DownListWin(QWidget *parent = 0);
    ~DownListWin();

private slots:
    void on_adddownloadBt_clicked();

private:
    Ui::DownListWin *ui;
};

#endif // DOWNLISTWIN_H
