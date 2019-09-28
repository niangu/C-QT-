#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSoundEffect>
#include<QMediaPlayer>
#include<QVideoWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    effect=new QSoundEffect(this);
effect->setSource(QUrl::fromLocalFile("E:/Qt(C++)/mysoundeffect/b.mp3"));
effect->setVolume(0.5f);//设置音量大小，其取值范围0.0-1.0

//播放视频
player=new QMediaPlayer(this);
videoWidget=new QVideoWidget(this);
videoWidget->resize(600,300);
player->setVideoOutput(videoWidget);
player->setMedia(QUrl::fromLocalFile("E:/Qt(C++)/mysoundeffect/c.wmv"));
player->play();
//亮度
ui->brightnessSlider->setValue(videoWidget->brightness());
connect(ui->brightnessSlider,&QSlider::sliderMoved,videoWidget,&QVideoWidget::setBrightness);
connect(videoWidget,&QVideoWidget::brightnessChanged,ui->brightnessSlider,&QSlider::setValue);
//对比度
ui->contrastSlider->setValue(videoWidget->contrast());
connect(ui->contrastSlider,&QSlider::sliderMoved,videoWidget,&QVideoWidget::setContrast);
connect(videoWidget,&QVideoWidget::contrastChanged,ui->contrastSlider,&QSlider::setValue);
//色相
ui->hueSlider->setValue(videoWidget->hue());
connect(ui->hueSlider,&QSlider::sliderMoved,videoWidget,&QVideoWidget::setHue);
connect(videoWidget,&QVideoWidget::hueChanged,ui->hueSlider,&QSlider::setValue);
//饱和度
ui->saturationSlider->setValue(videoWidget->saturation());
connect(ui->saturationSlider,&QSlider::sliderMoved,videoWidget,&QVideoWidget::setSaturation);
connect(videoWidget,&QVideoWidget::saturationChanged,ui->saturationSlider,&QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //播放按钮
    effect->play();
}

void MainWindow::on_pushButton_2_clicked()//停止按钮
{
   effect->stop();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    effect->setLoopCount(arg1);//设置声音的播放次数,如果要无限重复，则需要设置为QSoundEffect::Infinite
}
