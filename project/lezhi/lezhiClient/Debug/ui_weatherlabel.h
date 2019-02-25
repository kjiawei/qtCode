/********************************************************************************
** Form generated from reading UI file 'weatherlabel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHERLABEL_H
#define UI_WEATHERLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_weatherLabel
{
public:
    QLabel *tianqiLabel;
    QLabel *gaowen;
    QLabel *fx;
    QLabel *jibie;
    QLabel *diwen;
    QLabel *riqi;

    void setupUi(QWidget *weatherLabel)
    {
        if (weatherLabel->objectName().isEmpty())
            weatherLabel->setObjectName(QStringLiteral("weatherLabel"));
        weatherLabel->resize(140, 101);
        tianqiLabel = new QLabel(weatherLabel);
        tianqiLabel->setObjectName(QStringLiteral("tianqiLabel"));
        tianqiLabel->setGeometry(QRect(0, 30, 71, 51));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(26);
        tianqiLabel->setFont(font);
        tianqiLabel->setAlignment(Qt::AlignCenter);
        gaowen = new QLabel(weatherLabel);
        gaowen->setObjectName(QStringLiteral("gaowen"));
        gaowen->setGeometry(QRect(70, 30, 71, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(22);
        gaowen->setFont(font1);
        gaowen->setAlignment(Qt::AlignCenter);
        fx = new QLabel(weatherLabel);
        fx->setObjectName(QStringLiteral("fx"));
        fx->setGeometry(QRect(0, 80, 81, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        fx->setFont(font2);
        fx->setAlignment(Qt::AlignCenter);
        jibie = new QLabel(weatherLabel);
        jibie->setObjectName(QStringLiteral("jibie"));
        jibie->setGeometry(QRect(80, 80, 61, 21));
        jibie->setFont(font2);
        jibie->setAlignment(Qt::AlignCenter);
        diwen = new QLabel(weatherLabel);
        diwen->setObjectName(QStringLiteral("diwen"));
        diwen->setGeometry(QRect(80, 60, 51, 21));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(16);
        diwen->setFont(font3);
        diwen->setAlignment(Qt::AlignCenter);
        riqi = new QLabel(weatherLabel);
        riqi->setObjectName(QStringLiteral("riqi"));
        riqi->setGeometry(QRect(10, 0, 121, 31));
        riqi->setFont(font3);
        riqi->setAlignment(Qt::AlignCenter);

        retranslateUi(weatherLabel);

        QMetaObject::connectSlotsByName(weatherLabel);
    } // setupUi

    void retranslateUi(QWidget *weatherLabel)
    {
        weatherLabel->setWindowTitle(QApplication::translate("weatherLabel", "Form", 0));
        tianqiLabel->setText(QApplication::translate("weatherLabel", "\346\231\264", 0));
        gaowen->setText(QApplication::translate("weatherLabel", "24\342\204\203", 0));
        fx->setText(QApplication::translate("weatherLabel", "\345\215\227\351\243\216", 0));
        jibie->setText(QApplication::translate("weatherLabel", "\344\272\224\347\272\247", 0));
        diwen->setText(QApplication::translate("weatherLabel", "16\342\204\203", 0));
        riqi->setText(QApplication::translate("weatherLabel", "\346\230\237\346\234\237\344\270\200", 0));
    } // retranslateUi

};

namespace Ui {
    class weatherLabel: public Ui_weatherLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHERLABEL_H
