#include "widget.h"
#include "ui_widget.h"
#include<QCameraInfo>
#include<QCameraImageCapture>
#include<QCameraViewfinder>
#include<QFileDialog>
#include<QDebug>
#include<QMediaRecorder>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<QCameraInfo>cameras=QCameraInfo::availableCameras();
    if(cameras.count()>0)
    {
        foreach(const QCameraInfo &cameraInfo,cameras)
        {
            qDebug()<<cameraInfo.description();
        }
        camera=new QCamera(cameras.at(0));
    }
    viewfinder=new QCameraViewfinder(this);
    camera->setViewfinder(viewfinder);
    viewfinder->resize(600,350);
    imageCapture=new QCameraImageCapture(camera);
    camera->start();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    camera->setCaptureMode(QCamera::CaptureStillImage);//拍照设为拍照模式
    QString fileName=QFileDialog::getSaveFileName();
    camera->searchAndLock();//使用capture()捕获图形时,一般先对相机进行锁定，完成捕获后解锁
    //必须使用绝对路径
    imageCapture->capture(fileName);
    camera->unlock();

}

void Widget::on_pushButton_2_clicked()
{
    recorder=new QMediaRecorder(camera);
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);
    recorder->setAudioSettings(audioSettings);
    recorder->setOutputLocation(QUrl::fromLocalFile("E:/Qt(C++)/mycamera"));
    recorder->record();//不顶是
}
