#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <weatherlabel.h>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setJinjiText(QString str);//获取服务器发送的紧急消息设置到widget显示出来
protected:
//    void paintEvent(QPaintEvent *event);
//    void updateIndex();
private:
    Ui::MainWindow *ui;
    QTimer *timer;//更新时间 图片 消息
    QTimer *timerNews;//更新消息
    QTimer *werTimer;//触发天气更新

    QString jinjiNews;
    int newsWidth;//每个字符宽度
    int newsCurIndex;//角码

    int i;//天气更新
    int day;
    QTcpSocket *socket,*dmSocket;//前面为发送调试信息的socket
    QProcess *process;//播放视频的进程

    QNetworkAccessManager *manager;//http客户端管理对象
    QNetworkAccessManager *versionManager;//版本管理
    QNetworkAccessManager *requestWeatherManager;//请求第三方天气数据

    weatherLabel *weaLabel,*weaLabel2,*weaLabel3;
    //weatherLabel *weaLabel[3];//测试的第一个天气label
    QList<_Weather> weatherList;//用于存放天气数据
private slots:
    void timerTime();//时间
    void wertherUpdate();//更新天气显示
    void read_data();//读取服务端发送来的紧急信息
    void read_dmData();//弹幕信息
    void read_appUpdate(QNetworkReply*);//监测版本更新
    void read_wertherData(QNetworkReply* reply);//读取本地服务器上天气数据
};

#endif // MAINWINDOW_H
