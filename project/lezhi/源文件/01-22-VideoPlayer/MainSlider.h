#ifndef SLIDER_H
#define SLIDER_H

#include<QSlider>
#include<QMouseEvent>
#include<QEvent>

class MainSlider : public QSlider
{
    Q_OBJECT
public:
    explicit MainSlider(Qt::Orientation orientation, QWidget* parent =0);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent * event);
signals:
    void signalPressPosition(qint64 position);

public slots:

};

#endif // SLIDER_H
