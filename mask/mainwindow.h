#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//6068原型设计
//一键切换白天/黑夜模式  出厂设置-启动 延时  动效
//屏幕保护程序:无任何操作30分钟自动进入(工程模式可设置) 治疗模式下无操作5分钟-显示治疗中,有个治疗剩余时间logo移动
//

#include <QMainWindow>
#include <windows.h>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QWidget>

#include "globalvar.h"
#include "maskwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    typedef enum {
            ONE,
            TWO,
            THREE
        }page;

private:
    Ui::MainWindow *ui;

    int a;
    QTimer *timer;
    QLabel *countTimeLabel;
    //QPushButton *clearScreen;
    MaskWindow w2;
    QTimer saveTime;//屏保定时器
    QWidget *screenSaveTimeWidget = Q_NULLPTR;
    QButtonGroup *pageContainer;
    QRadioButton *switchPageOne;
    QRadioButton *switchPageTwo;
    QRadioButton *switchPageThree;
/*#ifdef VAR_GLOBALS
    #define scrSavTime_EXT
#else
    #define scrSavTime_EXT extern
#endif
    scrSavTime_EXT unsigned int Ctr;*/

protected:
    bool eventFilter(QObject *, QEvent *);//按键事件 有按键即触发

public slots:
    void screenHandOn();
    void showCountTime();
    void onSpinValueChanged(int i);//定义接收的槽函数
    void screenSaveTimeOutSlot();
    void initWidgetState();//设置页面控件初始状态

private slots:

    void on_startScreenSaveCheckBox_clicked();

    void on_dayModeCheckBox_clicked();

    void on_nightModeCheckBox_clicked();

    void on_workModeCheckBox_clicked();

    void on_useSysColdTimeCheckBox_clicked();

    void on_returnDefLight_clicked();

    void on_submitChange_clicked();

    void pageContainerToggled(int,bool);
    void pageContainerClicked(int);
    void radioChange(void);

private:
    bool isCleanScreen;//冻屏状态
    bool isSystemColdTime;//冻屏才有系统时间
    bool isScreenSaveUse;//是否启用屏幕保护程序
    bool isAutoWokeMode;//是否自动工作模式
    bool isDayWokeMode;//是否白天工作模式
    bool isNightWokeMode;//是否夜晚工作模式

    bool isNursePolicy;//护士/医生级别P1
    bool isSalesPolicy;//维护工程师级别P2
    bool isEngineerPolicy;//内部工程师级别P3
    bool isFactoryPolicy;//工厂配置级别P4


};

#endif // MAINWINDOW_H
