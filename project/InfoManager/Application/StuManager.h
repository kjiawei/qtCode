#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

namespace Ui {
class StuManager;
}

class StuManager : public QWidget
{
    Q_OBJECT

public:
    explicit StuManager(QWidget *parent = 0);
    ~StuManager();

    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();

private:
    Ui::StuManager *ui;
};

#endif // TABLEWIDGET_H
