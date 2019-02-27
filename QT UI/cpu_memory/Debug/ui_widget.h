/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QLabel *labCPUMemory;
    QComboBox *cboxColor;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labLive;
    QLabel *labDateTime;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(723, 566);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 60));
        lcdNumber->setStyleSheet(QStringLiteral(""));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setDigitCount(19);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout->addWidget(lcdNumber);

        labCPUMemory = new QLabel(Widget);
        labCPUMemory->setObjectName(QStringLiteral("labCPUMemory"));
        labCPUMemory->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(labCPUMemory);

        cboxColor = new QComboBox(Widget);
        cboxColor->setObjectName(QStringLiteral("cboxColor"));
        cboxColor->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(cboxColor);

        tableWidget = new QTableWidget(Widget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labLive = new QLabel(Widget);
        labLive->setObjectName(QStringLiteral("labLive"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labLive->sizePolicy().hasHeightForWidth());
        labLive->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(labLive);

        labDateTime = new QLabel(Widget);
        labDateTime->setObjectName(QStringLiteral("labDateTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labDateTime->sizePolicy().hasHeightForWidth());
        labDateTime->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(labDateTime);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labCPUMemory->setText(QApplication::translate("Widget", "CPU : 0%  \345\206\205\345\255\230 : 0% ( \345\267\262\347\224\250 0 MB / \345\205\261 0 MB )", 0));
        labLive->setText(QApplication::translate("Widget", "\345\267\262\350\277\220\350\241\214 : 0\345\244\2510\346\227\2660\345\210\2060\347\247\222  |  ", 0));
        labDateTime->setText(QApplication::translate("Widget", "\345\275\223\345\211\215\346\227\266\351\227\264 : 2015\345\271\2641\346\234\2101\346\227\245 12:33:33", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
