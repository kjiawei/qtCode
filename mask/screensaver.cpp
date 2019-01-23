#include "screensaver.h"
#include "ui_screensaver.h"

#include <QImage>
#include <QDebug>

ScreenSaver::ScreenSaver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);

    QImage *image = new QImage(":/ui_image/load.png");
    ui->label->setPixmap(QPixmap::fromImage(*image));
    //ui->label->setText("123");
}

ScreenSaver::~ScreenSaver()
{
    delete ui;
}

void ScreenSaver::keyPressEvent(QKeyEvent *e)
{
    this->hide();
    //((MainWindow*)this->parentWidget())->currentWidgetChanged(3);
    //((MainWindow*)this->parentWidget())->c
}
