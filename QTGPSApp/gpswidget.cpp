#include "gpswidget.h"
#include "ui_gpswidget.h"
#include<QSerialPortInfo>
#include<QDebug>
GPSWidget::GPSWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPSWidget)
{
    ui->setupUi(this);
    startInit();
    ui->statusBar->setText(tr("串口关闭"));
}

GPSWidget::~GPSWidget()
{
    delete ui;
}

void GPSWidget::startInit() //初始化打开和关闭按钮以及实例化定时器并建立信号和槽关联
{
ui->StartGPSbtn->setEnabled(true);
ui->StopGPSbtn->setEnabled(false);
timerdly=TIMER_INTERVAL; //初始化读取定时器计时间隔
readTimer=new QTimer(this);
connect(readTimer, SIGNAL(timeout()), this, SLOT(readGpsData()));
}

void GPSWidget::setComboBoxEnabled(bool status) //设置ComboBox的可用性
{
 ui->portNameComboBoxGPS->setEnabled(status);
 ui->baudRateComboBoxGPS->setEnabled(status);
 ui->dataBitsComboBoxGPS->setEnabled(status);
 ui->parityComboBoxGPS->setEnabled(status);
 ui->stopBitsComboBoxGPS->setEnabled(status);

}
void GPSWidget::on_StartGPSbtn_clicked()
{

    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();




QString portName= info.portName(); //"/dev"+ui->portNameComboBoxGPS->currentText(); //获取串口名

myGpsCom = new Posix_QextSerialPort(portName, QextSerialBase::Polling);
}
//这里QextSerialBase::QueryMode应该使用QextSerialBase::Polling
if(myGpsCom->open(QIODevice::ReadOnly))
    {
    ui->statusBar->setText(tr("串口打开成功"));
}else{
    ui->statusBar->setText(tr("串口打开失败"));
    return;
}
//设置波特率
myGpsCom->setBaudRate((BaudRateType)ui->baudRateComboBoxGPS->currentIndex());
//设置数据位
myGpsCom->setDataBits((DataBitsType)ui->dataBitsComboBoxGPS->currentIndex());
//设置校验
myGpsCom->setParity((ParityType)ui->parityComboBoxGPS->currentIndex());
//设置停止位
myGpsCom->setStopBits((StopBitsType)ui->stopBitsComboBoxGPS->currentIndex());
//设置数据流控制
myGpsCom->setFlowControl(FLOW_OFF);
//设置延时
myGpsCom->setTimeout(TIME_OUT);
setComboBoxEnabled(false);
readTimer->start(TIMER_INTERVAL);
ui->StartGPSbtn->setEnabled(false);
ui->StopGPSbtn->setEnabled(true);

}


void GPSWidget::readGpsData() // 定时读取GPS数据方法
{
   QByteArray GPS_Data = myGpsCom->readAll();
   if(!GPS_Data.isEmpty())
       {
       ui->textEditGPSData->append(GPS_Data);
       if(GPS_Data.contains("$GPRMC"))//读取RMC语句
           {
           GPS_Data.remove(0, GPS_Data.indexOf("$GPRMC"));
           if(GPS_Data.contains("*"))
               {
               GPS_RMC=GPS_Data.left(GPS_Data.indexOf("*"));
               //获得$GPRMC句子的定位信息
               Gps_list.clear();
               Gps_list<<GPS_RMC.split(',');
               //提取分隔符之间的信息，存入容器列表
               GpsDisplay();
           }
       }
   }
}
void GPSWidget::GpsDisplay()
{
    QString alt_str; //altitude value
    QString lon_str; //longtitude value
    QString u_date; //utc date value
    QString u_time; //utc time value
    ui->altitudedisplay->setText(alt_position(alt_str));
    ui->longtitudedisplay->setText(lon_position(lon_str));
    ui->speeddisplay->setText(Gps_list[7]);
    ui->datedisplay->setText(UTCdate(u_date));
    ui->timedisplay->setText(UTCtime(u_time));
    if(Gps_list[2].contains("A"))
        ui->statusdisplay->setText(tr("GPS 运行中"));
    else
        ui->statusdisplay->setText(tr("GPS 无信号"));
}
QString& GPSWidget::alt_position(QString& alt_str)
{
    alt_str.clear();
    QByteArray altitude = Gps_list[3];
    float SecNum = altitude.mid(5, 4).toInt()*60/10000;
    QString str=QString::number(SecNum);
    if(Gps_list[4]=="N")
        {
        alt_str=tr("北纬")+altitude.mid(0, 2)+tr("度")
                +altitude.mid(2, 2)+tr("分")
                +str.mid(0, 2)+tr("秒");//纬度方向
    }
    else
        {
        alt_str=tr("南维")+altitude.mid(0, 2)+tr("度")
                +altitude.mid(2, 2)+tr("分")
                +str.mid(0, 2)+tr("秒");//纬度方向
    }
    return alt_str;
}

QString& GPSWidget::lon_position(QString& lon_str)
{
    lon_str.clear();
    QByteArray longtitude = Gps_list[5];
    float SecNum = longtitude.mid(6, 4).toInt()*60/10000;
    QString str=QString::number(SecNum);
    if(Gps_list[6]=="W")
        {
        lon_str=tr("西经")+longtitude.mid(0, 3)+tr("度")
                 +longtitude.mid(3,2)+tr("分")
                 +str.mid(0, 2)+tr("秒"); //经度方向
        }
    else
        {
        lon_str=tr("东经")+longtitude.mid(0, 3)+tr("度")
                +longtitude.mid(3, 2)+tr("分")
                +str.mid(0, 2)+tr("秒");//经度方向
    }
    return lon_str;
}
QString& GPSWidget::UTCdate(QString& u_date)
{
    u_date.clear();
    QByteArray Udate=Gps_list[9];
    u_date="20"+Udate.mid(4,2)+tr("年")
            +Udate.mid(2, 2)+tr("月")
            +Udate.mid(0, 2)+tr("日");
    return u_date;
}
QString& GPSWidget::UTCtime(QString& u_time)
{
    u_time.clear();
    QByteArray Utime = Gps_list[1];
    u_time=QString::number((Utime.mid(0, 2).toInt())+8)+":"//小时
            +Utime.mid(2, 2)+":"//分
            +Utime.mid(4, 2);//秒
    return u_time;
}


void GPSWidget::on_StopGPSbtn_clicked()
{
myGpsCom->close();
delete myGpsCom;
readTimer->stop();
ui->statusBar->setText(tr("串口关闭"));
setComboBoxEnabled(true);
ui->StartGPSbtn->setEnabled(true);
ui->StopGPSbtn->setEnabled(false);
}
