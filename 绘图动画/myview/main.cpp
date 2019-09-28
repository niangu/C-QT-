/*
#include<QApplication>
#include"myitem.h"
#include"myview.h"
#include<QTime>
#include<QTimer>
#include<QPushButton>
#include<QPrinter>
#include<QPrintDialog>
#include<QPainter>
#include<QPixmap>
#include<QOpenGLWidget>
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene scene;
    scene.setSceneRect(-200,-150,400,300);
    for(int i=0;i<5;++i)
    {
        MyItem *item=new MyItem;
        item->setColor(QColor(qrand()%256,qrand()%256,qrand()%256));
        item->setPos(i*50-90,-50);
        scene.addItem(item);
    }
    //图形项组
    MyItem *item1=new MyItem;
    item1->setColor(Qt::blue);
    MyItem *item2=new MyItem;
    item2->setColor(Qt::green);
    QGraphicsItemGroup *group=new QGraphicsItemGroup;
    group->addToGroup(item1);
    group->addToGroup(item2);
    group->setFlag(QGraphicsItem::ItemIsMovable);
    item2->setPos(30,0);
    scene.addItem(group);
QPushButton *Btn=new QPushButton;
scene.addWidget(Btn);
Btn->setText("这呵呵呵呵呵");

    MyView view;
view.setViewport(new QOpenGLWidget());//将QOpenGLWidget做为QGraphicsView的视口，就可以使用OpenGL进行渲染了
    view.setScene(&scene);
    view.setBackgroundBrush(QPixmap("E:/Qt(C++)/myview/myico3.png"));
    view.show();
    QTimer timer;
    QObject::connect(&timer,&QTimer::timeout,&scene,&QGraphicsScene::advance);
    timer.start(300);
    //打印
QPrinter printer;
if(QPrintDialog(&printer).exec()==QDialog::Accepted)
{
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::Antialiasing);
    scene.render(&painter);
}



//屏幕快照
QPixmap pixmap(400,300);
QPainter painter(&pixmap);
painter.setRenderHint(QPainter::Antialiasing);
view.render(&painter);
painter.end();
pixmap.save("view.png");
    return app.exec();
}
*/

#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsWidget>
#include<QTextEdit>
#include<QPushButton>
#include<QGraphicsProxyWidget>
#include<QGraphicsLinearLayout>
#include<QObject>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QGraphicsScene scene;
    //创建部件，并关联它们的信号和槽
    QTextEdit *edit=new QTextEdit;
    QPushButton *button=new QPushButton("clear");
    QObject::connect(button,SIGNAL(clicked()),edit,SLOT(clear()));
    //将部件添加到场景中
    QGraphicsWidget *textEdit=scene.addWidget(edit);
    QGraphicsWidget *pushButton=scene.addWidget(button);
    //将部件添加到布局管理器中
    QGraphicsLinearLayout *layout=new QGraphicsLinearLayout;
    layout->addItem(textEdit);
    layout->addItem(pushButton);
    //创建图形部件，设置其为一个顶层窗口，然后在其上应用布局
    QGraphicsWidget *form=new QGraphicsWidget;
    form->setWindowTitle("Widget Item");
    form->setLayout(layout);
    //将图形部件进行扭曲，然后添加到场景中
    form->setTransform(QTransform().shear(2,-0.5),true);
    scene.addItem(form);
    QGraphicsView view(&scene);
    view.show();
    return app.exec();
}


