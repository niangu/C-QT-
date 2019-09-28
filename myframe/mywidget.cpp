#include "mywidget.h"
#include "ui_mywidget.h"
#include<QPixmap>
#include<QMovie>
#include<QDebug>
#include<QMenu>
#include<QCompleter>
#include<QHBoxLayout>
#include<QGridLayout>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{

    ui->setupUi(this);


 ui->label->setPixmap(QPixmap("E:/Qt(C++)/myframe/1.png"));
 QMovie *movie=new QMovie("E:/Qt(C++)/myframe/down_18_11_29_19_20_03.gif");
 ui->label_2->setMovie(movie);
 movie->start();
    //    QFrame
    ui->frame->setFrameShape(QFrame::Box);
    ui->frame->setFrameShadow(QFrame::Sunken);
    //以上俩个函数可以使用setFrameStyle(QFrame::Box|QFrame::Sunken)代替
    ui->frame->setLineWidth(5);
    ui->frame->setMidLineWidth(10);

/*
    QFont font;
    font.setFamily("华文行楷");
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    ui->label->setFont(font);
    //QFontMetrics
    QString string=tr("标题太长,需要进行省略!");
    QString str=ui->label->fontMetrics().elidedText(string,Qt::ElideRight,180);//进行文本省略,第一个参数指定要省略的文本，
                                                                               //第二个参数是省略模式（就是省略号出现的位置）,
                                                                               //第三个参数是文本的长度,单位是像素,只要第一个参数指定的文本长度超过了这个值,就会进行省略
    ui->label->setText(str);
*/

ui->pushBtn1->setText(tr("&nihao"));
//ui->pushBtn2->setText(tr("Help(&H)"));
//ui->pushBtn2->setIcon(QIcon(":/image/a.png"));
ui->pushBtn3->setText(tr("z&oom"));
QMenu *menu=new QMenu(this);
menu->addAction(QIcon("b"),tr("放大"));
ui->pushBtn3->setMenu(menu);

//输入验证
//新建验证器，指定范围为100-999
QValidator *validator=new QIntValidator(100,999,this);
//在行编辑器中使用验证器
ui->lineEdit_3->setValidator(validator);

//自动补全
QStringList wordList;
wordList<<"Qt"<<"Qt Creator"<<tr("你好");
QCompleter *completer=new QCompleter(wordList,this);//新建自动完成器
completer->setCaseSensitivity(Qt::CaseInsensitive);//设置大小写不敏感
ui->lineEdit_4->setCompleter(completer);

//设置时间为现在的系统时间
ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
//设置时间的显示格式
//ui->dateTimeEdit->setDisplayFormat(tr("yyyy年MM月dd日dddHH时mm分ss 秒"));
/*水平布局管理器
QHBoxLayout *layout=new QHBoxLayout;   //新建水平布局管理器,addLayout添加子布局
layout->addWidget(ui->fontComboBox);       //向布局管理器中添加部件
layout->addWidget(ui->textEdit);
layout->setSpacing(50);                //设置部件间的间隔
layout->setContentsMargins(0,0,50,100); //设置布局管理器到边界的距离，四个参数顺序是左,上,右,下
setLayout(layout);                      //将这个布局设置为MyWidget类的布局

*/
/*栅格布局管理器
QGridLayout *layout=new QGridLayout;
//添加部件，从第0行0列开始，占据1行2列
layout->addWidget(ui->fontComboBox,0,0,1,2);
//添加部件，从0行2列开始，占据1行1列
layout->addWidget(ui->pushButton,0,2,1,1);
//添加部件，从第1行0列开始，占据1行3列
layout->addWidget(ui->textEdit,1,0,1,3);
setLayout(layout);
*/

ui->textEdit->hide();//让文本编辑器隐藏，也可以使用setVisible(false)函数
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushBtn1_toggled(bool checked)  //按钮是否处于被按下状态
{
    qDebug()<<tr("按钮是否按下:")<<checked;
}

void MyWidget::on_lineEdit_3_returnPressed()//回车键按下信号的槽中
{
    ui->lineEdit_2->setFocus();    //让lineEdit3获得焦点
    qDebug()<<ui->lineEdit_2->text();   //输出lineEdit2的内容
    qDebug()<<ui->lineEdit_2->displayText();//输出lineEdit显示的内容

}

void MyWidget::on_pushButton_toggled(bool checked)     //显隐窗口按钮
{
    ui->textEdit->setVisible(checked);                 //设置文本编辑器的显示和隐藏
    if(checked)ui->pushButton->setText(tr("隐藏可可扩展窗口"));
    else ui->pushButton->setText(tr("显示可扩展窗口"));
}
