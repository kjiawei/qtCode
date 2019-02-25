#include "createdb.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

CreateDb::CreateDb()
{

}

void CreateDb::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("HostName.db");
    db.setDatabaseName("DatabaseName");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";

//        QSqlQuery query;
//        query.exec("create table StuManager (create_date datetime, "
//                   "id varchar(20)  primary key, name varchar(20) ,"
//                   " sex varchar(20) ,age INTEGER ,"
//                   "address varchar(20) , phone varchar(12) , description varchar(50))");


    }
    else
    {
        qDebug()<<db.databaseName();
    }
}

QList<QStringList> CreateDb::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM StuManager");

    QList<QStringList> stuInfo;


    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(2).toString();
        rowData <<query.value(1).toString();
        rowData <<query.value(3).toString();
        rowData <<query.value(4).toString();
        rowData <<query.value(5).toString();
        rowData <<query.value(6).toString();
        rowData <<query.value(7).toString();
        rowData <<query.value(8).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}

