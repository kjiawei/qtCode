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
#include "image.h"
#include "lcd.h"

#include <QPainter>
#include <stdio.h>
#include <QWSServer>

#define MPLAYER_PATH "/bin/mplayer"
#define ADS_PATH "/usr/local/adsdemo/ads/"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    memset(m_buttonImages, 0, sizeof(m_buttonImages));
    memset(m_buttonDownImages, 0, sizeof(m_buttonDownImages));
    m_currentMovieIndex = 0;
    m_isPlaying = false;

    m_mplayerProcess = new QProcess(this);
    connect(m_mplayerProcess, SIGNAL(readyReadStandardOutput()),
        this, SLOT(catchOutput()));
    connect(m_mplayerProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(mplayerEnded(int, QProcess::ExitStatus)));

    QStringList adsList;
    adsList << QString(ADS_PATH"iphone4.mp4")
            << QString(ADS_PATH"car.mp4")
            << QString(ADS_PATH"vsop.mp4")
            << QString(ADS_PATH"ipad2.mp4")
            << QString(ADS_PATH"qqweibo.mp4")
            << QString(ADS_PATH"wuyanzu.mp4")
            << QString(ADS_PATH"biguiyuan.mp4");

    int adsIndex = 0;
    for (int i=0; i<MOVIE_COUNT; i++) {
        m_movieFiles[i] = adsList[adsIndex++];
        if (adsIndex >= adsList.count()) {
            adsIndex = 0;
        }
    }

    m_fd2 = -1;
    m_fd3 = -1;

    setAutoFillBackground(false);
    QWSServer::setCursorVisible(false);
}

void MainWidget::catchOutput()
{
    while(m_mplayerProcess->canReadLine()) {
        QByteArray buffer(m_mplayerProcess->readLine());
        //TODO:
    }
}

MainWidget::~MainWidget()
{
    delete ui;

    for (int i=0; i<MOVIE_COUNT; i++) {
        delete m_buttonImages[i];
        delete m_buttonDownImages[i];
    }

    if (m_fd2 >= 0) {
        ioctl(m_fd2, SET_OSD_STOP);
        ::close(m_fd2);
        m_fd2 = -1;
    }

    if (m_fd3 >= 0) {
        ioctl(m_fd3, SET_OSD_STOP);
        ::close(m_fd3);
        m_fd3 = -1;
    }
}


// open /dev/fd2 and /dev/fd3 to show logo at the video corner
void MainWidget::initOSD()
{
    m_fd2 = ::open(FB_DEV_NAME2, O_RDWR | O_NDELAY);
    if (m_fd2 >= 0) {
        s3c_win_info_t fb_info_to_driver;
        fb_info_to_driver.Bpp = 16;  //BPP
        fb_info_to_driver.LeftTop_x = 5;
        fb_info_to_driver.LeftTop_y = 5;
        fb_info_to_driver.Width = 80;
        fb_info_to_driver.Height = 18;


        int fb_size = fb_info_to_driver.Width * fb_info_to_driver.Height * 2; // RGB565
        char* fb_addr = (char *) mmap(0, fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd2, 0);
        if (fb_addr == NULL) {
            ::close(m_fd2);
            m_fd2 = -1;
             qDebug("mmap fb2 failed!");
            return ;
        }

        if (ioctl(m_fd2, SET_OSD_INFO, &fb_info_to_driver) == -1) {
            qDebug("SET_OSD_INFO fb2 failed!");
        }

        if (ioctl(m_fd2, SET_OSD_START) == -1) {
            qDebug("SET_OSD_START fb2 failed!");
        }

        // show logo at the video corner (left/top)
        memcpy(fb_addr, gImage_logo, sizeof(gImage_logo));
    } else {
        qDebug("open fb2 failed!");
    }


    m_fd3 = ::open(FB_DEV_NAME3, O_RDWR | O_NDELAY);
    if (m_fd3 >= 0) {
        s3c_win_info_t fb_info_to_driver;
        fb_info_to_driver.Bpp = 16;  //BPP
        fb_info_to_driver.Width = 300;
        fb_info_to_driver.Height = 18;
        fb_info_to_driver.LeftTop_x = 5;
        fb_info_to_driver.LeftTop_y = height()-fb_info_to_driver.Height-5;

        int fb_size = fb_info_to_driver.Width * fb_info_to_driver.Height * 2; // RGB565
        char* fb_addr = (char *) mmap(0, fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd3, 0);
        if (fb_addr == NULL) {
            ::close(m_fd3);
            m_fd3 = -1;
             qDebug("mmap fb3 failed!");
            return ;
        }

        if (ioctl(m_fd3, SET_OSD_INFO, &fb_info_to_driver) == -1) {
            qDebug("SET_OSD_INFO fb3 failed!");
        }

        if (ioctl(m_fd3, SET_OSD_START) == -1) {
            qDebug("SET_OSD_START fb3 failed!");
        }

        // show text at the video corner (left/bottom)
        memcpy(fb_addr, gImage_bottom, sizeof(gImage_bottom));
    } else {
        qDebug("open fb3 failed!");
    }
}

// launch MPlayer to play video
bool MainWidget::startMPlayer()
{
    if(m_isPlaying) {
        return true;
    }

    /*
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

   */

    QStringList args;
    args << "-framebuffer-index" << "1";
    args << "-videoframe" << "fullscreen:keepratio";

    QString screenRect = QString("%1,%2,%3,%4").arg(m_videoWindowRect.left()).arg(m_videoWindowRect.top()).arg(m_videoWindowRect.width()).arg(m_videoWindowRect.height());
    args << "-screenrect";
    args << screenRect;

    args << "-slave";
    args << "-quiet";
    args << m_movieFiles[m_currentMovieIndex];

    m_mplayerProcess->setProcessChannelMode(QProcess::MergedChannels);
    m_mplayerProcess->start(MPLAYER_PATH, args);
    if(!m_mplayerProcess->waitForStarted(3000)) {
        qDebug("startMplayer failed");
        return false;
    }
    m_isPlaying = true;
    m_clickOnItem = false;
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

void MainWidget::mplayerEnded(int exitCode, QProcess::ExitStatus exitStatus)
{
    m_isPlaying = false;

    if (m_clickOnItem) {
        startMPlayer();
    } else {
        // play next video
        m_currentMovieIndex++;
        if (m_currentMovieIndex>=MOVIE_COUNT) {
            m_currentMovieIndex = 0;
        }
        repaint(width()-m_buttonImages[0]->width(),0,m_buttonImages[0]->width(),height());
        startMPlayer();
    }

    m_clickOnItem = false;
}

void MainWidget::closeEvent(QCloseEvent *e)
{
   stopMPlayer();
   e->accept();
}

void MainWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);

    if (m_buttonImages[0] == 0) {
        if (height() < 480) {
            for (int i=0; i<MOVIE_COUNT; i++) {
                m_buttonImages[i] = new QPixmap(QString(":/images_lcd4/button%1.png").arg(i+1));
                m_buttonDownImages[i] = new QPixmap(QString(":/images_lcd4/button%1_down.png").arg(i+1));
            }
        } else {
            for (int i=0; i<MOVIE_COUNT; i++) {
                m_buttonImages[i] = new QPixmap(QString(":/images_lcd7/button%1.png").arg(i+1));
                m_buttonDownImages[i] = new QPixmap(QString(":/images_lcd7/button%1_down.png").arg(i+1));
            }
        }
    }

    m_videoWindowRect.setLeft(2);
    m_videoWindowRect.setTop(2);
    m_videoWindowRect.setWidth(width()-4-m_buttonImages[0]->width());
    m_videoWindowRect.setHeight(height()-4);

    initOSD();
    startMPlayer();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);

    int x = width()-m_buttonImages[0]->width();
    int y = 0;
    bool clickOnItem = false;

    for (int i=0; i<MOVIE_COUNT; i++) {
        QRect rect(x,y,m_buttonImages[i]->width(),m_buttonImages[i]->height());
        if (rect.contains(e->pos())) {
            m_currentMovieIndex = i;
            clickOnItem = true;
            repaint(width()-m_buttonImages[0]->width(),0,m_buttonImages[0]->width(),height());
            break;
        }
        y += m_buttonImages[i]->height();
    }

    if (clickOnItem) {
        m_clickOnItem = true;
        stopMPlayer();
    } else {
        stopMPlayer();
        QWidget::close();
    }
}

void MainWidget::paintEvent(QPaintEvent* e)
{
    static QPixmap pix(width(),height());
    QPainter painter(&pix);
    painter.fillRect(0, 0, width(), height(), QColor(0,0,0));

    int x = width()-m_buttonImages[0]->width();
    int y = 0;
    for (int i=0; i<MOVIE_COUNT; i++) {
        if (m_currentMovieIndex == i) {
            painter.drawPixmap(x,y,m_buttonDownImages[i]->width(),m_buttonDownImages[i]->height(),*(m_buttonDownImages[i]));
        } else {
            painter.drawPixmap(x,y,m_buttonImages[i]->width(),m_buttonImages[i]->height(),*(m_buttonImages[i]));
        }
        y += m_buttonImages[i]->height();
    }

    QPainter p (this);
    p.drawPixmap(0, 0, pix);
}
