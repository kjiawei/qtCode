#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QMainWindow>

namespace Ui {
class friendlist;
}

class friendlist : public QMainWindow
{
    Q_OBJECT

public:
    explicit friendlist(QWidget *parent = 0);
    ~friendlist();

private:
    Ui::friendlist *ui;
};

#endif // FRIENDLIST_H
