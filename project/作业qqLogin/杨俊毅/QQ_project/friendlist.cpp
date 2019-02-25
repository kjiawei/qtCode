#include "friendlist.h"
#include "ui_friendlist.h"

friendlist::friendlist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::friendlist)
{
    ui->setupUi(this);
}

friendlist::~friendlist()
{
    delete ui;
}
