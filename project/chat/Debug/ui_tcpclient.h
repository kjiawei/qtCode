/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

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

class Ui_TcpClient
{
public:
    QProgressBar *progressBar;
    QPushButton *tcpClientCancleBtn;
    QPushButton *tcpClientCloseBtn;
    QLabel *tcpClientStatusLabel;

    void setupUi(QDialog *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QStringLiteral("TcpClient"));
        TcpClient->resize(350, 180);
        progressBar = new QProgressBar(TcpClient);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 90, 311, 23));
        progressBar->setValue(0);
        tcpClientCancleBtn = new QPushButton(TcpClient);
        tcpClientCancleBtn->setObjectName(QStringLiteral("tcpClientCancleBtn"));
        tcpClientCancleBtn->setGeometry(QRect(140, 140, 75, 23));
        tcpClientCloseBtn = new QPushButton(TcpClient);
        tcpClientCloseBtn->setObjectName(QStringLiteral("tcpClientCloseBtn"));
        tcpClientCloseBtn->setGeometry(QRect(240, 140, 75, 23));
        tcpClientStatusLabel = new QLabel(TcpClient);
        tcpClientStatusLabel->setObjectName(QStringLiteral("tcpClientStatusLabel"));
        tcpClientStatusLabel->setGeometry(QRect(20, 10, 321, 71));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        tcpClientStatusLabel->setFont(font);
        tcpClientStatusLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QDialog *TcpClient)
    {
        TcpClient->setWindowTitle(QApplication::translate("TcpClient", "\346\226\207\344\273\266\344\274\240\351\200\201", 0));
        tcpClientCancleBtn->setText(QApplication::translate("TcpClient", "\345\217\226\346\266\210", 0));
        tcpClientCloseBtn->setText(QApplication::translate("TcpClient", "\345\205\263\351\227\255", 0));
        tcpClientStatusLabel->setText(QApplication::translate("TcpClient", "\347\255\211\345\276\205\346\216\245\346\224\266\346\226\207\344\273\266... ...", 0));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
