#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLibrary>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUi();

    initAddDlg();

    setTabCornerBtn();

    m_pCreateDb = new CreateDb;

    m_pCreateDb->initDB();  //打开数据库

    onBtnRefresh(); //程序启动时，查询数据

    showMaximized();

    m_operateType = Add;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnAdd()
{
    qDebug()<<"onBtnAdd";

    m_operateType = Add;

    m_pAddStuDlg->activateWindow();
    m_pAddStuDlg->setWindowTitle(tr("添加: 学生信息"));
    m_pAddStuDlg->exec();

}

void MainWindow::onBtnEdit()
{
    qDebug()<<"onBtnEdit";

    m_operateType = Edit;

    QStringList rowData ;
    rowData = m_pTableWidget->getCurrentRowData();
    if(rowData.isEmpty())
    {
        QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
        return ;
    }
    else
    {
        m_pAddStuDlg->setEditData(rowData);
    }

    m_pAddStuDlg->activateWindow();
    m_pAddStuDlg->setWindowTitle(tr("修改: 学生信息"));
    m_pAddStuDlg->exec();
}

void MainWindow::onBtnDel()
{
    qDebug()<<"onBtnDel";
    QString ID = m_pTableWidget->getCurrentID();
    if(ID.isEmpty())
    {
        QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
        return ;
    }

    QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
    if(button == QMessageBox::Yes)
    {
        //删除操作
        ExecDelSql(ID);
    }
}

void MainWindow::onBtnRefresh()
{
    qDebug()<<"onBtnRefresh";
    QList<QStringList> tableData;

    tableData = m_pCreateDb->selectDataFromBase();
    if(!tableData.isEmpty())
    {
        m_pTableWidget->clearTableData();
        QListIterator<QStringList> itr(tableData);
        while(itr.hasNext())
        {
            m_pTableWidget->appendRowData(itr.next());
        }
    }
}

void MainWindow::ExecAddSql(QVariantMap stuInfo)
{
    if(m_operateType == Add)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString id = stuInfo.value("number").toString();
        QString name = stuInfo.value("name").toString();
        QString sex = stuInfo.value("sex").toString();
        QString age = stuInfo.value("age").toString();
        QString address = stuInfo.value("address").toString();
        QString phone = stuInfo.value("phone").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("insert into StuManager (create_date,id ,name ,sex ,age ,address , phone ,description)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8')")
                .arg(create_date).arg(id).arg(name).arg(sex).arg(age).arg(address).arg(phone).arg(description);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            QStringList rowData;
            rowData << name <<id <<sex <<age << address <<phone << description ;
            m_pTableWidget->appendRowData(rowData);

            QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
        }
    }
}

void MainWindow::ExecEditSql(QVariantMap stuInfo)
{
    if(m_operateType == Edit)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString id = stuInfo.value("number").toString();
        QString name = stuInfo.value("name").toString();
        QString sex = stuInfo.value("sex").toString();
        QString age = stuInfo.value("age").toString();
        QString address = stuInfo.value("address").toString();
        QString phone = stuInfo.value("phone").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("UPDATE StuManager "
                      "set create_date = '%0' ,id = '%2' ,name = '%3',"
                      "sex = '%4',age = '%5',address = '%6', phone = '%7',description = '%8'"
                      " where id = '%9' ")
                .arg(create_date).arg(id).arg(name).arg(sex).arg(age).arg(address).arg(phone).arg(description).arg(id);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            onBtnRefresh(); //重新加载数据
            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }
    }
}

void MainWindow::ExecDelSql(QString id)
{
    QString sql;
    sql = QString("DELETE FROM StuManager "
                  " where id = '%9' ").arg(id);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        onBtnRefresh(); //重新加载数据
        QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
    }
}

void MainWindow::initUi()
{
    m_pTableWidget = new StuManager;
    m_pTeacherManager = new TeacherManager;

    m_pTabWidget = new QTabWidget(this);

    m_pTabWidget->addTab(m_pTableWidget , tr("学生管理"));
    m_pTabWidget->addTab(m_pTeacherManager ,tr("教师管理"));

    setStyleSheet("QTabBar::tab{min-width:30ex; min-height:10ex;}");

    setCentralWidget(m_pTabWidget);
    setContentsMargins(5 , 25, 5 ,5);
}

void MainWindow::setTabCornerBtn()
{
    QPushButton *btnRefresh = new QPushButton;
    btnRefresh->setText(tr("刷新"));

    QPushButton *btnAdd = new QPushButton;
    btnAdd->setText(tr("添加"));

    QPushButton *btnEdit = new QPushButton;
    btnEdit->setText(tr("编辑"));

    QPushButton *btnDel = new QPushButton;
    btnDel->setText(tr("删除"));

    QWidget *widget = new QWidget;
    widget->setMinimumSize(20 ,55);
    widget->setContentsMargins(0,0,0,10);

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->addWidget(btnRefresh);
    hLayout->addWidget(btnAdd);
    hLayout->addWidget(btnEdit);
    hLayout->addWidget(btnDel);

    widget->setLayout(hLayout);
    m_pTabWidget->setCornerWidget(widget ,Qt::TopRightCorner);

    connect(btnRefresh , SIGNAL(clicked(bool)) , this ,SLOT(onBtnRefresh()));
    connect(btnAdd , SIGNAL(clicked(bool)) , this ,SLOT(onBtnAdd()));
    connect(btnEdit , SIGNAL(clicked(bool)), this ,SLOT(onBtnEdit()));
    connect(btnDel , SIGNAL(clicked(bool)) ,this , SLOT(onBtnDel()));
}

void MainWindow::initAddDlg()
{
    m_pAddStuDlg = new AddStuDlg;
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecAddSql(QVariantMap)));
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecEditSql(QVariantMap)));

}
