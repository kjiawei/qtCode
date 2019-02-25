/********************************************************************************
** Form generated from reading UI file 'find_replace.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_REPLACE_H
#define UI_FIND_REPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Find_Replace
{
public:
    QTabWidget *tabWidget;
    QWidget *find;
    QPushButton *nextButtonF;
    QLineEdit *lineEditF;
    QLabel *labelFindF;
    QCheckBox *checkBoxSenceF;
    QPushButton *cancleButtonF;
    QGroupBox *groupBoxDirectionF;
    QRadioButton *radioButtonUpF;
    QRadioButton *radioButtonDownF;
    QWidget *replace;
    QCheckBox *checkBoxSenceR;
    QGroupBox *groupBoxDirectionR;
    QRadioButton *radioButtonUpR;
    QRadioButton *radioButtonDownR;
    QLabel *labelFindR;
    QLineEdit *lineEditR;
    QPushButton *nextButtonR;
    QPushButton *cancleButtonR;
    QLineEdit *lineEditreplace;
    QLabel *labelReplace;
    QPushButton *pushButtonReplace;
    QPushButton *pushButtonReplaceAll;

    void setupUi(QDialog *Find_Replace)
    {
        if (Find_Replace->objectName().isEmpty())
            Find_Replace->setObjectName(QStringLiteral("Find_Replace"));
        Find_Replace->resize(420, 160);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        Find_Replace->setWindowIcon(icon);
        tabWidget = new QTabWidget(Find_Replace);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 422, 161));
        find = new QWidget();
        find->setObjectName(QStringLiteral("find"));
        nextButtonF = new QPushButton(find);
        nextButtonF->setObjectName(QStringLiteral("nextButtonF"));
        nextButtonF->setGeometry(QRect(310, 10, 91, 23));
        lineEditF = new QLineEdit(find);
        lineEditF->setObjectName(QStringLiteral("lineEditF"));
        lineEditF->setGeometry(QRect(110, 10, 171, 20));
        labelFindF = new QLabel(find);
        labelFindF->setObjectName(QStringLiteral("labelFindF"));
        labelFindF->setGeometry(QRect(40, 10, 61, 20));
        checkBoxSenceF = new QCheckBox(find);
        checkBoxSenceF->setObjectName(QStringLiteral("checkBoxSenceF"));
        checkBoxSenceF->setGeometry(QRect(10, 100, 101, 16));
        cancleButtonF = new QPushButton(find);
        cancleButtonF->setObjectName(QStringLiteral("cancleButtonF"));
        cancleButtonF->setGeometry(QRect(310, 100, 91, 23));
        groupBoxDirectionF = new QGroupBox(find);
        groupBoxDirectionF->setObjectName(QStringLiteral("groupBoxDirectionF"));
        groupBoxDirectionF->setGeometry(QRect(130, 70, 151, 51));
        radioButtonUpF = new QRadioButton(groupBoxDirectionF);
        radioButtonUpF->setObjectName(QStringLiteral("radioButtonUpF"));
        radioButtonUpF->setGeometry(QRect(10, 20, 61, 16));
        radioButtonDownF = new QRadioButton(groupBoxDirectionF);
        radioButtonDownF->setObjectName(QStringLiteral("radioButtonDownF"));
        radioButtonDownF->setGeometry(QRect(80, 20, 61, 16));
        tabWidget->addTab(find, QString());
        replace = new QWidget();
        replace->setObjectName(QStringLiteral("replace"));
        checkBoxSenceR = new QCheckBox(replace);
        checkBoxSenceR->setObjectName(QStringLiteral("checkBoxSenceR"));
        checkBoxSenceR->setGeometry(QRect(10, 100, 101, 16));
        groupBoxDirectionR = new QGroupBox(replace);
        groupBoxDirectionR->setObjectName(QStringLiteral("groupBoxDirectionR"));
        groupBoxDirectionR->setGeometry(QRect(130, 70, 151, 51));
        radioButtonUpR = new QRadioButton(groupBoxDirectionR);
        radioButtonUpR->setObjectName(QStringLiteral("radioButtonUpR"));
        radioButtonUpR->setGeometry(QRect(10, 20, 61, 16));
        radioButtonDownR = new QRadioButton(groupBoxDirectionR);
        radioButtonDownR->setObjectName(QStringLiteral("radioButtonDownR"));
        radioButtonDownR->setGeometry(QRect(80, 20, 61, 16));
        labelFindR = new QLabel(replace);
        labelFindR->setObjectName(QStringLiteral("labelFindR"));
        labelFindR->setGeometry(QRect(40, 10, 61, 20));
        lineEditR = new QLineEdit(replace);
        lineEditR->setObjectName(QStringLiteral("lineEditR"));
        lineEditR->setGeometry(QRect(110, 10, 171, 20));
        nextButtonR = new QPushButton(replace);
        nextButtonR->setObjectName(QStringLiteral("nextButtonR"));
        nextButtonR->setGeometry(QRect(310, 10, 91, 23));
        cancleButtonR = new QPushButton(replace);
        cancleButtonR->setObjectName(QStringLiteral("cancleButtonR"));
        cancleButtonR->setGeometry(QRect(310, 100, 91, 23));
        lineEditreplace = new QLineEdit(replace);
        lineEditreplace->setObjectName(QStringLiteral("lineEditreplace"));
        lineEditreplace->setGeometry(QRect(110, 40, 171, 20));
        labelReplace = new QLabel(replace);
        labelReplace->setObjectName(QStringLiteral("labelReplace"));
        labelReplace->setGeometry(QRect(40, 40, 61, 20));
        pushButtonReplace = new QPushButton(replace);
        pushButtonReplace->setObjectName(QStringLiteral("pushButtonReplace"));
        pushButtonReplace->setGeometry(QRect(310, 40, 91, 23));
        pushButtonReplaceAll = new QPushButton(replace);
        pushButtonReplaceAll->setObjectName(QStringLiteral("pushButtonReplaceAll"));
        pushButtonReplaceAll->setGeometry(QRect(310, 70, 91, 23));
        tabWidget->addTab(replace, QString());
        QWidget::setTabOrder(lineEditF, nextButtonF);
        QWidget::setTabOrder(nextButtonF, checkBoxSenceF);
        QWidget::setTabOrder(checkBoxSenceF, radioButtonUpF);
        QWidget::setTabOrder(radioButtonUpF, radioButtonDownF);
        QWidget::setTabOrder(radioButtonDownF, cancleButtonF);
        QWidget::setTabOrder(cancleButtonF, lineEditR);
        QWidget::setTabOrder(lineEditR, lineEditreplace);
        QWidget::setTabOrder(lineEditreplace, nextButtonR);
        QWidget::setTabOrder(nextButtonR, pushButtonReplace);
        QWidget::setTabOrder(pushButtonReplace, pushButtonReplaceAll);
        QWidget::setTabOrder(pushButtonReplaceAll, cancleButtonR);
        QWidget::setTabOrder(cancleButtonR, radioButtonDownR);
        QWidget::setTabOrder(radioButtonDownR, radioButtonUpR);
        QWidget::setTabOrder(radioButtonUpR, checkBoxSenceR);
        QWidget::setTabOrder(checkBoxSenceR, tabWidget);

        retranslateUi(Find_Replace);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Find_Replace);
    } // setupUi

    void retranslateUi(QDialog *Find_Replace)
    {
        Find_Replace->setWindowTitle(QApplication::translate("Find_Replace", "\346\237\245\346\211\276&\346\233\277\346\215\242", 0));
        nextButtonF->setText(QApplication::translate("Find_Replace", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252(&F)", 0));
        labelFindF->setText(QApplication::translate("Find_Replace", "\346\237\245\346\211\276\345\206\205\345\256\271\357\274\232", 0));
        checkBoxSenceF->setText(QApplication::translate("Find_Replace", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231(&H)", 0));
        cancleButtonF->setText(QApplication::translate("Find_Replace", "\345\217\226\346\266\210(&C)", 0));
        groupBoxDirectionF->setTitle(QApplication::translate("Find_Replace", "\346\226\271\345\220\221\357\274\232", 0));
        radioButtonUpF->setText(QApplication::translate("Find_Replace", "\345\220\221\344\270\212(&U)", 0));
        radioButtonDownF->setText(QApplication::translate("Find_Replace", "\345\220\221\344\270\213(&D)", 0));
        tabWidget->setTabText(tabWidget->indexOf(find), QApplication::translate("Find_Replace", "\346\237\245\346\211\276(&F)", 0));
        checkBoxSenceR->setText(QApplication::translate("Find_Replace", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231(&H)", 0));
        groupBoxDirectionR->setTitle(QApplication::translate("Find_Replace", "\346\226\271\345\220\221\357\274\232", 0));
        radioButtonUpR->setText(QApplication::translate("Find_Replace", "\345\220\221\344\270\212(&U)", 0));
        radioButtonDownR->setText(QApplication::translate("Find_Replace", "\345\220\221\344\270\213(&D)", 0));
        labelFindR->setText(QApplication::translate("Find_Replace", "\346\237\245\346\211\276\345\206\205\345\256\271\357\274\232", 0));
        nextButtonR->setText(QApplication::translate("Find_Replace", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252(&F)", 0));
        cancleButtonR->setText(QApplication::translate("Find_Replace", "\345\217\226\346\266\210(&C)", 0));
        labelReplace->setText(QApplication::translate("Find_Replace", " \346\233\277\346\215\242\344\270\272\357\274\232", 0));
        pushButtonReplace->setText(QApplication::translate("Find_Replace", "\346\233\277\346\215\242(&R)", 0));
        pushButtonReplaceAll->setText(QApplication::translate("Find_Replace", "\345\205\250\351\203\250\346\233\277\346\215\242(&A)", 0));
        tabWidget->setTabText(tabWidget->indexOf(replace), QApplication::translate("Find_Replace", "\346\233\277\346\215\242(&R)", 0));
    } // retranslateUi

};

namespace Ui {
    class Find_Replace: public Ui_Find_Replace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_REPLACE_H
