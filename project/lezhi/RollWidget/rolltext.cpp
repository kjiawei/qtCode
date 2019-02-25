#include "rolltext.h"
#include <QDebug>

RollText::RollText(QWidget *parent) :
    QWidget(parent)
{
    offset = 0;
    myTimerId = 0;
}

RollText::~RollText()
{

}


void RollText::setText(const QString &newText)

{
     myText = newText;
     update();
     updateGeometry();
}


QSize RollText::sizeHint() const
{
     return fontMetrics().size(0, text());
}


void RollText::paintEvent(QPaintEvent * )
{
     QPainter painter(this);
     int textWidth = fontMetrics().width(text());
     if (textWidth < 1)
         return;
     int x = offset;
     int clong = (width()-textWidth)-x;
     painter.drawText(clong, 0, width(), height(),
                     Qt::AlignLeft | Qt::AlignVCenter, text());
     if(clong<0)
     {
         painter.drawText(width()+clong, 0, width(), height(),
                         Qt::AlignLeft | Qt::AlignVCenter, text());
     }
     x += textWidth;
}


void RollText::showEvent(QShowEvent * )
{
     myTimerId = startTimer(30);
}

void RollText::timerEvent(QTimerEvent *event)
{
     if (event->timerId() == myTimerId) {
         ++offset;
//         if (offset >= fontMetrics().width(text()))
//             offset = 0;
         if (offset >= width())
             offset = 0;
         scroll(-1, 0);
     } else {
         QWidget::timerEvent(event);
     }
}


void RollText::hideEvent(QHideEvent * )
{
     killTimer(myTimerId);
     myTimerId = 0;
}


