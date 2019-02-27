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
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow//public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setJinjiText(QString str);//获取服务器发送的紧急消息设置到widget显示出来
    void initView();
    void initParams();
    void saveToFile();

public slots:
    bool eventFilter(QObject *, QEvent *);

protected:
    //    void paintEvent(QPaintEvent *event);
    //    void updateIndex();

private:
    int newsWidth;//每个字符宽度
    int newsCurIndex;//角码
    int wkDay_num;//天气更新

    int videoIsPlaying;//0end/noPlaying 1playing 2pause
    bool voiceMute;//静音
    int tmpVoiceVolume;//音量调节

    QString video_full, video_name, video_path,player_full, player_name, player_path;
    QFileInfo videoInfo,playerInfo;

    int Flag_isOpen;
    //QFile txt_file;
    QString Last_FileName;

    QString videoCurrentTime;

    Ui::MainWindow *ui;
    QTimer *playerTimer;//视频播放定时器 获取进度信息等
    QTimer *timer;//更新时间 图片 消息
    QTimer *timerNews;//更新消息
    QTimer *weatherTimer;//触发天气更新
    QString jinjiNews;
    QTcpSocket *socket,*dmSocket;//前面为发送调试信息的socket
    QProcess *pVideoProcess;//播放视频的进程
    QNetworkAccessManager *manager;//http客户端管理对象
    QNetworkAccessManager *versionManager;//版本管理
    QNetworkAccessManager *requestWeatherManager;//请求第三方天气数据
    weatherLabel *weaLabel,*weaLabel2,*weaLabel3;
    QList<_Weather> weatherList;//用于存放天气数据

signals:
    void readyReadStandardOutput();

private slots:
    void timerTime();//时间
    void playerTime();
    void weatherUpdate();//更新天气显示
    void read_data();//读取服务端发送来的紧急信息
    void read_dmData();//弹幕信息
    void read_appUpdate(QNetworkReply*);//监测版本更新
    void read_wertherData(QNetworkReply* reply);//读取本地服务器上天气数据
    void back_message_slots();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
};

#endif // MAINWINDOW_H
