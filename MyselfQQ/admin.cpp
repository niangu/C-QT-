#include "admin.h"
#include "ui_admin.h"
#include<QSqlQueryModel>
#pragma execution_character_set("utf-8")//设置中文= =
admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    init();
}

admin::~admin()
{
    delete ui;
}
void admin::init()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString a;
    a="select name as 用户名, password as 密码 from user";
    model->setQuery(a);
    ui->tableView->setModel(model);
}

void admin::on_pushButton_clicked()
{
    close();
}
