#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "StuManager.h"
#include "TeacherManager.h"
#include "../CreateDB/createdb.h"
#include "addstudlg.h"


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum OperateType
    {
        Add ,
        Edit
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onBtnAdd();

    void onBtnEdit();

    void onBtnDel();

    void onBtnRefresh();

    void ExecAddSql(QVariantMap stuInfo);

    void ExecEditSql(QVariantMap stuInfo);

    void ExecDelSql(QString id);

private:
    void initUi();

    void setTabCornerBtn();

    void initAddDlg();

private:
    Ui::MainWindow *ui;
    QTabWidget *m_pTabWidget;

    StuManager *m_pTableWidget;
    TeacherManager *m_pTeacherManager;

    CreateDb *m_pCreateDb;
    AddStuDlg* m_pAddStuDlg;

    OperateType m_operateType;
};

#endif // MAINWINDOW_H
