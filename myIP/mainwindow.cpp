#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QDebug>
#include<QDnsLookup>
#include<QDnsServiceRecord>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //获取主机名称
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    //获取与主机名相关的ip地址，一般第一个是本机设定的ip地址（可以在“Internet协议(TCP/IP)”中手动指定）
    qDebug()<<"localHostName:"<<localHostName<<endl<<"IP Address:"<<info.addresses();
    //还可能出现IPv4和IPv6俩种地址，可以对IP地址列表进行遍历
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug()<<"IPv4遍历"<<address.toString();
        if(address.protocol() == QAbstractSocket::IPv6Protocol)
            qDebug()<<"IPv6遍历"<<address.toString();
    }

 //第二种方法
    QHostInfo::lookupHost("www.baidu.com",this,SLOT(lookedUp(QHostInfo)));//查找工作在其他线程中进行，既异步进行
//方法三
    //获取所有网络接口的列表
    QList<QNetworkInterface>list=QNetworkInterface::allInterfaces();
    //遍历每一个网络接口
    foreach(QNetworkInterface interface,list)
    {
        //接口名称
        qDebug()<<"Name:"<<interface.name();
        //硬件地址
        qDebug()<<"HardwareAddress:"<<interface.hardwareAddress();
        //获取Ip地址条目列表，每个条目包含一个IP地址，子网掩码和广播地址
        QList<QNetworkAddressEntry>entryList=interface.addressEntries();
        //遍历每一个IP地址条目
        foreach(QNetworkAddressEntry entry,entryList)
        {
            //IP地址
            qDebug()<<"IP Address:"<<entry.ip().toString();
            //子网掩码
            qDebug()<<"Netmask:"<<entry.netmask().toString();
            //广播地址
            qDebug()<<"Broadcast:"<<entry.broadcast().toString();
        }
    }
    //qt5中引入了一个QDnsLookup类来进行Dns查询
    dns = new QDnsLookup(this);
    connect(dns,SIGNAL(finished()),this, SLOT(handleServers()));
    dns->setType(QDnsLookup::SRV);
    dns->setName("_xmpp-client._tcp.gmail.com");
    dns->lookup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleServers()
{
    if(dns->error()!=QDnsLookup::NoError)
    {
        qWarning("DNS lookup failed");
        dns->deleteLater();
        return;
    }
    //foreach(const QDnsServiceRecord &record,dns->serviceRecords())
    //{
        //处理结果

    //}
    dns->deleteLater();
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if(host.error()!=QHostInfo::NoError)
    {
        qDebug()<<"Lookup failed:"<<host.errorString();
        return;
    }
    foreach(const QHostAddress &address,host.addresses())
        qDebug()<<"Found address:"<<address.toString();
}
