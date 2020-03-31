#include "login.h"
#include "ui_login.h"
#include<QSqlDatabase>
#include"drawer.h"
#include<QDebug>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<login.h>
#include<QSqlQuery>
#pragma execution_character_set("utf-8")//设置中文= =
bool opendatabase();
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    opendatabase();//QQ765715928
}

login::~login()
{
    delete ui;
}
bool opendatabase()
{
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
  //  mydb.setDatabaseName("F:\\chat.db");
    mydb.setDatabaseName("chat.db");
    if(mydb.open())
    {

        qDebug()<<"open success";

        QSqlQuery query;
        query.exec("select * from user");
        while(query.next())
        {
            qDebug()<<query.value(0).toString()<":"<<query.value(1).toString()<":"<<query.value(2).toString();
        }
        return true;
    }
    else
    {
        qDebug()<<"open failed";
        return false;
    }
}

void login::on_pushButton_exit_clicked()
{
    close();
}

void login::on_pushButton_login_clicked()
{
    QString name=ui->lineEdit_name->text();
    QString password=ui->lineEdit_password->text();
    QString sqlName,sqlPassword;
    QSqlQueryModel *model=new QSqlQueryModel;
    sqlName="select count(*) from user where name='"+name+"'";
    model->setQuery(sqlName);
    QString nameresult,passwordresult;
    QModelIndex index1=model->index(0,0);
    sqlPassword="select password from user where name='"+name+"'";
    model->setQuery(sqlPassword);
    QModelIndex index2=model->index(0,0);

    if(index1.data()==0||index2.data()!=password)
    {
        QMessageBox::about(NULL,"提示","用户名或密码错误");
    }
    else if(index1.data()!=0&&index2.data()==password)
    {
        QMessageBox::about(NULL,"提示","登陆成功");
        Drawer Draw;
        if(name=="djy")
        {
            Draw.showChatWidget1();
        }
        else if(name=="zyj")
        {
            Draw.showChatWidget2();
        }
        else if(name=="pig")
        {
            Draw.showChatWidget3();
        }
        else if(name=="a")
        {
            Draw.showChatWidget4();
        }
        else if(name=="ashen")
        {
            Draw.showChatWidget5();
        }
        else if(name=="zzz")
        {
            Draw.showChatWidget6();

        }
        else if(name=="fanchen")
        {
            Draw.showChatWidget7();
        }
        else if(name=="Admin")
        {
            adm=new admin;
            adm->show();
        }
    }
    qDebug()<<index1.data();
}
