/********************************************************************************
** Form generated from reading UI file 'MarkDownTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKDOWNTEST_H
#define UI_MARKDOWNTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MarkDownTestClass
{
public:

    void setupUi(QWidget *MarkDownTestClass)
    {
        if (MarkDownTestClass->objectName().isEmpty())
            MarkDownTestClass->setObjectName(QStringLiteral("MarkDownTestClass"));
        MarkDownTestClass->resize(600, 400);

        retranslateUi(MarkDownTestClass);

        QMetaObject::connectSlotsByName(MarkDownTestClass);
    } // setupUi

    void retranslateUi(QWidget *MarkDownTestClass)
    {
        MarkDownTestClass->setWindowTitle(QApplication::translate("MarkDownTestClass", "MarkDownTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MarkDownTestClass: public Ui_MarkDownTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKDOWNTEST_H
