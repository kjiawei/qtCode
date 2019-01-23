#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
//数据操作类
//连接不同数据库 运用事务机制 多并发

class dataManage
{
public:
    dataManage();

    void initDatabase();
    void openDatabase();//事务机制
    void chooseDatabase();
    void closeDatabase();
    void createTable();//创建表格
    void queryData(QString querySQL);//需要一个泛型参数-模板
    void deleteData();//删除
    void insertData();//插入
    void updateData();//更新

private:
    QSqlDatabase database;
    QSqlQuery sql_query;
};

#endif // DATAMANAGE_H
