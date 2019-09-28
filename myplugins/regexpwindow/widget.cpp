#include "widget.h"
#include "ui_widget.h"
#include<QPluginLoader>
#include<QMessageBox>
#include<QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    if(!loadPlugin()){//如果无法加载插件
        QMessageBox::information(this,"Error","Could not load the plugin");
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::loadPlugin()
{
    QDir pluginDir("E:/Qt(C++)/myplugins/plugins");
    //遍历插件目录
    foreach(QString fileName,pluginDir.entryList(QDir::Files)){
        QPluginLoader pluginLoader(pluginDir.absoluteFilePath(fileName));
        QObject *plugin=pluginLoader.instance();
        if(plugin){
            regexpInterface=qobject_cast<RegExpInterface*>(plugin);
            if(regexpInterface)
                return true;
        }
    }
}
void Widget::on_pushButton_clicked()
{
    QString str=regexpInterface->regexp(ui->lineEdit->text());
    ui->labelNum->setText(str);
}


