/*
#include<QApplication>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QSequentialAnimationGroup>//串行动画组
#include<QParallelAnimationGroup>//并行动画组
 int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    /*
    QPushButton button("Animated Button");
    button.show();
    QPropertyAnimation animation(&button,"geometry");

    animation.setLoopCount(-1);//在stop()停止前一直持续
    animation.setDuration(10000);
//    animation.setStartValue(QRect(0,0,120,30));
  //  animation.setEndValue(QRect(250,250,200,60));
    animation.setKeyValueAt(0,QRect(0,0,120,30));//实现按钮部件在8秒内从屏幕的（0,0）点移动到（250,250），并变化大小，然后又在2秒内又回到原点
    //animation.setKeyValueAt(0.8,QRect(250,250,200,60));
    //使用缓和曲线

    animation.setDuration(2000);
    animation.setStartValue(QRect(250,0,120,30));
    animation.setEndValue(QRect(250,300,120,30));
    animation.setEasingCurve(QEasingCurve::OutBounce);//使用了缓和曲线，QEasingCurve类中提供了四十多种缓和曲线，而且还可以自定义缓和曲线
    animation.setKeyValueAt(1,QRect(0,0,120,30));

    animation.start();

    QPushButton button("Animated Button");
    button.show();
    //按钮部件的动画1
    QPropertyAnimation *animation1=new QPropertyAnimation(&button,"geometry");
    animation1->setDuration(2000);
    animation1->setStartValue(QRect(250,0,120,30));
    animation1->setEndValue(QRect(250,300,120,30));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //按钮部件的动画2
    QPropertyAnimation *animation2=new QPropertyAnimation(&button,"geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(QRect(250,300,120,30));
    animation2->setEndValue(QRect(250,300,200,60));
    //串行动画组
   // QSequentialAnimationGroup group;
    //group.addAnimation(animation1);
   // group.addAnimation(animation2);
    //group.start();
    //并行动画组
    QParallelAnimationGroup group2;
    group2.addAnimation(animation1);
    group2.addAnimation(animation2);
    group2.start();
    return app.exec();
}
*/
//QGraphicsObject使用，myitem类
#include<QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include"myitem.h"
#include<QPropertyAnimation>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QGraphicsScene scene;
    scene.setSceneRect(-200,-150,400,300);
    MyItem *item=new MyItem;
    scene.addItem(item);
    QGraphicsView view;
    view.setScene(&scene);
    view.show();
    //为图形项的rotation属性创建动画
    QPropertyAnimation *animation=new QPropertyAnimation(item,"rotation");
    animation->setDuration(2000);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    return app.exec();
}
