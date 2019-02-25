#include "MainSlider.h"
#include<QWidget>
#include<QSlider>
#include<QDebug>
#include<QCursor>

MainSlider::MainSlider(Qt::Orientation orientation, QWidget* parent):QSlider(orientation, parent)
{
    this->setTracking(true);
    //this->setPageStep(15);
  //  connect(this, SIGNAL(sliderPressed()), this, SLOT(slotSliderPressed()));

    this->setCursor(QCursor(Qt::PointingHandCursor	));
//
    this->setStyleSheet("QSlider{background-color:rgb(0,0,0)}"
                                      "QSlider::add-page:horizontal{   background-color: rgb(87, 97, 106);  height:4px; }"
                                    "QSlider::sub-page:horizontal {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));"
                                                 "height:4px;}"

                                       "QSlider::add-page:hover:horizontal{   background-color: rgb(87, 97, 106);  height:6px; }"
                                        "QSlider::sub-page:hover:horizontal {background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));"
                                                                         "height:6px;}"

                                    "QSlider::handle:horizontal {margin-top:-2px; margin-bottom:-2px;"
                                                         "border-radius:4px;  background: rgb(222,222,222); width:14px; height:18px;}"


                                    "QSlider::groove:horizontal {background:transparent;height:4px}"
                                    "QSlider::groove:hover:horizontal {background:transparent;height:6px}"

   );



}

void MainSlider::mouseMoveEvent(QMouseEvent *event)
{

}

void MainSlider::mousePressEvent(QMouseEvent *event)
{
    qint64 mousePosX = event->pos().x();
    qint64 duration = this->maximum();
    qint64 width = this->size().width();

    //使其保持在一定范围内
    if(mousePosX < 0)
        mousePosX = 0;
    if(mousePosX > width)
        mousePosX = width;

    qint64 position = duration * mousePosX / width;
    //qDebug()<<"position:  "<<position;
    //this->setValue(position);
    emit signalPressPosition(position);
}


