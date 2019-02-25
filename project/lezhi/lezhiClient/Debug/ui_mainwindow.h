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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <rolltext.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *videoWidget;
    QLabel *weatherLabel1;
    QLabel *weatherLabel2;
    QLabel *weatherLabel3;
    QLabel *logoLabel;
    QLabel *activityLabel;
    QLabel *newLabel;
    QLabel *timeLabel;
    RollText *jinjiNewWidget;
    QWidget *tsWidget;
    RollText *danmuWidget;
    QLabel *lxLabel;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        videoWidget = new QWidget(centralWidget);
        videoWidget->setObjectName(QStringLiteral("videoWidget"));
        videoWidget->setGeometry(QRect(0, 0, 560, 331));
        videoWidget->setMouseTracking(false);
        videoWidget->setAutoFillBackground(false);
        weatherLabel1 = new QLabel(centralWidget);
        weatherLabel1->setObjectName(QStringLiteral("weatherLabel1"));
        weatherLabel1->setGeometry(QRect(0, 330, 141, 101));
        weatherLabel1->setAlignment(Qt::AlignCenter);
        weatherLabel2 = new QLabel(centralWidget);
        weatherLabel2->setObjectName(QStringLiteral("weatherLabel2"));
        weatherLabel2->setGeometry(QRect(140, 330, 141, 101));
        weatherLabel2->setAlignment(Qt::AlignCenter);
        weatherLabel3 = new QLabel(centralWidget);
        weatherLabel3->setObjectName(QStringLiteral("weatherLabel3"));
        weatherLabel3->setGeometry(QRect(280, 330, 141, 101));
        weatherLabel3->setAlignment(Qt::AlignCenter);
        logoLabel = new QLabel(centralWidget);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        logoLabel->setGeometry(QRect(420, 330, 141, 101));
        logoLabel->setAlignment(Qt::AlignCenter);
        activityLabel = new QLabel(centralWidget);
        activityLabel->setObjectName(QStringLiteral("activityLabel"));
        activityLabel->setGeometry(QRect(560, 230, 241, 201));
        activityLabel->setAlignment(Qt::AlignCenter);
        newLabel = new QLabel(centralWidget);
        newLabel->setObjectName(QStringLiteral("newLabel"));
        newLabel->setGeometry(QRect(560, 0, 241, 231));
        newLabel->setAlignment(Qt::AlignCenter);
        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(0, 430, 221, 51));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        timeLabel->setFont(font);
        timeLabel->setAlignment(Qt::AlignCenter);
        jinjiNewWidget = new RollText(centralWidget);
        jinjiNewWidget->setObjectName(QStringLiteral("jinjiNewWidget"));
        jinjiNewWidget->setGeometry(QRect(219, 429, 581, 51));
        tsWidget = new QWidget(centralWidget);
        tsWidget->setObjectName(QStringLiteral("tsWidget"));
        tsWidget->setGeometry(QRect(610, 350, 141, 61));
        danmuWidget = new RollText(centralWidget);
        danmuWidget->setObjectName(QStringLiteral("danmuWidget"));
        danmuWidget->setGeometry(QRect(560, 260, 241, 71));
        lxLabel = new QLabel(centralWidget);
        lxLabel->setObjectName(QStringLiteral("lxLabel"));
        lxLabel->setGeometry(QRect(630, 230, 81, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(14);
        lxLabel->setFont(font1);
        lxLabel->setAlignment(Qt::AlignCenter);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(570, 140, 211, 31));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\271\220\347\237\245\347\224\237\346\264\273\344\277\241\346\201\257\345\271\263\345\217\260", 0));
        weatherLabel1->setText(QString());
        weatherLabel2->setText(QString());
        weatherLabel3->setText(QString());
        logoLabel->setText(QString());
        activityLabel->setText(QApplication::translate("MainWindow", "\350\212\202\346\260\224\346\264\273\345\212\250", 0));
        newLabel->setText(QApplication::translate("MainWindow", "\346\226\260\351\227\273\346\213\233\350\201\230", 0));
        timeLabel->setText(QApplication::translate("MainWindow", "\346\227\245\346\234\237\346\227\266\351\227\264", 0));
        lxLabel->setText(QApplication::translate("MainWindow", "\346\262\246\351\231\267\345\214\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
