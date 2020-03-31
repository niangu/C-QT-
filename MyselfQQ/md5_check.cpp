#include "md5_check.h"
#include "ui_md5_check.h"
#include <QCryptographicHash>
#include <QByteArray>
#include<QDebug>
#include <QFileDialog>
#include<QMessageBox>
#include <QFileInfo>
#include<QClipboard>
#include <QFile>
#pragma execution_character_set("utf-8")//设置中文= =
MD5_check::MD5_check(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MD5_check)
{
    ui->setupUi(this);
}

MD5_check::~MD5_check()
{
    delete ui;
}

void MD5_check::on_pushButton_clicked()
{
    close();
}

void MD5_check::on_pushButton_createMD5_clicked()
{
    QString input=ui->lineEdit_input->text();
    QString result;
    QCryptographicHash md(QCryptographicHash::Md5);
    QString md5;
    QByteArray bb,cc;
    cc=input.toLatin1();//转String
    bb = QCryptographicHash::hash(cc,QCryptographicHash::Md5 );
    result=bb.toHex();//转换存储方式
    md5.append(result);

//QQ765715928

    //result=md5.MD5(input);
    //ui->lineEdit_result->setText(result);
    ui->lineEdit_result->setText(md5);
    QClipboard *clip=QApplication::clipboard();
    QString originaltext=clip->text();
    clip->setText(md5);
    qDebug()<<md5;
    qDebug()<<bb;
    MyMD5="MD5:"+md5;
    qDebug()<<MyMD5;
}

void MD5_check::on_pushButton_createMD5ofFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
            tr("选择要计算的文件"),
            "",
            "",
         0);
    ui->lineEdit_input->setText(filename);
    QString path=ui->lineEdit_input->text();
    QFile *myfile=new QFile(path);
    myfile->open(QIODevice::ReadOnly);
    QCryptographicHash md(QCryptographicHash::Md5);
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash(myfile->readAll(),QCryptographicHash::Md5 );

    md5.append(bb.toHex());
    md5.toStdString();
    myfile->close();
    ui->lineEdit_result_file->setText(md5);
    QClipboard *clip=QApplication::clipboard();
    QString originaltext=clip->text();
    clip->setText(md5);
    MyMD5="MD5:"+md5;
    qDebug()<<MyMD5;
}

void MD5_check::on_pushButton_check_clicked()
{
    QString a,b;
    a=ui->lineEdit_result->text();
    b=ui->lineEdit_result_file->text();
    QString check;
    check=ui->lineEdit_result_check->text();
    QString combobox;
    combobox=ui->comboBox_check->currentText();
    if(combobox=="字段")
    {
        if(a==check)
        {
            QMessageBox::about(NULL,"提示","校验完整性成功");

        }
        else
        {
            QMessageBox::about(NULL,"提示","校验完整性失败，MD5不符合");
        }
    }
    else if(combobox=="文件")
    {
        if(b==check)
        {
            QMessageBox::about(NULL,"提示","校验完整性成功");

        }
        else
        {
            QMessageBox::about(NULL,"提示","校验完整性失败，MD5不符合");
        }
    }
}
