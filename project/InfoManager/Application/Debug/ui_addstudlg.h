/********************************************************************************
** Form generated from reading UI file 'addstudlg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTUDLG_H
#define UI_ADDSTUDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddStuDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *NameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *IDEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *AgeSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *SexComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *AddressEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *PhoneEdit;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
    QTextEdit *DescText;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddStuDlg)
    {
        if (AddStuDlg->objectName().isEmpty())
            AddStuDlg->setObjectName(QStringLiteral("AddStuDlg"));
        AddStuDlg->resize(288, 299);
        verticalLayout_2 = new QVBoxLayout(AddStuDlg);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AddStuDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(70, 0));
        label->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label);

        NameEdit = new QLineEdit(AddStuDlg);
        NameEdit->setObjectName(QStringLiteral("NameEdit"));

        horizontalLayout->addWidget(NameEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(AddStuDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(70, 0));
        label_2->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(label_2);

        IDEdit = new QLineEdit(AddStuDlg);
        IDEdit->setObjectName(QStringLiteral("IDEdit"));

        horizontalLayout_2->addWidget(IDEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(AddStuDlg);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(70, 0));
        label_4->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(label_4);

        AgeSpinBox = new QSpinBox(AddStuDlg);
        AgeSpinBox->setObjectName(QStringLiteral("AgeSpinBox"));

        horizontalLayout_4->addWidget(AgeSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(AddStuDlg);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(70, 0));
        label_3->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(label_3);

        SexComboBox = new QComboBox(AddStuDlg);
        SexComboBox->setObjectName(QStringLiteral("SexComboBox"));

        horizontalLayout_3->addWidget(SexComboBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(AddStuDlg);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(70, 0));
        label_5->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_5->addWidget(label_5);

        AddressEdit = new QLineEdit(AddStuDlg);
        AddressEdit->setObjectName(QStringLiteral("AddressEdit"));

        horizontalLayout_5->addWidget(AddressEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(AddStuDlg);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(70, 0));
        label_6->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(label_6);

        PhoneEdit = new QLineEdit(AddStuDlg);
        PhoneEdit->setObjectName(QStringLiteral("PhoneEdit"));

        horizontalLayout_6->addWidget(PhoneEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(AddStuDlg);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(70, 0));
        label_7->setMaximumSize(QSize(70, 16777215));

        verticalLayout->addWidget(label_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_7->addLayout(verticalLayout);

        DescText = new QTextEdit(AddStuDlg);
        DescText->setObjectName(QStringLiteral("DescText"));

        horizontalLayout_7->addWidget(DescText);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(AddStuDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_8->addWidget(buttonBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_8);


        retranslateUi(AddStuDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddStuDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddStuDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddStuDlg);
    } // setupUi

    void retranslateUi(QDialog *AddStuDlg)
    {
        AddStuDlg->setWindowTitle(QApplication::translate("AddStuDlg", "Dialog", 0));
        label->setText(QApplication::translate("AddStuDlg", "\345\247\223\345\220\215:", 0));
        label_2->setText(QApplication::translate("AddStuDlg", "\345\255\246\345\217\267:", 0));
        label_4->setText(QApplication::translate("AddStuDlg", "\345\271\264\351\276\204:", 0));
        label_3->setText(QApplication::translate("AddStuDlg", "\346\200\247\345\210\253:", 0));
        SexComboBox->clear();
        SexComboBox->insertItems(0, QStringList()
         << QApplication::translate("AddStuDlg", "\347\224\267", 0)
         << QApplication::translate("AddStuDlg", "\345\245\263", 0)
        );
        label_5->setText(QApplication::translate("AddStuDlg", "\345\256\266\345\272\255\344\275\217\345\235\200:", 0));
        label_6->setText(QApplication::translate("AddStuDlg", "\350\201\224\347\263\273\347\224\265\350\257\235:", 0));
        label_7->setText(QApplication::translate("AddStuDlg", "\346\217\217\350\277\260:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddStuDlg: public Ui_AddStuDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTUDLG_H
