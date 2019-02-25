/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QProgressBar *progressBar;
    QLabel *serverStatusLabel;
    QPushButton *serverOpenBtn;
    QPushButton *serverCloseBtn;
    QPushButton *serverSendBtn;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QStringLiteral("TcpServer"));
        TcpServer->resize(350, 180);
        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 90, 291, 23));
        progressBar->setValue(0);
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(10, 10, 331, 71));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        serverStatusLabel->setFont(font);
        serverStatusLabel->setAlignment(Qt::AlignCenter);
        serverOpenBtn = new QPushButton(TcpServer);
        serverOpenBtn->setObjectName(QStringLiteral("serverOpenBtn"));
        serverOpenBtn->setGeometry(QRect(60, 140, 75, 23));
        serverCloseBtn = new QPushButton(TcpServer);
        serverCloseBtn->setObjectName(QStringLiteral("serverCloseBtn"));
        serverCloseBtn->setGeometry(QRect(240, 140, 75, 23));
        serverSendBtn = new QPushButton(TcpServer);
        serverSendBtn->setObjectName(QStringLiteral("serverSendBtn"));
        serverSendBtn->setGeometry(QRect(150, 140, 75, 23));

        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QApplication::translate("TcpServer", "\346\226\207\344\273\266\344\274\240\351\200\201", 0));
        serverStatusLabel->setText(QApplication::translate("TcpServer", "\350\257\267\351\200\211\346\213\251\350\246\201\345\217\221\351\200\201\347\232\204\346\226\207\344\273\266\357\274\201", 0));
        serverOpenBtn->setText(QApplication::translate("TcpServer", "\346\211\223\345\274\200", 0));
        serverCloseBtn->setText(QApplication::translate("TcpServer", "\351\200\200\345\207\272", 0));
        serverSendBtn->setText(QApplication::translate("TcpServer", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
