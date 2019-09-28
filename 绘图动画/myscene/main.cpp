#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsRectItem>
#include<QDebug>
#include<QGraphicsView>
#include"myitem.h"
#include"myview.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    /*
//新建场景
    QGraphicsScene scene;
    //创建矩形图形项
    //QGraphicsRectItem *item=new QGraphicsRectItem(0,0,100,100);
    //使用自定义图形项
    MyItem *item=new MyItem;
    //将图像项添加到场景中
    scene.addItem(item);
    //输出（50，,50）点处的图形项
    qDebug()<<scene.itemAt(50,50,QTransform());

    //为场景创建视图
    QGraphicsView view(&scene);
    //设置场景的前景色
    //view.setForegroundBrush(QColor(255,255,0,100));
    scene.setForegroundBrush(QColor(255,255,0,100));
    //设置场景的背景图片
    //view.setBackgroundBrush(QPixmap("E:/Qt(C++)/myscene/as.png"));
    scene.setBackgroundBrush(QPixmap("E:/Qt(C++)/myscene/as.png"));
    view.resize(400,300);
    view.show();

    QGraphicsView view2(&scene);
    view2.resize(400,300);
    view2.show();
    */
    QGraphicsScene scene;
    scene.setSceneRect(0,0,400,300);//设置创建场景矩形
    MyItem *item=new MyItem;
    //item->setZValue(1);

    scene.addItem(item);
    item->setPos(10,10);
    QGraphicsRectItem *rectItem=scene.addRect(QRect(0,0,100,100),QPen(Qt::blue),QBrush(Qt::green));
    item->setParentItem(rectItem);//把item图形项添加到rectItem图形项
    rectItem->setRotation(45);
    rectItem->setPos(20,20);
    MyView view;
    view.setScene(&scene);
    view.setForegroundBrush(QColor(255,255,0,100));
    view.setBackgroundBrush(QPixmap("E:/Qt(C++)/myscene/as.png"));
    view.resize(400,300);
    view.show();
    return app.exec();
}
