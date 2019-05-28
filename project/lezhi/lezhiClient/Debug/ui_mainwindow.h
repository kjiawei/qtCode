/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <rolltext.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QLabel *weatherLabel1;
    QLabel *logoLabel;
    QLabel *weatherLabel2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *timeLabel;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_10;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    RollText *jinjiNewWidget;
    RollText *danmuWidget;
    QLabel *lxLabel;
    QLabel *activityLabel;
    QWidget *tsWidget;
    QLabel *weatherLabel3;
    QPushButton *pushButton_11;
    QLabel *newLabel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_12;
    QSlider *voiceSlider;
    QPushButton *pushButton;
    QWidget *videoWidget;
    QProgressBar *progressBar;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1144, 569);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 5, 1, 1);

        weatherLabel1 = new QLabel(centralWidget);
        weatherLabel1->setObjectName(QStringLiteral("weatherLabel1"));
        weatherLabel1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(weatherLabel1, 19, 0, 3, 1);

        logoLabel = new QLabel(centralWidget);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        logoLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(logoLabel, 19, 4, 2, 1);

        weatherLabel2 = new QLabel(centralWidget);
        weatherLabel2->setObjectName(QStringLiteral("weatherLabel2"));
        weatherLabel2->setMaximumSize(QSize(140, 140));
        weatherLabel2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(weatherLabel2, 19, 1, 3, 2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(pushButton_3, 0, 7, 1, 1);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(60, 60));

        gridLayout->addWidget(pushButton_4, 1, 7, 1, 1);

        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        timeLabel->setFont(font);
        timeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(timeLabel, 22, 0, 1, 1);

        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 2, 6, 1, 1);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 3, 7, 1, 1);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 3, 6, 1, 1);

        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 2, 7, 1, 1);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 3, 5, 1, 1);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 2, 5, 1, 1);

        jinjiNewWidget = new RollText(centralWidget);
        jinjiNewWidget->setObjectName(QStringLiteral("jinjiNewWidget"));

        gridLayout->addWidget(jinjiNewWidget, 22, 2, 1, 6);

        danmuWidget = new RollText(centralWidget);
        danmuWidget->setObjectName(QStringLiteral("danmuWidget"));
        lxLabel = new QLabel(danmuWidget);
        lxLabel->setObjectName(QStringLiteral("lxLabel"));
        lxLabel->setGeometry(QRect(100, -50, 184, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(14);
        lxLabel->setFont(font1);
        lxLabel->setAlignment(Qt::AlignCenter);
        activityLabel = new QLabel(danmuWidget);
        activityLabel->setObjectName(QStringLiteral("activityLabel"));
        activityLabel->setGeometry(QRect(160, -40, 60, 41));
        activityLabel->setMaximumSize(QSize(60, 16777215));
        activityLabel->setAlignment(Qt::AlignCenter);
        lxLabel->raise();
        activityLabel->raise();

        gridLayout->addWidget(danmuWidget, 17, 5, 3, 3);

        tsWidget = new QWidget(centralWidget);
        tsWidget->setObjectName(QStringLiteral("tsWidget"));

        gridLayout->addWidget(tsWidget, 20, 6, 1, 2);

        weatherLabel3 = new QLabel(centralWidget);
        weatherLabel3->setObjectName(QStringLiteral("weatherLabel3"));
        weatherLabel3->setMaximumSize(QSize(140, 140));
        weatherLabel3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(weatherLabel3, 19, 3, 2, 1);

        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout->addWidget(pushButton_11, 4, 7, 1, 1);

        newLabel = new QLabel(centralWidget);
        newLabel->setObjectName(QStringLiteral("newLabel"));
        newLabel->setMaximumSize(QSize(16777215, 20));
        newLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(newLabel, 6, 5, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(label, 6, 6, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(40, 16777215));

        gridLayout->addWidget(label_2, 7, 6, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(80, 16777215));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 7, 5, 1, 1);

        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 10, 6, 1, 1);

        voiceSlider = new QSlider(centralWidget);
        voiceSlider->setObjectName(QStringLiteral("voiceSlider"));
        voiceSlider->setMinimumSize(QSize(0, 60));
        voiceSlider->setMaximumSize(QSize(5, 60));
        voiceSlider->setValue(50);
        voiceSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(voiceSlider, 9, 5, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 5, 1, 1);

        videoWidget = new QWidget(centralWidget);
        videoWidget->setObjectName(QStringLiteral("videoWidget"));
        videoWidget->setMouseTracking(false);
        videoWidget->setAutoFillBackground(false);

        gridLayout->addWidget(videoWidget, 0, 0, 18, 5);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximumSize(QSize(848, 16777215));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 18, 0, 1, 5);

        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        gridLayout->addWidget(pushButton_13, 12, 6, 1, 1);

        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        gridLayout->addWidget(pushButton_14, 11, 6, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(120, 240));

        gridLayout->addWidget(textEdit, 10, 5, 4, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\271\220\347\237\245\347\224\237\346\264\273\344\277\241\346\201\257\345\271\263\345\217\260", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\222\255\346\224\276\345\231\250", 0));
        weatherLabel1->setText(QString());
        logoLabel->setText(QString());
        weatherLabel2->setText(QString());
        pushButton_3->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", 0));
        timeLabel->setText(QApplication::translate("MainWindow", "\346\227\245\346\234\237\346\227\266\351\227\264", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "\351\237\263\351\207\217+", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "\351\235\231\351\237\263", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "\345\277\253\351\200\200", 0));
        pushButton_10->setText(QApplication::translate("MainWindow", "\351\237\263\351\207\217-", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "\345\277\253\350\277\233", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\345\205\250\345\261\217", 0));
        lxLabel->setText(QApplication::translate("MainWindow", "\346\262\246\351\231\267\345\214\272", 0));
        activityLabel->setText(QApplication::translate("MainWindow", "\350\212\202\346\260\224\346\264\273\345\212\250", 0));
        weatherLabel3->setText(QString());
        pushButton_11->setText(QApplication::translate("MainWindow", "\346\210\252\345\261\217", 0));
        newLabel->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276\346\227\266\351\227\264", 0));
        label->setText(QApplication::translate("MainWindow", "00:00", 0));
        label_2->setText(QApplication::translate("MainWindow", "00:00", 0));
        label_3->setText(QApplication::translate("MainWindow", "\350\247\206\351\242\221\351\225\277\347\237\255", 0));
        pushButton_12->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        pushButton_13->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
        pushButton_14->setText(QApplication::translate("MainWindow", "\346\227\266\345\210\273\346\240\207\350\256\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
