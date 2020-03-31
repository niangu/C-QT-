#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include<QSqlDatabase>
bool opendatabase();
int main(int argc, char *argv[])
{
    opendatabase();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();//QQ765715928

    return a.exec();
}
bool opendatabase()
{
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");

    mydb.setDatabaseName("D:\\sqlite\\student.db");//平时debug正常用
    //mydb.setDatabaseName("./student.db");//release用
    if(mydb.open())
    {
        qDebug()<<"open success";
        return true;
    }
    else
    {
        qDebug()<<"open failed";
        return false;
    }
}
