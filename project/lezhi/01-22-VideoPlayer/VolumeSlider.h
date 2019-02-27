#ifndef SOUNDSLIDER_H
#define SOUNDSLIDER_H

#include<QSlider>
#include<QMouseEvent>
#include<QWidget>

class VolumeSlider : public QSlider
{
    Q_OBJECT
public:
    VolumeSlider(Qt::Orientation orientation, QWidget * parent);
    void mousePressEvent(QMouseEvent* event);
signals:
    void signalPressVolumePosition(qint64 position);
};

#endif // SOUNDSLIDER_H
