#ifndef DATACENTER_H
#define DATACENTER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QListWidget>
#include <QListWidgetItem>

//sql database
//file operation
//system

#define SQLDB_NAME "C:\\sqlite3\\family.db"  // data/smartHome

//平台编译  pro文件里判断以调用哪个
//#define UNIX_MODEL 1
#define WIN_MODEL  2

namespace Ui {
class dataCenter;
}

class dataCenter : public QWidget
{
    Q_OBJECT

public:
    explicit dataCenter(QWidget *parent = 0);
    ~dataCenter();

private slots:
    void on_createDatabase_clicked();
    void on_createTable_clicked();
    void on_insertData_clicked();
    void on_queryData_clicked();
    void on_pushButton_clicked();
    void on_queryShow_itemClicked(QListWidgetItem *item);

    void on_showAllTables_itemClicked(QListWidgetItem *item);

private:
    Ui::dataCenter *ui;
    QSqlDatabase mainDb;
    QListWidgetItem *tmpItem;
    bool isOpenDatabaseSuccess;

    //数据库操作 优化话题
    bool createDatabase();
    bool openDatabase();
    bool closeDatabase();
    void showDatabase();//显示数据库 可以多个
    bool dropDatabase();//备份数据库
    bool analyzerDatabase();//分析数据库(拆分组合等操作)
    void deleteDatabase();

    void showAllTables();
    bool deleteTables();
    bool showAllColumn(QString tableName);
    bool readDatabase();

    //数据处理  树-双向链表

    //数据逻辑(返回 拉取)

    //运行记录(新建数据库 并进行插表操作)
};

#endif // DATACENTER_H
