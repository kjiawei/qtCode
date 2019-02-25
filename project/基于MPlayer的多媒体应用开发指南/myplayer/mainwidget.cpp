/*
* Name: mainwidget.cpp
*
* Version: 1.0
*
* Created by: FriendlyARM
*
* Purpose:  MPlayer Demo's main window
*/

#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include <linux/vt.h>
#include <linux/fb.h>
#include <linux/kd.h>

#include <QPainter>
#include <stdio.h>
#include <QWSServer>
#include <QFileDialog>
#include <QMessageBox>

#define MPLAYER_PATH "/bin/mplayer"
#define CONTROL_BAR_HEIGHT 40


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
  , m_logoPixmap(":/images/playerlogo.png")
  , m_tvoutModePixmap0(":/images/tvoutmode0.png")
  , m_tvoutModePixmap(":/images/tvoutmode.png")
  , m_playIcon(QPixmap(":/images/play.png"))
  , m_pauseIcon(QPixmap(":/images/pause.png"))
{
    ui->setupUi(this);
    m_isPlaying = false;
    m_tvoutMode = MainWidget::TVMODE_OFF;

    m_mplayerProcess = new QProcess(this);
    connect(m_mplayerProcess, SIGNAL(readyReadStandardOutput()),
        this, SLOT(catchOutput()));
    connect(m_mplayerProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(mplayerEnded(int, QProcess::ExitStatus)));

    m_timeTimer = new QTimer(this);
    connect(m_timeTimer, SIGNAL(timeout()), this, SLOT(getTimepos()));
    ui->m_slider->setEnabled(false);

    QWSServer::setCursorVisible(false);
}

void MainWidget::catchOutput()
{
    while(m_mplayerProcess->canReadLine()) {
        QByteArray buffer(m_mplayerProcess->readLine());
        // get_time_length : ANS_LENGTH=xx.yy
        if(buffer.startsWith("ANS_LENGTH"))
        {
            buffer.remove(0, 11); // vire ANS_LENGTH=
            buffer.replace(QByteArray("'"), QByteArray(""));
            buffer.replace(QByteArray(" "), QByteArray(""));
            buffer.replace(QByteArray("\n"), QByteArray(""));
            buffer.replace(QByteArray("\r"), QByteArray(""));
            float maxTime = buffer.toFloat();
            ui->m_slider->setMaximum(static_cast<int>(maxTime+1));
        }
        // get_time_pos : ANS_TIME_POSITION=xx.y
        else if(buffer.startsWith("ANS_TIME_POSITION"))
        {
            buffer.remove(0, 18); // vire ANS_TIME_POSITION=
            buffer.replace(QByteArray("'"), QByteArray(""));
            buffer.replace(QByteArray(" "), QByteArray(""));
            buffer.replace(QByteArray("\n"), QByteArray(""));
            buffer.replace(QByteArray("\r"), QByteArray(""));
            float currTime = buffer.toFloat();
            ui->m_slider->setValue(static_cast<int>(currTime+1));
        }
    }
}

void MainWidget::getTimepos()
{
    m_mplayerProcess->write("get_time_pos\n");
}

MainWidget::~MainWidget()
{
    delete ui;
}


// launch MPlayer to play video
bool MainWidget::startMPlayer(int pos)
{
    if(m_isPlaying) {
        return true;
    }

    /*
[root@FriendlyARM /]# mplayer -friendlyarm-version

MPlayer - FriendlyARM Premium Edition (http://www.arm9.net)

New options:
        -videoframe fullscreen:keepratio
                show fullscreen and keep film aspect ratio.
        -videoframe fullscreen:stretch
                show fullscreen and stretches image to the screen's size.
        -videoframe zoom:<percent>
                set videoframe's size according to zoom ratio.
                (Example: -videoframe zoom:200)

        -screenrect <x,y,w,h>
                set video's display area: video is limited to the specified area.
                (Example: -screenrect 50,50,320,240)

        -framebuffer-index <index>
                set video's display on specified framebuffer, index range 0~3.

        -tvout <off | tvonly | tvandlcd>
                Output video to TV.
   */

    QStringList args;
    args << "-framebuffer-index" << "1";
    args << "-videoframe" << "fullscreen:keepratio";

    QString screenRect = QString("%1,%2,%3,%4").arg(m_videoWindowRect.left()).arg(m_videoWindowRect.top()).arg(m_videoWindowRect.width()).arg(m_videoWindowRect.height());
    args << "-screenrect";
    args << screenRect;

    if (m_tvoutMode == MainWidget::TVMODE_TVONLY) {
        args << "-tvout" << "tvonly";
    } else if (m_tvoutMode == MainWidget::TVMODE_TVANDLCD) {
        args << "-tvout" << "tvandlcd";
    }

    args << "-slave";
    args << "-quiet";
    args << m_movieFile;

    m_mplayerProcess->setProcessChannelMode(QProcess::MergedChannels);
    m_mplayerProcess->start(MPLAYER_PATH, args);
    if(!m_mplayerProcess->waitForStarted(3000)) {
        qDebug("startMplayer failed");
        return false;
    }

    m_mplayerProcess->write("get_video_resolution\n");
    m_mplayerProcess->write("get_time_length\n");

    if (pos > 0) {
         m_mplayerProcess->write(QString("seek " + QString::number(pos) + " 2\n").toUtf8());
    }

    m_isPlaying = true;
    m_isPause = false;
    m_timeTimer->start(1000);
    ui->m_slider->setEnabled(true);

    ui->m_playButton->setIcon(m_pauseIcon);

    return true;
}


// stop playing playing
bool MainWidget::stopMPlayer()
{
    if(!m_isPlaying)
        return true;

    m_mplayerProcess->write("quit\n");
    if(!m_mplayerProcess->waitForFinished(3000)) {
        return false;
    }

    return true;
}


bool MainWidget::pauseMPlayer()
{
    if(!m_isPlaying)
        return true;

    m_mplayerProcess->write("pause\n");
    m_isPause = !m_isPause;
    if (m_isPause) {
        ui->m_playButton->setIcon(m_playIcon);
        m_timeTimer->stop();
        ui->m_slider->setEnabled(false);
    } else {
        ui->m_playButton->setIcon(m_pauseIcon);
        m_timeTimer->start(1000);
        ui->m_slider->setEnabled(true);
    }

    return true;
}

void MainWidget::mplayerEnded(int, QProcess::ExitStatus)
{
    m_isPlaying = false;
    m_isPause = false;
    m_timeTimer->stop();
    ui->m_slider->setValue(ui->m_slider->maximum());
    ui->m_slider->setEnabled(false);
    ui->m_playButton->setIcon(m_playIcon);
}

void MainWidget::closeEvent(QCloseEvent *e)
{
   stopMPlayer();
   e->accept();
}

void MainWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);

    int w = width()-4;
    int h = height()-CONTROL_BAR_HEIGHT-4;

    if (w % 8 > 0) {
        w = w - (w % 8);
    }

    if (h % 8 > 0) {
        h = h - (h % 8);
    }

    m_videoWindowRect.setLeft((width()-w)/2);
    m_videoWindowRect.setTop((height()-h-CONTROL_BAR_HEIGHT)/2);
    m_videoWindowRect.setWidth(w);
    m_videoWindowRect.setHeight(h);

    const int space = 5;
    int x = space;
    int y = height() - CONTROL_BAR_HEIGHT + space;

    ui->m_openButton->setGeometry(x,y,41,30);
    x += space + 41;

    ui->m_playButton->setGeometry(x,y,31,30);
    x += 31;

    ui->m_stopButton->setGeometry(x,y,31,30);
    x += space +31;

    int sliderWidth = width() - 5*space - 41*1 - 31*4;
    ui->m_slider->setGeometry(x,y,sliderWidth,30);
    x += space + sliderWidth;

    ui->m_tvButton->setGeometry(x,y,31,30);
    x += 31;

    ui->m_exitButton->setGeometry(x,y,31,30);
}

void MainWidget::paintEvent(QPaintEvent*)
{
    QPainter p (this);
    p.fillRect(m_videoWindowRect, QColor(0,0,0));

    QPixmap* pPixmap;
    if (m_tvoutMode == MainWidget::TVMODE_OFF) {
        pPixmap = &m_logoPixmap;
    } else {
        if (m_tvoutMode == MainWidget::TVMODE_TVONLY) {
            pPixmap = &m_tvoutModePixmap0;
        } else {
            pPixmap = &m_tvoutModePixmap;
        }
    }

    p.drawPixmap(m_videoWindowRect.left()+(m_videoWindowRect.width()-pPixmap->width())/2,m_videoWindowRect.top()+ (m_videoWindowRect.height()-pPixmap->height())/2, pPixmap->width(), pPixmap->height(), *pPixmap);
}

void MainWidget::on_m_openButton_clicked()
{
    stopMPlayer();

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("Open Media File");
    fileDialog->setDirectory("/usr/local/adsdemo/ads");
    fileDialog->setFilter("Media Files(*.mp4 *.avi)");
    fileDialog->showMaximized();
    if(fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        m_movieFile = path;
        stopMPlayer();
        startMPlayer();
    }
}

void MainWidget::on_m_playButton_clicked()
{
    if (m_isPlaying) {
        pauseMPlayer();
    } else {
        if (!m_movieFile.isEmpty()) {
            startMPlayer();
        } else {
            on_m_openButton_clicked();
        }
    }
}

void MainWidget::on_m_stopButton_clicked()
{
    stopMPlayer();
}

void MainWidget::on_m_tvButton_clicked()
{
    m_tvoutMode ++;
    if (m_tvoutMode >= MainWidget::TVMODE_MAX) {
        m_tvoutMode = MainWidget::TVMODE_OFF;
    }

    if (m_tvoutMode == MainWidget::TVMODE_TVONLY) {
        ui->m_tvButton->setIcon(QIcon(QPixmap(":/images/tv.png")));
    } else if (m_tvoutMode == MainWidget::TVMODE_TVANDLCD) {
        ui->m_tvButton->setIcon(QIcon(QPixmap(":/images/lcd.png")));
    } else {
        ui->m_tvButton->setIcon(QIcon(QPixmap(":/images/tv.png")));
    }

    if (m_isPlaying) {
        int currentPos = ui->m_slider->value();
        stopMPlayer();
        repaint();
        startMPlayer(currentPos);
    } else {
        repaint();
    }
}

void MainWidget::on_m_exitButton_clicked()
{
    QWidget::close();
}

void MainWidget::on_m_slider_sliderMoved(int position)
{
}

void MainWidget::on_m_slider_sliderPressed()
{
    if (m_isPlaying) {
        m_timeTimer->stop();
    }
}

void MainWidget::on_m_slider_sliderReleased()
{
    if (m_isPlaying && !m_isPause) {
        m_mplayerProcess->write(QString("seek " + QString::number(ui->m_slider->value()) + " 2\n").toUtf8());
        m_timeTimer->start(1000);
    }
}
