#ifndef CALCQT_H
#define CALCQT_H

#include <QMainWindow>
#include <QButtonGroup>

namespace Ui {
class CalcQt;
}

class CalcQt : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcQt(QWidget *parent = 0);
    ~CalcQt();

private slots:
    void on_calcBt_clicked();
    void on_subBt_clicked();
    void on_changBt_clicked();
    void button_num(int i);
private:
    Ui::CalcQt *ui;
    QButtonGroup *group;
};

#endif // CALCQT_H
