/********************************************************************************
** Form generated from reading UI file 'cutscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTSCREEN_H
#define UI_CUTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CutScreen
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *cutBt;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CutScreen)
    {
        if (CutScreen->objectName().isEmpty())
            CutScreen->setObjectName(QStringLiteral("CutScreen"));
        CutScreen->resize(501, 388);
        centralWidget = new QWidget(CutScreen);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cutBt = new QPushButton(centralWidget);
        cutBt->setObjectName(QStringLiteral("cutBt"));

        verticalLayout->addWidget(cutBt);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        CutScreen->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CutScreen);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 501, 23));
        CutScreen->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CutScreen);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CutScreen->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CutScreen);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CutScreen->setStatusBar(statusBar);

        retranslateUi(CutScreen);

        QMetaObject::connectSlotsByName(CutScreen);
    } // setupUi

    void retranslateUi(QMainWindow *CutScreen)
    {
        CutScreen->setWindowTitle(QApplication::translate("CutScreen", "CutScreen", 0));
        cutBt->setText(QApplication::translate("CutScreen", "\346\210\252\345\261\217", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CutScreen: public Ui_CutScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTSCREEN_H
