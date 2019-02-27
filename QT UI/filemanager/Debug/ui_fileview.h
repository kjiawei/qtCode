/********************************************************************************
** Form generated from reading UI file 'fileview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEVIEW_H
#define UI_FILEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fileview
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *backButton;
    QToolButton *forwardButton;
    QToolButton *aheadButton;
    QToolButton *listButton;
    QToolButton *detailButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QListView *listView;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *closeButton;

    void setupUi(QWidget *fileview)
    {
        if (fileview->objectName().isEmpty())
            fileview->setObjectName(QStringLiteral("fileview"));
        fileview->resize(240, 320);
        verticalLayout = new QVBoxLayout(fileview);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        backButton = new QToolButton(fileview);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setEnabled(true);
        backButton->setStyleSheet(QStringLiteral("border-style: flat;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/buttons/images/left-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon);
        backButton->setIconSize(QSize(24, 24));
        backButton->setAutoRaise(true);

        horizontalLayout->addWidget(backButton);

        forwardButton = new QToolButton(fileview);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setStyleSheet(QStringLiteral("border-style: flat;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/buttons/images/right-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        forwardButton->setIcon(icon1);
        forwardButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(forwardButton);

        aheadButton = new QToolButton(fileview);
        aheadButton->setObjectName(QStringLiteral("aheadButton"));
        aheadButton->setStyleSheet(QStringLiteral("border-style: flat;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/buttons/images/up-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        aheadButton->setIcon(icon2);
        aheadButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(aheadButton);

        listButton = new QToolButton(fileview);
        listButton->setObjectName(QStringLiteral("listButton"));
        listButton->setStyleSheet(QStringLiteral("border-style: flat;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/buttons/images/viewlist-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        listButton->setIcon(icon3);
        listButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(listButton);

        detailButton = new QToolButton(fileview);
        detailButton->setObjectName(QStringLiteral("detailButton"));
        detailButton->setStyleSheet(QStringLiteral("border-style: flat;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/buttons/images/viewdetailed-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        detailButton->setIcon(icon4);
        detailButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(detailButton);


        verticalLayout->addLayout(horizontalLayout);

        stackedWidget = new QStackedWidget(fileview);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listView = new QListView(page);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_2->addWidget(listView);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        treeView = new QTreeView(page_2);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout_3->addWidget(treeView);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        closeButton = new QPushButton(fileview);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);
        closeButton->setFlat(false);

        horizontalLayout_2->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(fileview);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(fileview);
    } // setupUi

    void retranslateUi(QWidget *fileview)
    {
        fileview->setWindowTitle(QApplication::translate("fileview", "Widget", 0));
        backButton->setText(QString());
        forwardButton->setText(QString());
        aheadButton->setText(QString());
        listButton->setText(QString());
        detailButton->setText(QString());
        closeButton->setText(QApplication::translate("fileview", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class fileview: public Ui_fileview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEVIEW_H
