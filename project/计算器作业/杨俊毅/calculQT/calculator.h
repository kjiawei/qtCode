#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include<QButtonGroup>
#include<QDebug>
#include <QString>
namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
public slots:
    void button_group(int sig);
private slots:

    void cal_group(int sig);
    void on_pequal_clicked();

    void on_pclear_clicked();

private:
    Ui::Calculator *ui;
    QButtonGroup *group;
    QButtonGroup *calgroup;
};

#endif // CALCULATOR_H
