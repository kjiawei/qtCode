#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

//项目控制页-QT creator创建的类,用以学习继承关系

#include <QWidget>
#include <QPushButton>

#include "view/globalwidget.h"
#include "view/componentwidget.h"
#include "model/globaldata.h"

class ConfigPage : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPage(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *backButton;//返回上级界面
};

#endif // CONFIGPAGE_H
