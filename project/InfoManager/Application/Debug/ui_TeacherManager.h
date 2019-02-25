/********************************************************************************
** Form generated from reading UI file 'TeacherManager.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERMANAGER_H
#define UI_TEACHERMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeacherManager
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *TeacherManager)
    {
        if (TeacherManager->objectName().isEmpty())
            TeacherManager->setObjectName(QStringLiteral("TeacherManager"));
        TeacherManager->resize(478, 374);
        gridLayout = new QGridLayout(TeacherManager);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(TeacherManager);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(TeacherManager);

        QMetaObject::connectSlotsByName(TeacherManager);
    } // setupUi

    void retranslateUi(QWidget *TeacherManager)
    {
        TeacherManager->setWindowTitle(QApplication::translate("TeacherManager", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TeacherManager: public Ui_TeacherManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERMANAGER_H
