#include "weatherlabel.h"
#include "ui_weatherlabel.h"

weatherLabel::weatherLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weatherLabel)
{
    ui->setupUi(this);
}

weatherLabel::~weatherLabel()
{
    delete ui;
}

void weatherLabel::setWeather(const _Weather &weather)
{
    ui->riqi->setText(weather.riqi);
    ui->jibie->setText(weather.fengli);
    ui->fx->setText(weather.fx);
    ui->gaowen->setText(weather.gaowen);
    ui->diwen->setText(weather.diwen);
    ui->tianqiLabel->setText(weather.tianqi);
}
