/*
* Name: mainwidget.h
*
* Version: 1.0
*
* Created by: FriendlyARM
*
* Purpose:  MPlayer Demo's main window
*/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QProcess>
#include <QTimer>
#include <QIcon>

namespace Ui {
    class MainWidget;
}

/*
 * MainWidget
 * Purpose: Main window
 */
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    enum {
        TVMODE_OFF = 0,
        TVMODE_TVONLY,
        TVMODE_TVANDLCD,
        TVMODE_MAX,
    };

private slots:
    void catchOutput();
    void mplayerEnded(int exitCode, QProcess::ExitStatus exitStatus);
    void on_m_openButton_clicked();
    void on_m_playButton_clicked();
    void on_m_stopButton_clicked();
    void on_m_tvButton_clicked();
    void on_m_exitButton_clicked();
    void getTimepos();

    void on_m_slider_sliderMoved(int position);

    void on_m_slider_sliderPressed();

    void on_m_slider_sliderReleased();

protected:
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent* e);
    void closeEvent(QCloseEvent *e);

private:
    // launch MPlayer to play video
    bool startMPlayer(int pos = 0);
    // stop playing playing
    bool stopMPlayer();
    bool pauseMPlayer();

    QString m_movieFile;
    QRect m_videoWindowRect;
    Ui::MainWidget *ui;

    QPixmap m_logoPixmap;
    QPixmap m_tvoutModePixmap0;
    QPixmap m_tvoutModePixmap;

    QTimer* m_timeTimer;
    QProcess *m_mplayerProcess;
    bool m_isPlaying;
    bool m_isPause;
    int m_tvoutMode;

    QIcon m_playIcon;
    QIcon m_pauseIcon;
};

#endif // MAINWIDGET_H
