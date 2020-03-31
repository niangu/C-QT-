#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "serialportapi/qextserialport.h"

namespace Ui
{
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private slots:
    void Append(QString msg, bool isSend);
    void ReadData();
    void WriteData();
    void on_btnOpen_clicked();
    void on_btnClearCount_clicked();
    void on_btnStopShow_clicked();
    void on_btnClearAll_clicked();
    void on_btnSave_clicked();
    void on_ckHexSend_stateChanged(int arg1);
    void on_ckHexReceive_stateChanged(int arg1);
    void on_btnSend_clicked();
    void on_cboxInterval_activated(const QString &arg1);
    void on_cboxSleepTime_activated(const QString &arg1);
    void on_cboxMaxCount_activated(const QString &arg1);

    void on_btnPlot_clicked();
    void addPlot();

private:
    Ui::frmMain *ui;

    QextSerialPort *com;
    QTimer *timer;
    QTimer *timerPlot;

    int MaxCount;       //最大显示行数
    int CurrentCount;   //当前显示行数
    int SleepTime;      //接收延时时间
    int SendCount;      //发送数据计数
    int ReceiveCount;   //接收数据计数
    bool IsShow;        //是否显示数据
    bool IsHexSend;     //是否16进制数据发送
    bool IsHexReceive;  //是否16进制数据接收
    void InitForm();    //初始化窗体数据
    void InitPlot();

};

#endif // FRMMAIN_H
