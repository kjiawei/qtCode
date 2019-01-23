#include "datamanage.h"

#include <QtSql/QSqlDatabase> //实现了数据库连接的操作
#include <QtSql/QSqlQuery>    //执行SQL语句
#include <QtSql/QSqlRecord>   //类封装数据库所有记录
#include <QtSql/QSqlError>
#include <QTime>
#include <QDebug>

dataManage::dataManage()
{


}

//建立数据库
void dataManage::initDatabase(){
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");//第二个参数已省,若使用自定义名称则需要加上
        database.setDatabaseName("myDatabase.db");//不存在则创建
        //database.setUserName("XingYeZhiXia");//免费版Sqlite不带加密功能,需要去添加加密功能
        //database.setPassword("123456");
    }
}

void dataManage::openDatabase(){
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }
}

void dataManage::createTable(){
    QString create_sql = "create table student (id int primary key, name varchar(30), age int)";
    sql_query.prepare(create_sql);
    //sql_query.exec("create table student (id int primary key, name varchar(30), age int)");
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

void dataManage::insertData(){
    QString insert_sql = "insert into student values (?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(5+1);//max_id
    sql_query.addBindValue("Wang");
    sql_query.addBindValue(25);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Wang!";
    }
    if(!sql_query.exec("INSERT INTO student VALUES(3, \"Li\", 23)"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Li!";
    }
}

void dataManage::updateData(){
    QString update_sql = "update student set name = :name where id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name", "Qt");
    sql_query.bindValue(":id", 1);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "updated!";
    }
}

void dataManage::queryData(QString querySQL){
    //query part:"select id, name from student"
    //query all:"select * from student"
    QString select_sql = querySQL;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            qDebug()<<QString("id:%1    name:%2").arg(id).arg(name);
        }
    }

    QString select_all_sql = querySQL;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            int age = sql_query.value(2).toInt();
            qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
        }
    }
}

void dataManage::closeDatabase(){
    database.close();
}
