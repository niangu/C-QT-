#include "qtrsa.h"
#include "ui_qtrsa.h"
#include"rsa.h"

QtRSA::QtRSA(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtRSA)
{
    ui->setupUi(this);
}

QtRSA::~QtRSA()
{
    delete ui;
}

void QtRSA::on_pushButton_jiami_clicked()
{
    QString a=ui->lineEdit_input->text();
    Initialize(a);//cin>>a;
    while(!e)
    {
        RSA_Initialize();
    }
    RSA_Encrypt();
    a="";
    for(int i = 0; i<1024 && Ciphertext[i]!=0 ; i++)
    {
        a+=QString::number(Ciphertext[i]);//1+2=12 102 12
        //qDebug()<<"result a="<<a;
        //qDebug()<<"result Ciper ="<<Ciphertext[i];
    }
    ui->lineEdit_result->setText(a);
    ui->lineEdit_e->setText(QString::number(e));
    ui->lineEdit_d->setText(QString::number(d));
    ui->lineEdit_n->setText(QString::number(n));
    QString e,d,n;
    e=ui->lineEdit_e->text();
    d=ui->lineEdit_d->text();
    n=ui->lineEdit_n->text();

    word="公钥:e="+e+"  n="+n;

}

void QtRSA::on_pushButton_jiemi_clicked()
{
    QString b=ui->lineEdit_result->text();
    ui->lineEdit_input->setText(b);
    RSA_Decrypt();
    QString a="";
    //for(int i = 0; i<1024 && Ciphertext[i]!=0 ; i++)
    for(int i=1023;i>=0;i--)
    {
        if(Ciphertext[i]!=0)
        {
            a+=QString::number(Ciphertext[i]);
            //qDebug()<<a;
            //qDebug()<<Ciphertext[i];
        }
        else
        {
            a+="";
        }
    }
    ui->lineEdit_result->setText(a);
}

void QtRSA::on_pushButton_exit_clicked()
{
    close();
}

