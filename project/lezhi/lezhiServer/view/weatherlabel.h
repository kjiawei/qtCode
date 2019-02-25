#ifndef WEATHERLABEL_H
#define WEATHERLABEL_H

#include <QWidget>

class _Weather//天气数据类,与其他类名不冲突就可以了
{
public:
    QString fx;
    QString fengli;
    QString tianqi;
    QString gaowen;
    QString diwen;
    QString riqi;
};

namespace Ui {
class weatherLabel;
}

class weatherLabel : public QWidget
{
    Q_OBJECT

public:
    explicit weatherLabel(QWidget *parent = 0);
    ~weatherLabel();
    void setWeather(const _Weather &weather);

private:
    Ui::weatherLabel *ui;
};

#endif // WEATHERLABEL_H
