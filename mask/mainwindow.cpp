#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gammaramp.h"
#include "screensaver.h"
#include "globalvar.h"

#include <QLabel>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>

#define CLEARSCREEN_TIME 31

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isCleanScreen = false;
    isScreenSaveUse = false;//默认不启用屏幕保护程序
    isSystemColdTime = true;
    isAutoWokeMode = true;//系统默认自动工作模式
    isDayWokeMode = false;
    isNightWokeMode = false;

    isNursePolicy = false;//护士级别P1 跳转工程模式函数中激活
    isSalesPolicy = true;//维护工程师级别P2
    isEngineerPolicy = false;//内部工程师级别P3
    isFactoryPolicy = false;//工厂配置级别P4

    //翻页按钮
    pageContainer = new QButtonGroup(this);
    switchPageOne = new QRadioButton(tr("pageOne"),this);//
    switchPageTwo = new QRadioButton(tr("pageTwo"),this);
    switchPageThree = new QRadioButton(tr("pageThree"),this);
    pageContainer->addButton(switchPageOne,1);
    pageContainer->addButton(switchPageTwo,2);
    pageContainer->addButton(switchPageThree,3);
    switchPageOne->setChecked(true);
    switchPageOne->setGeometry(QRect(100,500,80,40));
    switchPageTwo->setGeometry(QRect(200,500,80,40));
    switchPageThree->setGeometry(QRect(300,500,80,40));/**/
    //switchPageOne->setText("pageOne");
    //switchPageOne->setText(tr("Rinse"));
    //switchPageTwo.setGeometry(QRect(100,500,150,200));

    /*按钮组布局管理
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(switchPageOne);
    mainLayout->addWidget(switchPageTwo);
    mainLayout->addWidget(switchPageThree);
    mainLayout->addStretch();
    setLayout(mainLayout);*/

    initWidgetState();

    a = 31;//清洁屏幕倒计时
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(showCountTime()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(screenHandOn()));
    QObject::connect(ui->coldSpinBox,SIGNAL(valueChanged(int)),ui->coldSlider,SLOT(setValue(int)));
    QObject::connect(ui->coldSlider,SIGNAL(valueChanged(int)),ui->coldSpinBox,SLOT(setValue(int)));
    countTimeLabel = new QLabel(this);//动态冻屏倒计时提示标签
    countTimeLabel->setText(" ");
    countTimeLabel->setGeometry(/*parent->width()/2,parent->height()/2*/100,100,100,100);

    //屏幕亮度 spinbox和slider数据同步 spinbox值传到onspinvaluechanged
    QObject::connect(ui->screenLightSpinBox,SIGNAL(valueChanged(int)),ui->screenLightSlider,SLOT(setValue(int)));
    QObject::connect(ui->screenLightSlider,SIGNAL(valueChanged(int)),ui->screenLightSpinBox,SLOT(setValue(int)));
    QObject::connect(ui->screenLightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinValueChanged(int)));

    //屏幕保护
    screenSaveTimeWidget = new ScreenSaver(this);
    screenSaveTimeWidget->hide();
    connect(&saveTime,SIGNAL(timeout()),this,SLOT(screenSaveTimeOutSlot()));
    //采用治疗画面
    QObject::connect(ui->cureTimeSpinBox,SIGNAL(valueChanged(int)),ui->cureTimeSlider,SLOT(setValue(int)));
    QObject::connect(ui->cureTimeSlider,SIGNAL(valueChanged(int)),ui->cureTimeSpinBox,SLOT(setValue(int)));
    //采用系统时长
    QObject::connect(ui->savTimeSpinBox,SIGNAL(valueChanged(int)),ui->savTimeSlider,SLOT(setValue(int)));
    QObject::connect(ui->savTimeSlider,SIGNAL(valueChanged(int)),ui->savTimeSpinBox,SLOT(setValue(int)));

    //音量调节
    QObject::connect(ui->systemVoiceSpinBox,SIGNAL(valueChanged(int)),ui->systemVoiceSlider,SLOT(setValue(int)));
    QObject::connect(ui->systemVoiceSlider,SIGNAL(valueChanged(int)),ui->systemVoiceSpinBox,SLOT(setValue(int)));
    QObject::connect(ui->alarmVoiceSpinBox,SIGNAL(valueChanged(int)),ui->alarmVoiceSlider,SLOT(setValue(int)));
    QObject::connect(ui->alarmVoiceSlider,SIGNAL(valueChanged(int)),ui->alarmVoiceSpinBox,SLOT(setValue(int)));

    //页面跳转
    //connect(pageContainer, SIGNAL(buttonToggled(int,bool)), this, SLOT(pageContainerToggled(int,bool)));
    //connect(pageContainer, SIGNAL(buttonClicked(int)), this, SLOT(pageContainerClicked(int)));
    connect(switchPageOne, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(switchPageTwo, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(switchPageThree, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
}

void MainWindow::radioChange(void){
    if(sender() == switchPageOne)
    {

        ui->label_10->setText(tr("1"));
    }
    else if(sender() == switchPageTwo)
    {
        ui->label_10->setText(tr("2"));
    }
    else if(sender() == switchPageThree)
    {
        ui->label_10->setText(tr("3"));
    }
    //qDebug()<<"4";
    //qDebug("1");
}

void MainWindow::pageContainerToggled(int id,bool status)
{
    int tmp = pageContainer->checkedId();
    QString str = pageContainer->checkedButton()->text();
    QByteArray byteArray = str.toLocal8Bit();
    qDebug("flag = %d, status = %d, tmp = %d, checked = %s", id, status, tmp, byteArray.data());
}

void MainWindow::pageContainerClicked(int id)
{
    qDebug("Clicked: %d", id);
}

//按键启动屏保事件  第一次触发屏保需要按键  再次按键取消屏保 并在设定的间隔值自动启动屏保
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        saveTime.start(scrSavTime * 1000);
    }
    return QObject::eventFilter(obj, event);
}

//初始化控件状态
void MainWindow::initWidgetState()
{
    //冻屏控件组
    ui->coldSlider->setRange(10,300);
    ui->coldSpinBox->setRange(10,300);
    ui->coldSlider->setValue(30);//初值,与系统默认相等
    ui->coldSpinBox->setValue(30);
    ui->coldSlider->setDisabled(true);//取消系统默认值才能调节
    ui->coldSpinBox->setDisabled(true);

    //屏幕亮度
    ui->screenLightSlider->setRange(0, 255);
    ui->screenLightSpinBox->setRange(0, 255);
    ui->screenLightSlider->setValue(128);
    ui->screenLightSpinBox->setValue(128);

    //屏幕保护 2分钟~30分钟 60~1800未解决
    ui->savTimeSlider->setRange(0, 300);
    ui->savTimeSpinBox->setRange(0, 300);
    ui->cureTimeSlider->setRange(0, 300);
    ui->cureTimeSpinBox->setRange(0, 300);
    ui->savTimeSlider->setValue(60);
    ui->savTimeSpinBox->setValue(60);
    ui->cureTimeSpinBox->setValue(80);
    ui->cureTimeSlider->setValue(80);
    ui->savTimeSlider->setDisabled(true);
    ui->savTimeSpinBox->setDisabled(true);
    ui->cureTimeSlider->setDisabled(true);
    ui->cureTimeSpinBox->setDisabled(true);

    //工作模式
    ui->dayModeCheckBox->setDisabled(true);
    ui->nightModeCheckBox->setDisabled(true);

    //音量调节
    ui->systemVoiceSlider->setRange(0, 255);
    ui->systemVoiceSpinBox->setRange(0, 255);
    ui->alarmVoiceSlider->setRange(0, 255);
    ui->alarmVoiceSpinBox->setRange(0, 255);
    ui->systemVoiceSlider->setValue(30);
    ui->alarmVoiceSlider->setValue(50);
    ui->systemVoiceSlider->setDisabled(true);
    ui->systemVoiceSpinBox->setDisabled(true);
    ui->alarmVoiceSlider->setDisabled(true);
    ui->alarmVoiceSpinBox->setDisabled(true);

    //密码设置区
    ui->P1_lineEdit->setPlaceholderText("******");//新旧密码
    ui->P1_lineEdit->setEnabled(false);
    ui->P1_lineEdit_2->setPlaceholderText("******");
    ui->P1_lineEdit_2->setEnabled(false);
    ui->P2_lineEdit->setPlaceholderText("******");
    ui->P2_lineEdit->setEnabled(false);
    ui->P2_lineEdit_2->setPlaceholderText("******");
    ui->P2_lineEdit_2 ->setEnabled(false);
    ui->P3_lineEdit->setPlaceholderText("******");
    ui->P3_lineEdit->setEnabled(false);
    ui->P3_lineEdit_2->setPlaceholderText("******");
    ui->P3_lineEdit_2->setEnabled(false);
    ui->P4_lineEdit->setPlaceholderText("******");
    ui->P4_lineEdit->setEnabled(false);
    ui->P4_lineEdit_2->setPlaceholderText("******");
    ui->P4_lineEdit_2->setEnabled(false);

    if (isNursePolicy == true){
        ui->P1_lineEdit->setPlaceholderText("请输入原密码");
        ui->P1_lineEdit->setEnabled(true);
        ui->P1_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P1_lineEdit_2->setEnabled(true);
    }else if(isSalesPolicy == true){
        ui->P1_lineEdit->setPlaceholderText("请输入原密码");
        ui->P1_lineEdit->setEnabled(true);
        ui->P1_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P1_lineEdit_2->setEnabled(true);
        ui->P2_lineEdit->setPlaceholderText("请输入原密码");
        ui->P2_lineEdit->setEnabled(true);
        ui->P2_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P2_lineEdit_2->setEnabled(true);
    }else if(isEngineerPolicy == true){
        ui->P1_lineEdit->setPlaceholderText("请输入原密码");
        ui->P1_lineEdit->setEnabled(true);
        ui->P1_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P1_lineEdit_2->setEnabled(true);
        ui->P2_lineEdit->setPlaceholderText("请输入原密码");
        ui->P2_lineEdit->setEnabled(true);
        ui->P2_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P2_lineEdit_2->setEnabled(true);
        ui->P3_lineEdit->setPlaceholderText("请输入原密码");
        ui->P3_lineEdit->setEnabled(true);
        ui->P3_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P3_lineEdit_2->setEnabled(true);
    }else if(isFactoryPolicy == true){
        ui->P1_lineEdit->setPlaceholderText("请输入原密码");
        ui->P1_lineEdit->setEnabled(true);
        ui->P1_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P1_lineEdit_2->setEnabled(true);
        ui->P2_lineEdit->setPlaceholderText("请输入原密码");
        ui->P2_lineEdit->setEnabled(true);
        ui->P2_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P2_lineEdit_2->setEnabled(true);
        ui->P3_lineEdit->setPlaceholderText("请输入原密码");
        ui->P3_lineEdit->setEnabled(true);
        ui->P3_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P3_lineEdit_2->setEnabled(true);
        ui->P4_lineEdit->setPlaceholderText("请输入原密码");
        ui->P4_lineEdit->setEnabled(true);
        ui->P4_lineEdit_2->setPlaceholderText("请输入新密码");
        ui->P4_lineEdit_2->setEnabled(true);
    }

    //消毒参数表格
    //QStringList header;
    //header<<"Month"<<"Description";
    /*ui->disinfectTableWidget->setHorizontalHeaderLabels(header);
    ui->disinfectTableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
    ui->disinfectTableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
    ui->disinfectTableWidget->setItem(2,0,new QTableWidgetItem("Mar"));*/
    QTableWidget *tableWidget = new QTableWidget(100,8);
    tableWidget->setWindowTitle("消毒参数");
    tableWidget->resize(780, 380);  //设置表格
    QStringList header;
    header<<"清洁类型"<<"参数"<<"默认值"<<"最大值"<<"最小值"<<"单位"<<""<<"权限";
    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->setItem(0,0,new QTableWidgetItem("冷冲洗"));
    tableWidget->setItem(1,0,new QTableWidgetItem(""));
    tableWidget->setSpan(0,0,2,1);//合并第一列的一二行
    /*tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));
        tableWidget->setItem(2,0,new QTableWidgetItem("Mar2"));
        tableWidget->setItem(2,0,new QTableWidgetItem("Mar3"));*/
    //tableWidget->show();
}

//屏保处理
void MainWindow::screenSaveTimeOutSlot()
{
    screenSaveTimeWidget->show();
    screenSaveTimeWidget->grabKeyboard();
}

//获取设置的屏幕亮度值
void MainWindow::onSpinValueChanged(int i)
{
    int gamma = i;
    CGammaRamp GammaRamp;
    GammaRamp.SetBrightness(NULL, gamma);
}

//冻结屏幕操作
void MainWindow::screenHandOn()
{
    if(isSystemColdTime == true)
        a = CLEARSCREEN_TIME;
    else
        a = int(ui->coldSpinBox->value()) + 1;
    w2.show();
    timer->start();
}

//显示冻屏倒计时
void MainWindow::showCountTime()
{
    if ( a == 0)
    {
        countTimeLabel->setText(" ");
        w2.hide();
    }else if ( a != 0){
        a -= 1;
        QString num = QString::number(a);
        countTimeLabel->setText("清洁倒计时:"+num+"秒");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//屏幕保护启用按钮
void MainWindow::on_startScreenSaveCheckBox_clicked()
{
    isScreenSaveUse = !isScreenSaveUse;
    if(ui->startScreenSaveCheckBox->isChecked()==false){
        ui->savTimeSlider->setDisabled(true);
        ui->savTimeSpinBox->setDisabled(true);
        ui->cureTimeSlider->setDisabled(true);
        ui->cureTimeSpinBox->setDisabled(true);
    }else{
        ui->savTimeSlider->setDisabled(false);
        ui->savTimeSpinBox->setDisabled(false);
        ui->cureTimeSlider->setDisabled(false);
        ui->cureTimeSpinBox->setDisabled(false);
    }
}

//白天模式
void MainWindow::on_dayModeCheckBox_clicked()
{
    isDayWokeMode = !isDayWokeMode;
    if(ui->dayModeCheckBox->isChecked() == true)
    {
        ui->workModeCheckBox->setDisabled(true);
        ui->nightModeCheckBox->setDisabled(true);
    }else{
        ui->workModeCheckBox->setDisabled(false);
        ui->nightModeCheckBox->setDisabled(false);
    }
}

//夜晚模式
void MainWindow::on_nightModeCheckBox_clicked()
{
    isNightWokeMode = !isNightWokeMode;
    if(ui->nightModeCheckBox->isChecked() == true)
    {
        ui->workModeCheckBox->setDisabled(true);
        ui->dayModeCheckBox->setDisabled(true);
    }else{
        ui->dayModeCheckBox->setDisabled(false);
        ui->workModeCheckBox->setDisabled(false);
    }
}

//自动工作模式
void MainWindow::on_workModeCheckBox_clicked()
{
    isAutoWokeMode = !isAutoWokeMode;
    if(ui->workModeCheckBox->isChecked() == false)
    {
        ui->dayModeCheckBox->setDisabled(false);
        ui->nightModeCheckBox->setDisabled(false);
    }else{
        ui->dayModeCheckBox->setDisabled(true);
        ui->nightModeCheckBox->setDisabled(true);
    }
}

//启用系统冻屏时间
void MainWindow::on_useSysColdTimeCheckBox_clicked()
{
    isSystemColdTime = !isSystemColdTime;
    if(isSystemColdTime == false)
    {
        ui->coldSlider->setDisabled(false);
        ui->coldSpinBox->setDisabled(false);
    }else{
        ui->coldSlider->setDisabled(true);
        ui->coldSpinBox->setDisabled(true);
    }
}

//恢复默认亮度
void MainWindow::on_returnDefLight_clicked()
{
    ui->screenLightSlider->setValue(128);
    ui->screenLightSlider->setValue(128);
    CGammaRamp GammaRamp;
    GammaRamp.SetBrightness(NULL, 128);
}

//密码修改提交  采用槽函数方法可能会好点-修改控件状态触发相应事件
void MainWindow::on_submitChange_clicked()
{
    //if(ui->ui->P1_lineEdit.value() != "OLD_PASSWORD"){
    //QToast("密码不对,请重新输入")
    //}else
    //new_password = P1_lineEdit.value() //保存到数据库或配置文件
}
