#include "bluetoothlight.h"
#include "ui_bluetoothlight.h"

BluetoothLight::BluetoothLight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothLight)
{
    ui->setupUi(this);
}

BluetoothLight::~BluetoothLight()
{
    delete ui;
}

void BluetoothLight::on_toogleButton_clicked()
{

}
