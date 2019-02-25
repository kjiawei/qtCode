#include "datacenter.h"
#include "ui_datacenter.h"

//#include <QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTextEdit>

dataCenter::dataCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dataCenter)
{
    ui->setupUi(this);

    mainDb = QSqlDatabase::addDatabase("QSQLITE");
    mainDb.setDatabaseName(SQLDB_NAME);
    if(!mainDb.open())
    {
        qDebug()<<"open database failed!";
    }
//    QTextEdit display;
//    display.resize(500, 160);
//    display.show();

    //showDatabase();
    //openDatabase();   //选中数据库进行缓冲  预操作

}

dataCenter::~dataCenter()
{
    delete ui;
}

void dataCenter::on_createDatabase_clicked()
{
    //根据输入的名字来创建数据库
    ui->toastLabel->setText("123");//test
    //qDebug()<<"create database success!";
    //showDatabase();//show all databases
}

void dataCenter::on_createTable_clicked()//选中Item后调用
{
    ui->toastLabel->setText("");
#ifdef UNIX_MODEL
    ui->toastLabel->setText(QString::fromLocal8Bit("建表成功"));//乱码解决
#elif WIN_MODEL
    ui->toastLabel->setText("建表成功");
#endif

    QSqlQuery query;
    QString createTableSql = QString("create table %1(number int unique)").arg(
                                                        ui->tableEdit->text());
    query.exec(createTableSql);
    qDebug()<<"create table success!";
}

void dataCenter::on_insertData_clicked()
{
    ui->toastLabel->setText("插入成功");
    QSqlQuery query;
    QString insertTableSql = QString("insert into %1 values(%2)").arg(ui->tableEdit->text()).arg(ui->insertEdit->text());
    query.exec(insertTableSql);
    qDebug()<<"insert table success!";
}

void dataCenter::on_queryData_clicked()
{
    ui->toastLabel->setText("查询成功");
    ui->queryShow->clear();
    QString queryTableSql = QString("select * from %1").arg(ui->tableEdit->text());
    QSqlQuery query(queryTableSql);
    while(query.next())
    {
        ui->queryShow->addItem(query.value(1).toString());
    }
    qDebug()<<"query table success!";
}

bool dataCenter::openDatabase() //保持连接需提升为全局 read sql file or better?
{
//    mainDb = QSqlDatabase::addDatabase("QSQLITE", SQLDB_NAME);
//    mainDb.setDatabaseName(SQLDB_NAME);
//    isOpenDatabaseSuccess = mainDb.open();
//    if(isOpenDatabaseSuccess == false)
//    {
//        qDebug()<<"open failed!";
//    }else{
        //QSqlQuery query = QSqlQuery(mainDb);
        //QString queryTableSql = QString("select * from table _userInfo");
//        query.exec(queryTableSql);
//        while(query.next())
//        {
//            qDebug()<<"1-";
//            ui->queryShow->addItem(query.value(0).toString());
//        }
//                    int numRow = 0;
//                    //检查数据库驱动的完备性，查询结果影响到的行数
//                    if(mainDb.driver()->hasFeature(QSqlDriver::QuerySize))
//                    {
//                        numRow = query.size();//将影响到的行数记录下来
//                    }
//                    else
//                    {
//                        //不支持，定位到记录的最后一行
//                        query.last();
//                        numRow = query.at() + 1;
//                        query.seek(-1);

//                    }
//                    QString id,name;
//                    display.append("=============================");
//                    while(query.next()) //将结果循环记录下来，定位来下一条记录
//                    {
//                        id = query.value(0).toString();//第一列值
//                        name = query.value(1).toString();//第二例值
//                        QString result = id + "   " + name;
//                        display.append(result);
//                    }
//                    display.append("=============================");
//                    //打印总行数
//                    display.append(QString("totall %1 rows").arg(numRow));
    //}
}

bool dataCenter::closeDatabase()
{
    if(mainDb.open())
    {
        mainDb.close();
    }
}

void dataCenter::showDatabase()
{
    //how to show in the listWidgets
    //ui->showAllDatabase  可选中某个进行操作
    ui->toastLabel->setText("current database selected"); //选中数据库进行下步操作
    //    QSqlQuery query;
    //    QString showAllDatabaseSql = QString(".tables");
    //    query.exec(showAllDatabaseSql);
}

bool dataCenter::dropDatabase()
{

}

void dataCenter::deleteDatabase()
{

}

void dataCenter::showAllTables()
{
    if(mainDb.open())
    {
        ui->showAllTables->clear();
        QStringList mainDbTables = mainDb.tables();
        QStringListIterator tableIter(mainDbTables);
        while(tableIter.hasNext()){
            QString tableName = tableIter.next();
            qDebug()<<tableName;
            ui->showAllTables->addItem(tableName);
        }
    }else{
        qDebug()<<"open database failed!";
        //return 0;
    }
//    QString showAllTablesSql = QString("select * from _userInfo");//selected database直接显示所有字段
//    QSqlQuery query(showAllTablesSql);
//    //query.exec(query);
//    while(query.next())
//    {
//        ui->showAllTables->addItem(query.value(0).toString());
//    }
//    qDebug()<<"query all tables success!";
}

bool dataCenter::deleteTables()
{

}

bool dataCenter::showAllColumn(QString tableName)//控件绑定属性方法 还是事件调用呢
{
    QSqlQuery query;//ctrl + i格式化代码
    QString strTableNmae = tableName;
    QString str = "PRAGMA table_info(" + strTableNmae + ")";

    query.prepare(str);
    if (query.exec())
    {
        while (query.next())
        {
            qDebug() << QString("字段数:%1   字段名:%2   字段类型:%3").arg(
                            query.value(0).toString()).arg(
                            query.value(1).toString()).arg(
                            query.value(2).toString());
        }
    }
    else
    {
        qDebug() << query.lastError();
        return false;
    }
}

void dataCenter::on_pushButton_clicked()
{
    //openDatabase();函数退出会断掉连接
    //showAllTables();
    showAllColumn("people");
}

void dataCenter::on_queryShow_itemClicked(QListWidgetItem *item)//点击选中Item
{
    QString itemText = QString(item->text());
    qDebug()<<itemText;//未能正确输出文字
}

void dataCenter::on_showAllTables_itemClicked(QListWidgetItem *item)
{
    //根据传回的item值来执行查表操作

}
