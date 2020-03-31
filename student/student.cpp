#include "student.h"
#include "ui_student.h"
#include<QDebug>
#include<QSqlQueryModel>
#pragma execution_character_set("utf-8")//设置中文= =
student::student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    init();
}

student::~student()
{
    delete ui;
}

void student::on_pushButton_clicked()
{
    close();
}
void student::init()
{
    qDebug()<<stuName;//=0
    QString sql_stu;
    sql_stu="select name as 姓名 ,number as 学号,class as 专业 ,EnterTime as 年级, GPA as 绩点,password as 密码  from student where name='"+stuName+"'";
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_stu);
    ui->tableView->setModel(modelx);
}
