#include "cutscreen.h"
#include "ui_cutscreen.h"
#include <QScreen>
#include <QPixmap>
#include "screenthread.h"
CutScreen::CutScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CutScreen)
{
    ui->setupUi(this);
}

CutScreen::~CutScreen()
{
    delete ui;
}

void CutScreen::on_cutBt_clicked()
{
    //截屏
    QPixmap pixmap = QApplication::screens().at(0)->grabWindow(0,0,0,400,400);
    //保存截屏
    //pixmap.save("./screen.jpg");
    pixmap = pixmap.scaled(ui->label->size());
    ui->label->setPixmap(pixmap);

    //创建线程
    ScreenThread *thread = new ScreenThread();
    thread->set_screen_show(ui->label,&mutex);
    //启动线程
    thread->start();
}
