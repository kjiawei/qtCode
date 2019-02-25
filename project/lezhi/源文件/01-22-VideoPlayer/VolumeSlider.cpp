#include "VolumeSlider.h"
#include<QSlider>
#include<QMouseEvent>
#include<QDebug>

VolumeSlider::VolumeSlider(Qt::Orientation orientation, QWidget* parent):QSlider(orientation, parent)
{
    this->setStyleSheet(" QSlider{background-color: rgb(25, 38, 58);border:0px solid rgb(25, 38, 58);}"
                                "QSlider::add-page:vertical{ background-color: rgb(37, 168, 198);width:4px;}"
                                "QSlider::sub-page:vertical {background-color: rgb(87, 97, 106);width:4px;}"
                                "QSlider::groove:vertical {background:transparent;width:4px; }"
                                "QSlider::handle:vertical { background-color:rgb(222,222,222); height: 10px; width:10px; margin:-1 -3px; border-radius:5px;}"   );

}

void VolumeSlider::mousePressEvent(QMouseEvent *event)
{
    qint64 mousePosY = (event->pos().y() );
    qint64 duration = this->maximum();
    qint64 height = this->size().height();

    //使其保持在一定范围内
    if(mousePosY < 0)
        mousePosY = 0;
    if(mousePosY > height)
        mousePosY = height;

    qint64 position = duration * (height-mousePosY) / height;
    emit signalPressVolumePosition(position);
    //qDebug()<<"mousePosY:   "<<mousePosY;
   // qDebug()<<"position:   "<<position;
}
