#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QToolTip>
#include<QMouseEvent>
#include<QTimer>
#include<QImage>
#include<QPixmap>
#include<QBitmap>
#include<QPicture>
#include<QDebug>
#include<QDesktopWidget>
#include<QLabel>
#include<QWindow>
#include<QScreen>
#include<QMouseEvent>
#include<QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMouseTracking(true);//保证不用按下鼠标键也能触发鼠标移动事件

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
   // timer->start(1000);
    angle=0;
/*
    //截取屏幕
    QWindow window;
    QPixmap grab=window.screen()->grabWindow(QApplication::desktop()->winId());
    grab.save("E:/Qt(C++)/mytransformation/screen.png");
    QLabel *label=new QLabel(this);
    label->resize(400,200);
    QPixmap pix=grab.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->move(0,100);
    */
//双缓冲绘图变量初始化
    pix=QPixmap(400,300);
    pix.fill(Qt::white);
    tempPix=pix;
    isDrawing=false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    /*
    QPainter painter(this);
    //填充界面背景为白色
    painter.fillRect(rect(),Qt::white);
    painter.setPen(QPen(Qt::red,11));
    //绘制一条线段
    painter.drawLine(QPoint(5,6),QPoint(100,99));
    //将坐标系统进行平移，使（200,150）点作为原点
    painter.translate(200,150);
    //开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //重新绘制相同的线段
    painter.drawLine(QPoint(5,6),QPoint(100,99));

    //保存Painter的状态
    painter.save();
    //将坐标系统旋转90度
    painter.rotate(90);
    painter.setPen(Qt::cyan);
    //重新绘制相同的线段
    painter.drawLine(QPoint(5,6),QPoint(100,99));
    //恢复painter的状态
    painter.restore();

    painter.setBrush(Qt::darkGreen);
    //绘制一个矩形
    painter.drawRect(-50,-50,100,50);
    painter.save();
    //将坐标系统进行缩放
    painter.scale(0.5,0.4);
    painter.setBrush(Qt::yellow);
    //重新绘制相同的矩形
    painter.drawRect(-50,-50,100,50);
    painter.restore();

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkYellow);
    //绘制一个椭圆
    painter.drawEllipse(QRect(60,-100,50,50));
    //将坐标系统进行扭曲
    painter.shear(1.5,-0.7);
    painter.setBrush(Qt::darkGray);
    //重新绘制相同的椭圆
    painter.drawEllipse(QRect(60,-100,50,50));
    */
    /*
    //窗口-视口转换
    QPainter painter(this);
    painter.setWindow(-50,-50,100,100);//设置逻辑坐标矩形以（-50,-50）为起点，宽100，高100，这样逻辑坐标的（-50，-50）点就会对应物理坐标的（0,0）点
    //因为逻辑坐标的高宽为100，所以界面的高度和宽度都会被100等分
    painter.setBrush(Qt::green);
    painter.drawRect(0,0,20,20);
    */
    /*//重要********************************************************************************
    QPainter painter(this);
    int side=qMin(width(),height());
    int x=(width()/2);
    int y=(height()/2);
    //设置视口
    painter.setViewport(x,y,side,side);
    painter.setWindow(0,0,100,100);
    painter.setBrush(Qt::green);
    painter.drawRect(0,0,20,20);
*/
    /*
    //定时器与2D绘图相结合实现简单动画
    angle+=10;
    if(angle==360)
        angle=0;
    int side=qMin(width(),height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QTransform transform;
    transform.translate(width()/2,height()/2);
    transform.scale(side/300.0,side/300.0);
    transform.rotate(angle);
    painter.setWorldTransform(transform);
    painter.drawEllipse(-120,-120,240,240);
    painter.drawLine(0,0,100,0);
    //当连续进行多个坐标转换时使用QTransform这个类更高效
    */
    /*
    //绘制文字
    QPainter painter(this);
    QRectF rect(10.0,10.0,380.0,280.0);
    painter.setPen(Qt::red);
    painter.drawRect(rect);
    painter.setPen(Qt::blue);
    painter.drawText(rect,Qt::AlignHCenter,tr("AlignHCenter"));
    painter.drawText(rect,Qt::AlignLeft,tr("AlignLeft"));
    painter.drawText(rect,Qt::AlignRight,tr("AlignRight"));
    painter.drawText(rect,Qt::AlignVCenter,tr("AlignVCenter"));
    painter.drawText(rect,Qt::AlignBottom,tr("AlignBottom"));
    painter.drawText(rect,Qt::AlignCenter,tr("AlignCenter"));
    painter.drawText(rect,Qt::AlignBottom|Qt::AlignRight,tr("AlignBottom\nAlignRight"));
QFont font("宋体",15,QFont::Bold,true);
//设置下划线
font.setUnderline(true);
//设置上划线
font.setOverline(true);
//设置字母大小写
font.setCapitalization(QFont::SmallCaps);
//设置字符间的间距
font.setLetterSpacing(QFont::AbsoluteSpacing,10);
//使用字体
painter.setFont(font);
painter.setPen(Qt::green);
painter.drawText(120,80,tr("念古linux"));
painter.translate(100,100);
painter.rotate(90);
painter.drawText(0,0,tr("helloqt"));
*/
    /*
    //绘制路径
    QPainter painter(this);
    QPainterPath path;
    //移动当前点到点（50,250）
    path.moveTo(50,250);
    //从当前点即（50,250）绘制一条直线到点（50,230），完成后当前点更改为（50,230）
    path.lineTo(50,230);
    //从当前点和点（120,60）之间绘制一条三次贝塞尔曲线
    path.cubicTo(QPointF(105,40),QPointF(115,80),QPointF(120,60));
    path.lineTo(130,130);
    //向路径中添加一个椭圆
    path.addEllipse(QPointF(130,130),30,30);
    painter.setPen(Qt::darkYellow);
    //绘制路径
    painter.drawPath(path);
    //平移坐标系统后重新绘制路径
    path.translate(200,0);
    painter.setPen(Qt::darkBlue);
    painter.drawPath(path);
    */
    /*
    //俩种填充规则，Qt::OddEvenFill和Qt::WindingFill,默认使用Qt::OddEvenFill
    QPainter painter(this);
    QPainterPath path;
    path.addEllipse(10,50,100,100);
    path.addRect(50,100,100,100);
    painter.setBrush(Qt::cyan);
    painter.drawPath(path);

    painter.translate(180,0);
    path.setFillRule(Qt::WindingFill);
    painter.drawPath(path);
    */
/*
    //绘制图像
    QPainter painter;
    //绘制image
    QImage image(100,100,QImage::Format_ARGB32);
    painter.begin(&image);
    painter.setPen(QPen(Qt::green,3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10,10,60,60);
    painter.drawText(10,10,60,60,Qt::AlignCenter,tr("QImage"));
    painter.setBrush(QColor(0,0,0,100));
    painter.drawRect(50,50,40,40);
    painter.end();
    //绘制pixmap
    QPixmap pix(100,100);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::green,3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10,10,60,60);
    painter.drawText(10,10,60,60,Qt::AlignCenter,tr("QPixmap"));
    painter.setBrush(QColor(0,0,0,100));
    painter.drawRect(50,50,40,40);
    painter.end();
    //绘制bitmap
    QBitmap bit(100,100);
    painter.begin(&bit);
    painter.setPen(QPen(Qt::green,3));
    painter.setBrush(Qt::yellow);
    painter.drawRect(10,10,60,60);
    painter.drawText(10,10,60,60,Qt::AlignCenter,tr("QBitmap"));
    painter.setBrush(QColor(0,0,0,100));
    painter.drawRect(50,50,40,40);
    painter.end();
    //绘制picture
    QPicture picture;
    painter.begin(&picture);
    painter.setPen(QPen(Qt::green,3));
    painter.setBrush(Qt::yellow);
painter.drawRect(10,10,60,60);
painter.drawText(10,10,60,60,Qt::AlignCenter,tr("QPicture"));
painter.setBrush(QColor(0,0,0,100));
painter.drawRect(50,50,40,40);
painter.end();
//在widget部件上进行绘制
painter.begin(this);
painter.drawImage(50,20,image);
painter.drawPixmap(200,20,pix);
painter.drawPixmap(50,170,bit);
painter.drawPicture(200,170,picture);
*/
/*
    //QImage
    QPainter painter(this);
    QImage image;
    //加载一张图片
    image.load("E:/Qt(C++)/mytransformation/myico.jpg");
    //image.load(":/image/myico.jpg");

    //输出图片的一些信息
    qDebug()<<image.size()<<image.format()<<image.depth();
    //在界面上绘制图片
    painter.drawImage(QPoint(10,10),image);
    //获取镜像图片
    QImage mirror=image.mirrored();
    //将图片进行扭曲
    QTransform transform;
    transform.shear(0.2,0);
    QImage image2=mirror.transformed(transform);
    painter.drawImage(QPoint(10,160),image2);
    //将镜像图片保存到文件
    image2.save("E:/Qt(C++)/mytransformation/mirror.png");
*/
    /*
//QPixmap
QPainter painter(this);
QPixmap pix;
pix.load("E:/Qt(C++)/mytransformation/myico.jpg");
painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
painter.setBrush(QColor(255,255,255,100));
painter.drawRect(0,0,pix.width(),pix.height());
painter.drawPixmap(100,0,pix.width(),pix.height(),pix);
painter.setBrush(QColor(0,0,255,100));
painter.drawRect(100,0,pix.width(),pix.height());
*/
    /*
    //QPicture
    //记录QPainter命令
    QPicture picture;
    QPainter painter;
    painter.begin(&picture);
    painter.drawEllipse(10,20,80,70);
    painter.end();
    picture.save("E:/Qt(C++)/mytransformation/drawing.pix");
*/
/*
//重演QPainter命令
    QPicture picture;
   picture.load("E:/Qt(C++)/mytransformation/drawing.pic");
    QPainter painter;
    //QPixmap pix;
 // pix.load("E:/Qt(C++)/mytransformation/myico.jpg");
  //painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
   painter.begin(this);
   painter.drawPicture(0,0,picture);
  painter.end();
*/
    /*
    //复合模式
    QPainter painter;
    QImage image(400,300,QImage::Format_ARGB32_Premultiplied);
    painter.begin(&image);
    painter.setBrush(Qt::green);
    painter.drawRect(100,50,200,200);
    painter.setBrush(QColor(0,0,255,150));
    painter.drawRect(50,0,100,100);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawRect(250,0,100,100);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.drawRect(50,200,100,100);
    painter.setCompositionMode(QPainter::CompositionMode_Xor);
    painter.drawRect(250,200,100,100);
    painter.end();
    painter.begin(this);
    painter.drawImage(0,0,image);
    */

    //双缓冲绘图
    int x=startPoint.x();
    int y=startPoint.y();
    int width=endPoint.x()-x;
    int height=endPoint.y()-y;
    QPainter painter;
    painter.begin(&tempPix);
    painter.drawRect(x,y,width,height);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0,0,tempPix);
    //如果已经完成了绘制，那么更新缓冲区
    if(!isDrawing)
        pix=tempPix;
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        //当鼠标左键按下时获取当前位置作为矩形的开始点
        startPoint=event->pos();
        //标记正在绘图
        isDrawing=true;
    }
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //QString pos=QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
   // QToolTip::showText(event->globalPos(),pos,this);
    if(event->button()&Qt::LeftButton){
        //当按着鼠标左键进行移动时，获取当前位置作为结束点，绘制矩形
        endPoint=event->pos();
        //将缓冲区的内容复制到临时缓冲区，这样进行动态绘制时
        //每次都是在缓冲区图像的基上进行绘制，就不会产生拖影现象了
        tempPix=pix;
        //更新显示
        update();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        //当鼠标左键松开时，获取当前位置为结束点，完成矩形绘制
        endPoint=event->pos();
        //标记已经结束绘图
        isDrawing=false;
        update();
    }
}
