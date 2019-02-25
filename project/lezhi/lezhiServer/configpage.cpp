#include "configpage.h"

ConfigPage::ConfigPage(QWidget *parent) : QWidget(parent)
{
    //通过代码设置UI  在界面无显示->setUi  不能同时打开多个页面
    backButton = new QPushButton();
    backButton->setText("返回主界面");
    backButton->setGeometry(QRect(50,100,20,40));
}

