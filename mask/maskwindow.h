#ifndef MASKWINDOW_H
#define MASKWINDOW_H

#include <QMainWindow>

namespace Ui {
class MaskWindow;
}

class MaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MaskWindow(QWidget *parent = 0);
    ~MaskWindow();

private:
    Ui::MaskWindow *ui;
};

#endif // MASKWINDOW_H
