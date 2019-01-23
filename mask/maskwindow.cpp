#include "maskwindow.h"
#include "ui_maskwindow.h"

MaskWindow::MaskWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaskWindow)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.5);
}

MaskWindow::~MaskWindow()
{
    delete ui;
}
