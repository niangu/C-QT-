#include "widget.h"
#include "ui_widget.h"
#include<QMouseEvent>
#include<QKeyEvent>
#include<QDebug>
#include<QTimer>
#include<QTime>
#include<QKeyEvent>
#include<QWheelEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCursor cursor;//创建光标对象
    cursor.setShape(Qt::OpenHandCursor);//设置光标形状
    setCursor(cursor);//使用光标
setMouseTracking(true);//设置鼠标跟踪
setFocus();//使主界面获得焦点
keyUp=false;//初始化变量
keyLeft=false;
move=false;
id1=startTimer(1000);//开启一个1秒=1000毫秒定时器，返回其ID
id2=startTimer(1500);
id3=startTimer(2200);

QTimer *timer=new QTimer(this);//创建一个新的定时器
//关联定时器的溢出信号到槽上
connect(timer,&QTimer::timeout,this,&Widget::timerUpdate);
timer->start(1000);//设置溢出时间为1s，并启动定时器

//随机数
qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//secsTo()俩个时间点之间的秒数，为qrand设置不同的初值，否则每次运行程序会产生相同的随机数

QTimer::singleShot(10000,this,&Widget::close);//singleShot()函数来开启一个只运行一次的定时器

ui->textEdit->installEventFilter(this);//为编辑器部件在本窗口上安装事件过滤器
ui->spinBox->installEventFilter(this);

QKeyEvent myEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier);
qApp->sendEvent(ui->spinBox,&myEvent);//发送键盘事件到spinBox部件，等价于QApplication::sendEvent()
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)//鼠标按下事件
{
    if(event->button()==Qt::LeftButton)//如果是鼠标左键按下
    {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);//使鼠标指针暂时改变形状
        offset=event->globalPos()-pos();//获取指针位置和窗口位置差值

    }
    else if(event->button()==Qt::RightButton)//如果是鼠标右键按下
    {
        QCursor cursor(QPixmap(":/image/a"));
        QApplication::setOverrideCursor(cursor);//使用自定义的图片作为鼠标指针
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{
    if(event->buttons()&Qt::LeftButton)//这里必须使用buttons()
        {
       QPoint temp;
       temp=event->globalPos()-offset;
       QWidget::move(temp);//使用鼠标指针当前的位置减去差值，就得到了窗口应该移动的位置
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)//鼠标释放事件
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();//恢复鼠标指针形状
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)//鼠标双击事件
{
    if(event->button()==Qt::LeftButton)//如果是鼠标左键按下
    {
        if(windowState()!=Qt::WindowFullScreen)//如果现在不是全屏
            setWindowState(Qt::WindowFullScreen);//将窗口设置为全屏
        else setWindowState(Qt::WindowNoState);//否则恢复以前的大小
    }
}

void Widget::wheelEvent(QWheelEvent *event)//滚轮事件
{
    if(event->delta()>0)//当滚轮远离使用者时
        {
        ui->textEdit->zoomIn();//进行放大
    }else{
        ui->textEdit->zoomOut();//进行缩小
    }
}

void Widget::keyPressEvent(QKeyEvent *event)//键盘按下事件
{
    /*
    if(event->modifiers()==Qt::ControlModifier)//是否按下Ctrl
        {
        if(event->key()==Qt::Key_M)//是否按下M键
            setWindowState(Qt::WindowMaximized);//窗口最大化
    }else if(event->key()==Qt::Key_Up)//如果是向上方向键
            {
                qDebug()<<"press:"<<event->isAutoRepeat();//是否自动重复
            }
    else QWidget::keyPressEvent(event);
*/
    if(event->key()==Qt::Key_Up)
    {
        if(event->isAutoRepeat())return;//按键重复时不做处理
        keyUp=true;//标记向上方向键已经按下
    }
    else if(event->key()==Qt::Key_Left)
    {
        if(event->isAutoRepeat())return;
        keyLeft=true;
    }
}



void Widget::keyReleaseEvent(QKeyEvent *event)//按键释放事件
{
    if(event->key()==Qt::Key_Up)
    {
    if(event->isAutoRepeat())return;
    keyUp=false;//释放按键后将标志设置为false
    if(move)//如果已经完成了移动
    {
        move=false;//设置标志为false
        return;//直接返回
    }
    if(keyLeft)//如果向左方向键已经按下且没有释放
    {
        ui->pushButton->move(30,80);//斜移
        move=true;//标记已经移动
    }else{
        ui->pushButton->move(120,80);//否则直接上移
    }
}
    else if(event->key()==Qt::Key_Left)
    {
        if(event->isAutoRepeat())return;
        keyLeft=false;
        if(move)
        {
            move=false;
            return;
        }
        if(keyUp)
        {
            ui->pushButton->move(30,80);
            move=true;
        }else{
            ui->pushButton->move(30,120);
        }
    }
    else if(event->key()==Qt::Key_Down)
    {
        ui->pushButton->move(120,120);//使用向下方向键来还原按钮的位置
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==id1)//判断是哪个定时器
    {
        qDebug()<<"timer1";
    }
    else if(event->timerId()==id2)
    {
        qDebug()<<"timer2";
    }
    else{
        qDebug()<<"timer2";
    }
}

void Widget::timerUpdate()//定时器溢出处理
{
    QTime time=QTime::currentTime();//获取当前时间
    QString text=time.toString("hh:mm");//转换为字符串
    if((time.second()%2)==0)text[2]=' ';//每隔一秒就将“：”显示为空格,如果想停止一个定时器可以调用他的stop()函数
    ui->lcdNumber->display(text);

    int rand=qrand()%300;//产生300以内的正整数
    ui->lcdNumber->move(rand,rand);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)//事件过滤器
{
    if(watched==ui->textEdit)//判断部件
        {
        if(event->type()==QEvent::Wheel)//判断事件
        {
            //将event强制转换为发生的事件的类型
            QWheelEvent *wheelEvent=static_cast<QWheelEvent*>(event);
            if(wheelEvent->delta()>0)ui->textEdit->zoomIn();
            else ui->textEdit->zoomOut();
            return true;//该事件已经被处理
        }else{
            return false;//如果是其他事件，可以进行进一步的处理
        }
    }
    else if(watched==ui->spinBox)
    {
        if(event->type()==QEvent::KeyPress)
        {
            QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
            if(keyEvent->key()==Qt::Key_Space)
            {
                ui->spinBox->setValue(0);
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    else return QWidget::eventFilter(watched,event);
}
