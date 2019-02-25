#ifndef BLUETOOTHLIGHT_H
#define BLUETOOTHLIGHT_H

#include <QWidget>

namespace Ui {
class BluetoothLight;
}

class BluetoothLight : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothLight(QWidget *parent = 0);
    ~BluetoothLight();

private slots:
    void on_toogleButton_clicked();

private:
    Ui::BluetoothLight *ui;
};

#endif // BLUETOOTHLIGHT_H
