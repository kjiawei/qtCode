#ifndef BUTTONSTACKEDWIDGET_H
#define BUTTONSTACKEDWIDGET_H

#include <QObject>
#include <QWidget>
#include"baseWidget.h"
#include"myPushButton.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QStackedWidget>
class buttonStackedWidget:public baseWidget
{
    Q_OBJECT
public:
    buttonStackedWidget(QWidget*parent=0);
    void addPushButton(const QString& name);
    void init();
    void showLayout();
    QStackedWidget *m_stackwid;
protected:
    void paintEvent(QPaintEvent*);
private slots:
    void buttonClicked();
    void curWidIndexChange(int);
private:
    QVector<myPushButton*> m_btnList;
    QHBoxLayout *m_hlyout;
    QVBoxLayout *m_vlyout;
};

#endif // BUTTONSTACKEDWIDGET_H
