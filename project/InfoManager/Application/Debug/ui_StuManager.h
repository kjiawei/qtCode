/********************************************************************************
** Form generated from reading UI file 'StuManager.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUMANAGER_H
#define UI_STUMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuManager
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *StuManager)
    {
        if (StuManager->objectName().isEmpty())
            StuManager->setObjectName(QStringLiteral("StuManager"));
        StuManager->resize(400, 300);
        gridLayout = new QGridLayout(StuManager);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(StuManager);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(StuManager);

        QMetaObject::connectSlotsByName(StuManager);
    } // setupUi

    void retranslateUi(QWidget *StuManager)
    {
        StuManager->setWindowTitle(QApplication::translate("StuManager", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class StuManager: public Ui_StuManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUMANAGER_H
