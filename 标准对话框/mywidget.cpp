#include "mywidget.h"
#include "ui_mywidget.h"
#include<QDebug>
#include<QColorDialog>
#include<QFileDialog>
#include<QFontDialog>
#include<QInputDialog>
#include<QMessageBox>
#include<QProgressDialog>
#include<QErrorMessage>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    errordlg=new QErrorMessage(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()   //颜色对话框
{
    /*
    QColor color=QColorDialog::getColor(Qt::red,this,tr("颜色对话框"));//使用了QColorDialog的静态函数getColor()来获取颜色,3个参数的作用分别是：设置初始颜色、指定父窗口和设置对话框标题
    //返回值QColor(ARGB1,1,0,0),分别代表透明度（alpha）、红色（red）、绿色（green）和蓝色（blue）
    qDebug()<<"color:"<<color;
*/
///*
    QColorDialog dialog(Qt::red,this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    dialog.exec();
    QColor color=dialog.currentColor();
    qDebug()<<"color:"<<color;
//*/
}

void MyWidget::on_pushButton_3_clicked()   //文件对话框
{
    QStringList fileNames=QFileDialog::getOpenFileNames(this,tr("文件对话框"),"E:",tr("图片文件(*png *jpg)"));//使用QFileDialog类中的getOpenFileName()函数来获取选择的文件名
    //它的4个参数的作用分别是：指定父窗口、设置对话框标题、指定默认打开的目录路径和设置文件类型过滤器
    qDebug()<<"fileName:"<<fileNames;
}

void MyWidget::on_pushButton_2_clicked()    //字体对话框
{

    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)ui->pushButton_2->setFont(font);
    else qDebug()<<tr("没有选择字体!");
}

void MyWidget::on_pushButton_4_clicked()   //输入对话框
{
    bool ok;
    //获取字符串
    QString string=QInputDialog::getText(this,tr("输入字符串对话框"),tr("请输入用户名:"),QLineEdit::Normal,tr("admin"),&ok);
   //getText()函数可以提供一个可输入字符串的对话框,各参数的作用分别是:指定父窗口、设置窗口标题、设置对话框中的标签显示文本、
    //设置输入字符串的显示模式（例如密码可以显示成小黑点，这里选择了显示用户输入的实际内容）、设置输入框中的默认字符串和设置获取按下按钮信息的bool变量

    if(ok) qDebug()<<"string:"<<string;
    //获取整数
    int value1=QInputDialog::getInt(this,tr("输入整数对话框"),
                                    tr("请输入-1000到1000之间的数值"),100,-1000,1000,10,&ok);//100为默认值，10表示使用箭头按钮，数值每次变化10
    if(ok) qDebug()<<"value1:"<<value1;
    //获得浮点数
    double value2=QInputDialog::getDouble(this,tr("输入浮点数对话框"),
                                          tr("请输入-1000到1000之间的数值"),0.00,-1000,1000,2,&ok);//2表示小数的位数为2
    if(ok) qDebug()<<"value2:"<<value2;


    QStringList items;
    items<<tr("条目1")<<tr("条目2");
    //获取条目
    QString item=QInputDialog::getItem(this,tr("输入条目对话框"),
                                       tr("请选择或输入一个条目"),items,0,false,&ok);
    //getItem()函数提供一个可以输入一个条目的对话框，需要先给它提供一些条目例如：QStringList类型的items,其中参数0表示默认显示列表中的第0个条目
    //(0就是第一个),参数false设置条目是否可以被更改
    if(ok)qDebug()<<"item:"<<item;
}

void MyWidget::on_pushButton_6_clicked()
{
    //问题对话框
    int ret1=QMessageBox::question(this,tr("问题对话框"),
                                   tr("你了解Qt吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ret1==QMessageBox::Yes) qDebug()<<tr("问题!");
    //提示对话框
    int ret2=QMessageBox::information(this,tr("提示对话框"),tr("这是Qt书籍!"),QMessageBox::Ok);
    if(ret2==QMessageBox::Ok) qDebug()<<tr("提示!");
    //警告对话框
    int ret3=QMessageBox::warning(this,tr("警告对话框"),
                                  tr("不能提前结束!"),QMessageBox::Abort);
    if(ret3==QMessageBox::Abort) qDebug()<<tr("警告!");
    //错误对话框
    int ret4=QMessageBox::critical(this,tr("严重错误对话框"),
                                   tr("发现一个严重错误!现在要关闭所有文件!"),QMessageBox::YesAll);
    if(ret4==QMessageBox::YesAll) qDebug()<<tr("错误");
    //关于对话框
    QMessageBox::about(this,tr("关于对话框"),tr("yafeilinux致力于Qt及Qt Creator的普及工作!"));

}

void MyWidget::on_pushButton_5_clicked()
{
    QProgressDialog dialog(tr("文件复制进度"),tr("取消"),0,50000,this);//参数分别用于设置对话框的标签内容、取消按钮的显示文本、最小值、最大值和父窗口

    dialog.setWindowTitle(tr("进度对话框"));   //设置窗口标题
    dialog.setWindowModality(Qt::WindowModal);  //将对话框设置为模态
    dialog.show();
    for(int i=0;i<50000;i++)       //演示（模拟）复制进度
    {
        dialog.setValue(i);        //设置进度条的当前值
        QCoreApplication::processEvents();//避免界面冻结（必须）
        if(dialog.wasCanceled()) break;//按下取消按钮则中断
    }
    dialog.setValue(50000);             //这样才能显示100%，因为for循环中少加了一个数
    qDebug()<<tr("复制结束!");

}

void MyWidget::on_pushButton_7_clicked()    //错误信息对话框
{
    errordlg->setWindowTitle(tr("错误信息对话框"));
    errordlg->showMessage(tr("这里是出错信息!"));//此对话框中有个Show this message again复选框，可以选择以后是否还要显示相同错误信息
                                               //为了这个复选框的功能有效，不能像前面几个例子一样在槽中直接创建对话框

}

QWizardPage *MyWidget::createPage1() //向导页面1
{
 QWizardPage *page=new QWizardPage;
 page->setTitle(tr("介绍"));
 return page;
}

QWizardPage *MyWidget::createPage2()  //向导页面2
{
   QWizardPage *page=new QWizardPage;
   page->setTitle(tr("用户选择信息"));
   return page;
}

QWizardPage *MyWidget::createPage3()  //向导页面3
{
    QWizardPage *page=new QWizardPage;
    page->setTitle(tr("结束"));
    return page;
}
void MyWidget::on_pushButton_8_clicked()
{
QWizard wizard(this);
wizard.setWindowTitle(tr("向导对话框"));
wizard.addPage(createPage1());          //添加向导页面
wizard.addPage(createPage2());
wizard.addPage(createPage3());
wizard.exec();
}
