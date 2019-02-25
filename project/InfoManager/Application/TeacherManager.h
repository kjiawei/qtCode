#ifndef TEACHERMANAGERWIDGET_H
#define TEACHERMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class TeacherManager;
}

class TeacherManager : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherManager(QWidget *parent = 0);
    ~TeacherManager();

private:
    Ui::TeacherManager *ui;
};

#endif // TEACHERMANAGERWIDGET_H
