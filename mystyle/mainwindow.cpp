#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStyleFactory>
#include<QPalette>
#include<QFile>
#include<QPixmap>
#include<QBitmap>
#include<QPainter>
#include<QGraphicsDropShadowEffect>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setStyle(QStyleFactory::create("windows"));
//调色板
    //获取pushButton的调色板
  //  QPalette palettel=ui->pushButton->palette();
    //设置按钮文本颜色为红色
   // palettel.setColor(QPalette::ButtonText,Qt::red);
    //设置按钮背景颜色为绿色
   // palettel.setColor(QPalette::Button,Qt::green);
    //pushButton使用修改后的调色板
    //ui->pushButton->setPalette(palettel);
    //设置spinBox不可用
   // ui->spinBox->setDisabled(true);
  //  QPalette palette2=ui->spinBox->palette();
    //设置spinBox不可用时的背景颜色为蓝色
  //  palette2.setColor(QPalette::Disabled,QPalette::Base,Qt::blue);
  //  ui->spinBox->setPalette(palette2);

    //样式表
//设置pushButton的背景为黄色
   // ui->pushButton_2->setStyleSheet("background:yellow");
    //设置horizontalSlider的背景色
    //ui->horizontalSlider->setStyleSheet("background:blue");
//setStyleSheet("QPushButton{background:yellow}QSlider{background:blue}");

    //调用样式表
  //  qssFile=new QFile(":/qss/my.qss",this);
    //只读方式打开该文件
   // qssFile->open(QFile::ReadOnly);
    //读取文件全部内容，使用tr()函数将其转换为QString类型
   // QString styleSheet=tr(qssFile->readAll());
    //为QApplication设置样式表
    //qApp->setStyleSheet(styleSheet);
  //  qssFile->close();

  //不规则窗体
  QPixmap pixmap(":/image/png/a.png");
  QPixmap pixmap2(":/image/png/a.png");
  ui->label->setPixmap(pixmap);
  ui->label->setMask(pixmap.mask());//mask部件遮罩
  ui->label_2->setPixmap(pixmap2);
  ui->label_2->setMask(pixmap.mask());
    QPixmap pix;
    //加载图片
   pix.load(":/image/png/b.png");
    //设置窗口大小为图片大小
   resize(pix.size());
    //为窗口设置遮罩
    setMask(pix.mask());
    //设置窗口的不透明度为0.5
    // setWindowOpacity(0.5);
//setWindowFlags(Qt::FramelessWindowHint);//在Windows下，还要使用setWindowFlags()函数指定Qt::FramelessWindowHint标志，这样才能实现透明效果
//setAttribute(Qt::WA_TranslucentBackground);//使窗体透明，部件不受影响

    //实现部件透明、模糊、阴影、染色等特殊效果
    //创建阴影效果
    QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect;
    //设置阴影颜色
    effect->setColor(QColor(100,100,100,100));
    //设置阴影模糊半径
    effect->setBlurRadius(2);
    //设置阴影偏移值
    effect->setOffset(10);
    //标签部件使用阴影效果
    ui->label->setGraphicsEffect(effect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(qssFile->fileName()==":/qss/my.qss")
        qssFile->setFileName(":/qss/my1.qss");
    else qssFile->setFileName(":/qss/my.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet=tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //从窗口左上角开始绘制图片
   painter.drawPixmap(0,0,QPixmap(":/image/png/b.png"));

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //关闭窗口
   // close();
}
