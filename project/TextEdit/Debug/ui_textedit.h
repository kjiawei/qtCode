/********************************************************************************
** Form generated from reading UI file 'textedit.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDIT_H
#define UI_TEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextEdit
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Asave;
    QAction *action_Print;
    QAction *action_PrintPreview;
    QAction *action_PDF;
    QAction *action_Quit;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Paste;
    QAction *action_Del;
    QAction *action_AllSelect;
    QAction *action_Clear;
    QAction *action_Find;
    QAction *action_Replace;
    QAction *action_Switch;
    QAction *action_Font;
    QAction *action_FontColor;
    QAction *action_ToobarShow;
    QAction *action_StatusBarShow;
    QAction *action_HighLightShow;
    QAction *action_Tile;
    QAction *action_Cascade;
    QAction *action_NextW;
    QAction *action_PreviousW;
    QAction *action_Close;
    QAction *action_AllClose;
    QAction *action_About;
    QAction *action_AboutQt;
    QAction *action_zoomIn;
    QAction *action_zoomOut;
    QWidget *centralWidget;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_RecentFile;
    QMenu *menu_E;
    QMenu *menu_O;
    QMenu *menu_V;
    QMenu *menu_H;
    QMenu *menu_W;
    QMenu *menu_ViewMode;
    QMenu *menu_SelectW;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TextEdit)
    {
        if (TextEdit->objectName().isEmpty())
            TextEdit->setObjectName(QStringLiteral("TextEdit"));
        TextEdit->resize(820, 600);
        TextEdit->setAcceptDrops(true);
        action_New = new QAction(TextEdit);
        action_New->setObjectName(QStringLiteral("action_New"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New->setIcon(icon);
        action_Open = new QAction(TextEdit);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon1);
        action_Save = new QAction(TextEdit);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save->setIcon(icon2);
        action_Asave = new QAction(TextEdit);
        action_Asave->setObjectName(QStringLiteral("action_Asave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/asave.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Asave->setIcon(icon3);
        action_Print = new QAction(TextEdit);
        action_Print->setObjectName(QStringLiteral("action_Print"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/fileprint.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Print->setIcon(icon4);
        action_PrintPreview = new QAction(TextEdit);
        action_PrintPreview->setObjectName(QStringLiteral("action_PrintPreview"));
        action_PrintPreview->setIcon(icon4);
        action_PDF = new QAction(TextEdit);
        action_PDF->setObjectName(QStringLiteral("action_PDF"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/exportpdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_PDF->setIcon(icon5);
        action_PDF->setIconVisibleInMenu(true);
        action_Quit = new QAction(TextEdit);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Quit->setIcon(icon6);
        action_Undo = new QAction(TextEdit);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Undo->setIcon(icon7);
        action_Redo = new QAction(TextEdit);
        action_Redo->setObjectName(QStringLiteral("action_Redo"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Redo->setIcon(icon8);
        action_Cut = new QAction(TextEdit);
        action_Cut->setObjectName(QStringLiteral("action_Cut"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cut->setIcon(icon9);
        action_Copy = new QAction(TextEdit);
        action_Copy->setObjectName(QStringLiteral("action_Copy"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copy->setIcon(icon10);
        action_Paste = new QAction(TextEdit);
        action_Paste->setObjectName(QStringLiteral("action_Paste"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Paste->setIcon(icon11);
        action_Del = new QAction(TextEdit);
        action_Del->setObjectName(QStringLiteral("action_Del"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/stock_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Del->setIcon(icon12);
        action_AllSelect = new QAction(TextEdit);
        action_AllSelect->setObjectName(QStringLiteral("action_AllSelect"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/edit-select-all.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_AllSelect->setIcon(icon13);
        action_Clear = new QAction(TextEdit);
        action_Clear->setObjectName(QStringLiteral("action_Clear"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/editclear.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Clear->setIcon(icon14);
        action_Find = new QAction(TextEdit);
        action_Find->setObjectName(QStringLiteral("action_Find"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/images/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Find->setIcon(icon15);
        action_Replace = new QAction(TextEdit);
        action_Replace->setObjectName(QStringLiteral("action_Replace"));
        action_Switch = new QAction(TextEdit);
        action_Switch->setObjectName(QStringLiteral("action_Switch"));
        action_Switch->setCheckable(true);
        action_Switch->setChecked(true);
        action_Font = new QAction(TextEdit);
        action_Font->setObjectName(QStringLiteral("action_Font"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/font.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Font->setIcon(icon16);
        action_FontColor = new QAction(TextEdit);
        action_FontColor->setObjectName(QStringLiteral("action_FontColor"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/images/textcolor.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_FontColor->setIcon(icon17);
        action_ToobarShow = new QAction(TextEdit);
        action_ToobarShow->setObjectName(QStringLiteral("action_ToobarShow"));
        action_ToobarShow->setCheckable(true);
        action_ToobarShow->setChecked(true);
        action_StatusBarShow = new QAction(TextEdit);
        action_StatusBarShow->setObjectName(QStringLiteral("action_StatusBarShow"));
        action_StatusBarShow->setCheckable(true);
        action_StatusBarShow->setChecked(true);
        action_HighLightShow = new QAction(TextEdit);
        action_HighLightShow->setObjectName(QStringLiteral("action_HighLightShow"));
        action_HighLightShow->setCheckable(true);
        action_HighLightShow->setChecked(false);
        action_Tile = new QAction(TextEdit);
        action_Tile->setObjectName(QStringLiteral("action_Tile"));
        action_Cascade = new QAction(TextEdit);
        action_Cascade->setObjectName(QStringLiteral("action_Cascade"));
        action_NextW = new QAction(TextEdit);
        action_NextW->setObjectName(QStringLiteral("action_NextW"));
        action_PreviousW = new QAction(TextEdit);
        action_PreviousW->setObjectName(QStringLiteral("action_PreviousW"));
        action_Close = new QAction(TextEdit);
        action_Close->setObjectName(QStringLiteral("action_Close"));
        action_AllClose = new QAction(TextEdit);
        action_AllClose->setObjectName(QStringLiteral("action_AllClose"));
        action_About = new QAction(TextEdit);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_AboutQt = new QAction(TextEdit);
        action_AboutQt->setObjectName(QStringLiteral("action_AboutQt"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/images/qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_AboutQt->setIcon(icon18);
        action_zoomIn = new QAction(TextEdit);
        action_zoomIn->setObjectName(QStringLiteral("action_zoomIn"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/images/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoomIn->setIcon(icon19);
        action_zoomOut = new QAction(TextEdit);
        action_zoomOut->setObjectName(QStringLiteral("action_zoomOut"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/images/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoomOut->setIcon(icon20);
        centralWidget = new QWidget(TextEdit);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setGeometry(QRect(0, 0, 821, 541));
        TextEdit->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TextEdit);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 820, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_RecentFile = new QMenu(menu_F);
        menu_RecentFile->setObjectName(QStringLiteral("menu_RecentFile"));
        menu_E = new QMenu(menuBar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        menu_O = new QMenu(menuBar);
        menu_O->setObjectName(QStringLiteral("menu_O"));
        menu_V = new QMenu(menuBar);
        menu_V->setObjectName(QStringLiteral("menu_V"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        menu_W = new QMenu(menuBar);
        menu_W->setObjectName(QStringLiteral("menu_W"));
        menu_ViewMode = new QMenu(menu_W);
        menu_ViewMode->setObjectName(QStringLiteral("menu_ViewMode"));
        menu_SelectW = new QMenu(menu_W);
        menu_SelectW->setObjectName(QStringLiteral("menu_SelectW"));
        TextEdit->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TextEdit);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TextEdit->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TextEdit);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TextEdit->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_E->menuAction());
        menuBar->addAction(menu_O->menuAction());
        menuBar->addAction(menu_V->menuAction());
        menuBar->addAction(menu_W->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(action_New);
        menu_F->addAction(action_Open);
        menu_F->addAction(action_Save);
        menu_F->addAction(action_Asave);
        menu_F->addSeparator();
        menu_F->addAction(action_Print);
        menu_F->addAction(action_PrintPreview);
        menu_F->addAction(action_PDF);
        menu_F->addSeparator();
        menu_F->addAction(menu_RecentFile->menuAction());
        menu_F->addSeparator();
        menu_F->addAction(action_Quit);
        menu_E->addAction(action_Undo);
        menu_E->addAction(action_Redo);
        menu_E->addSeparator();
        menu_E->addAction(action_Cut);
        menu_E->addAction(action_Copy);
        menu_E->addAction(action_Paste);
        menu_E->addAction(action_Del);
        menu_E->addSeparator();
        menu_E->addAction(action_AllSelect);
        menu_E->addAction(action_Clear);
        menu_E->addSeparator();
        menu_E->addAction(action_Find);
        menu_E->addAction(action_Replace);
        menu_O->addAction(action_Switch);
        menu_O->addSeparator();
        menu_O->addAction(action_Font);
        menu_O->addAction(action_FontColor);
        menu_V->addAction(action_ToobarShow);
        menu_V->addAction(action_StatusBarShow);
        menu_V->addSeparator();
        menu_V->addAction(action_HighLightShow);
        menu_V->addSeparator();
        menu_V->addAction(action_zoomIn);
        menu_V->addAction(action_zoomOut);
        menu_H->addAction(action_About);
        menu_H->addAction(action_AboutQt);
        menu_W->addAction(menu_ViewMode->menuAction());
        menu_W->addSeparator();
        menu_W->addAction(action_Tile);
        menu_W->addAction(action_Cascade);
        menu_W->addSeparator();
        menu_W->addAction(action_NextW);
        menu_W->addAction(action_PreviousW);
        menu_W->addSeparator();
        menu_W->addAction(action_Close);
        menu_W->addAction(action_AllClose);
        menu_W->addSeparator();
        menu_W->addAction(menu_SelectW->menuAction());
        mainToolBar->addAction(action_New);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(action_Save);
        mainToolBar->addAction(action_Asave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Undo);
        mainToolBar->addAction(action_Redo);
        mainToolBar->addAction(action_Cut);
        mainToolBar->addAction(action_Copy);
        mainToolBar->addAction(action_Paste);
        mainToolBar->addAction(action_Find);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Font);
        mainToolBar->addAction(action_FontColor);
        mainToolBar->addAction(action_Print);
        mainToolBar->addAction(action_PDF);

        retranslateUi(TextEdit);

        QMetaObject::connectSlotsByName(TextEdit);
    } // setupUi

    void retranslateUi(QMainWindow *TextEdit)
    {
        TextEdit->setWindowTitle(QApplication::translate("TextEdit", "TextEdit", 0));
        action_New->setText(QApplication::translate("TextEdit", "\346\226\260\345\273\272(&N)", 0));
        action_New->setShortcut(QApplication::translate("TextEdit", "Ctrl+N", 0));
        action_Open->setText(QApplication::translate("TextEdit", "\346\211\223\345\274\200(&O)", 0));
        action_Open->setShortcut(QApplication::translate("TextEdit", "Ctrl+O", 0));
        action_Save->setText(QApplication::translate("TextEdit", "\344\277\235\345\255\230(&S)", 0));
        action_Save->setShortcut(QApplication::translate("TextEdit", "Ctrl+S", 0));
        action_Asave->setText(QApplication::translate("TextEdit", "\345\217\246\345\255\230\344\270\272(&A)", 0));
        action_Asave->setShortcut(QApplication::translate("TextEdit", "Ctrl+A", 0));
        action_Print->setText(QApplication::translate("TextEdit", "\346\211\223\345\215\260(&P)", 0));
        action_Print->setShortcut(QApplication::translate("TextEdit", "Ctrl+P", 0));
        action_PrintPreview->setText(QApplication::translate("TextEdit", "\346\211\223\345\215\260\351\242\204\350\247\210", 0));
        action_PDF->setText(QApplication::translate("TextEdit", "\350\276\223\345\207\272PDF\346\226\207\346\241\243", 0));
        action_Quit->setText(QApplication::translate("TextEdit", "\351\200\200\345\207\272(&Q)", 0));
        action_Quit->setShortcut(QApplication::translate("TextEdit", "Ctrl+Q", 0));
        action_Undo->setText(QApplication::translate("TextEdit", "\346\222\244\351\224\200(&U)", 0));
        action_Undo->setShortcut(QApplication::translate("TextEdit", "Ctrl+Z", 0));
        action_Redo->setText(QApplication::translate("TextEdit", "\351\207\215\345\244\215(&R)", 0));
        action_Redo->setShortcut(QApplication::translate("TextEdit", "Ctrl+Y", 0));
        action_Cut->setText(QApplication::translate("TextEdit", "\345\211\252\345\210\207(&T)", 0));
        action_Cut->setShortcut(QApplication::translate("TextEdit", "Ctrl+X", 0));
        action_Copy->setText(QApplication::translate("TextEdit", "\345\244\215\345\210\266(&C)", 0));
        action_Copy->setShortcut(QApplication::translate("TextEdit", "Ctrl+C", 0));
        action_Paste->setText(QApplication::translate("TextEdit", "\347\262\230\350\264\264(&P)", 0));
        action_Paste->setShortcut(QApplication::translate("TextEdit", "Ctrl+V", 0));
        action_Del->setText(QApplication::translate("TextEdit", "\345\210\240\351\231\244(&D)", 0));
        action_Del->setShortcut(QApplication::translate("TextEdit", "Del", 0));
        action_AllSelect->setText(QApplication::translate("TextEdit", "\345\205\250\351\200\211(&A)", 0));
        action_AllSelect->setShortcut(QApplication::translate("TextEdit", "Ctrl+A", 0));
        action_Clear->setText(QApplication::translate("TextEdit", "\346\270\205\347\251\272(&L)", 0));
        action_Clear->setShortcut(QApplication::translate("TextEdit", "Ctrl+D", 0));
        action_Find->setText(QApplication::translate("TextEdit", "\346\237\245\346\211\276(&F)", 0));
        action_Find->setShortcut(QApplication::translate("TextEdit", "Ctrl+F", 0));
        action_Replace->setText(QApplication::translate("TextEdit", "\346\233\277\346\215\242(&R)", 0));
        action_Switch->setText(QApplication::translate("TextEdit", "\350\207\252\345\212\250\346\215\242\350\241\214(&W)", 0));
        action_Font->setText(QApplication::translate("TextEdit", "\345\255\227\344\275\223\350\256\276\347\275\256(F)", 0));
        action_FontColor->setText(QApplication::translate("TextEdit", "\345\255\227\344\275\223\351\242\234\350\211\262(&L)", 0));
        action_ToobarShow->setText(QApplication::translate("TextEdit", "\345\267\245\345\205\267\346\240\217(T)", 0));
        action_StatusBarShow->setText(QApplication::translate("TextEdit", "\347\212\266\346\200\201\346\240\217(&S)", 0));
        action_HighLightShow->setText(QApplication::translate("TextEdit", "\351\253\230\344\272\256\346\230\276\347\244\272(&H)", 0));
        action_Tile->setText(QApplication::translate("TextEdit", "\345\271\263\351\223\272(&T)", 0));
        action_Cascade->setText(QApplication::translate("TextEdit", "\345\261\202\345\217\240(&C)", 0));
        action_NextW->setText(QApplication::translate("TextEdit", "\344\270\213\344\270\200\347\252\227\345\217\243(&N)", 0));
        action_PreviousW->setText(QApplication::translate("TextEdit", "\345\211\215\344\270\200\347\252\227\345\217\243(&P)", 0));
        action_Close->setText(QApplication::translate("TextEdit", "\345\205\263\351\227\255\345\275\223\345\211\215(&C)", 0));
        action_AllClose->setText(QApplication::translate("TextEdit", "\345\205\263\351\227\255\346\211\200\346\234\211(&A)", 0));
        action_About->setText(QApplication::translate("TextEdit", "\345\205\263\344\272\216(&A)", 0));
        action_AboutQt->setText(QApplication::translate("TextEdit", "\345\205\263\344\272\216Qt(&Q)", 0));
        action_zoomIn->setText(QApplication::translate("TextEdit", "\346\224\276\345\244\247(&I)", 0));
        action_zoomIn->setShortcut(QApplication::translate("TextEdit", "Ctrl+Up", 0));
        action_zoomOut->setText(QApplication::translate("TextEdit", "\347\274\251\345\260\217(&O)", 0));
        action_zoomOut->setShortcut(QApplication::translate("TextEdit", "Ctrl+Down", 0));
        menu_F->setTitle(QApplication::translate("TextEdit", "\346\226\207\344\273\266(&F)", 0));
        menu_RecentFile->setTitle(QApplication::translate("TextEdit", "\346\234\200\350\277\221\346\211\223\345\274\200(&R)", 0));
        menu_E->setTitle(QApplication::translate("TextEdit", "\347\274\226\350\276\221(&E)", 0));
        menu_O->setTitle(QApplication::translate("TextEdit", "\346\240\274\345\274\217(&O)", 0));
        menu_V->setTitle(QApplication::translate("TextEdit", "\346\237\245\347\234\213 (&V)", 0));
        menu_H->setTitle(QApplication::translate("TextEdit", "\345\270\256\345\212\251(&H)", 0));
        menu_W->setTitle(QApplication::translate("TextEdit", "\347\252\227\345\217\243(&W)", 0));
        menu_ViewMode->setTitle(QApplication::translate("TextEdit", "\350\247\206\345\233\276\346\250\241\345\274\217(&V)", 0));
        menu_SelectW->setTitle(QApplication::translate("TextEdit", "\351\200\211\346\213\251\347\252\227\345\217\243(&S)", 0));
    } // retranslateUi

};

namespace Ui {
    class TextEdit: public Ui_TextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDIT_H
