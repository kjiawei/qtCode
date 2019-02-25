#include "addstudlg.h"
#include "ui_addstudlg.h"
#include <QDateTime>
#include <QStringList>
#include <QString>

AddStuDlg::AddStuDlg(QWidget *parent) :QDialog(parent),ui(new Ui::AddStuDlg)
{
    ui->setupUi(this);
}

AddStuDlg::~AddStuDlg()
{
    delete ui;
}

void AddStuDlg::setEditData(QStringList rowData)
{
    ui->NameEdit->setText(rowData.at(0));
    ui->IDEdit->setText(rowData.at(1));
    ui->AgeSpinBox->setValue(rowData.at(3).toInt());
    ui->SexComboBox->setCurrentText(rowData.at(2));
    ui->AddressEdit->setText(rowData.at(4));
    ui->PhoneEdit->setText(rowData.at(5));
    ui->DescText->setText(rowData.at(6));

    ui->IDEdit->setEnabled(false);
}

void AddStuDlg::clearData()
{
    ui->NameEdit->clear();
    ui->IDEdit->clear();
    ui->AgeSpinBox->cleanText();
    //ui->SexComboBox->clear();
    ui->AddressEdit->clear();
    ui->PhoneEdit->clear();
    ui->DescText->clear();
}

void AddStuDlg::on_buttonBox_accepted()
{
    QVariantMap stuInfo;

    QString name = ui->NameEdit->text();
    QString number = ui->IDEdit->text();
    QString age = ui->AgeSpinBox->text();
    QString sex = ui->SexComboBox->currentText();
    QString address = ui->AddressEdit->text();
    QString phone = ui->PhoneEdit->text();
    QString desc = ui->DescText->toPlainText();

    QString datetime = QDateTime::currentDateTime().toString();

    stuInfo.insert("datetime" ,datetime );
    stuInfo.insert("name" ,name );
    stuInfo.insert("number" ,number );
    stuInfo.insert("age" ,age );
    stuInfo.insert("sex" ,sex );
    stuInfo.insert("address" ,address );
    stuInfo.insert("phone" ,phone );
    stuInfo.insert("desc" ,desc );

    emit signalStuInfo(stuInfo);

    clearData(); //清除编辑的数据
    ui->IDEdit->setEnabled(true);
}

void AddStuDlg::on_buttonBox_rejected()
{
    close();
    ui->IDEdit->setEnabled(true);
}
