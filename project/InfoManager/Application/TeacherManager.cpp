#include "TeacherManager.h"
#include "ui_teachermanager.h"

TeacherManager::TeacherManager(QWidget *parent) : QWidget(parent), ui(new Ui::TeacherManager)
{
    ui->setupUi(this);
}

TeacherManager::~TeacherManager()
{
    delete ui;
}
