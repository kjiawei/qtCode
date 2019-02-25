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

namespace Ui {
    class MainWidget;
}

#define MOVIE_COUNT (7)


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

private slots:
    void catchOutput();
    void mplayerEnded(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent* e);
    void mousePressEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    // launch MPlayer to play video
    bool startMPlayer();
    // stop playing playing
    bool stopMPlayer();
    // open /dev/fd2 and /dev/fd3 to show logo at the video corner
    void initOSD();

    QPixmap* m_buttonImages[MOVIE_COUNT];
    QPixmap* m_buttonDownImages[MOVIE_COUNT];
    QString m_movieFiles[MOVIE_COUNT];
    int m_currentMovieIndex;
    QRect m_videoWindowRect;
    Ui::MainWidget *ui;

    QProcess *m_mplayerProcess;
    bool m_isPlaying;
    bool m_clickOnItem;

    // file descriptor (/dev/fd2)
    int m_fd2;
    // file descriptor (/dev/fd3)
    int m_fd3;
};

#endif // MAINWIDGET_H
