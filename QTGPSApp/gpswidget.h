#ifndef GPSWIDGET_H
#define GPSWIDGET_H

#include <QWidget>

#include"posix_qextserialport.h"
#include<QMessageBox>
#include<QTimer>
#define TIME_OUT 10 //延时,TIME_OUT是串口读写的延时
#define TIMER_INTERVAL 200  //读取定时器计时间隔,200ms


namespace Ui {
class GPSWidget;
}

class GPSWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GPSWidget(QWidget *parent = nullptr);
    ~GPSWidget();

private slots:
    void on_StartGPSbtn_clicked();

    void on_StopGPSbtn_clicked();
    void readGpsData();  //定时读取GPS设备串口数据

private:
    Ui::GPSWidget *ui;
    void startInit(); //初始化
    void setComboBoxEnabled(bool status);
    void GpsDisplay(); //显示定位信息
    QString& UTCtime(QString& u_time); //获取GPS当前时间
    QString& UTCdate(QString& u_date); //获取GPS当前日期
    QString& alt_position(QString& alt_str); //获取当前所在的维度值
    QString& lon_position(QString& lon_str); //获取当前所在的经度值
    int timerdly;
    Posix_QextSerialPort *myGpsCom; //定义读GPS端口
    QByteArray GPS_RMC;  //获取协议中$GPRMC语句数据
    QList<QByteArray>Gps_list; //GPS信息容器
    QTimer *readTimer;


};

#endif // GPSWIDGET_H
