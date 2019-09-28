#include "myview.h"
#include<QKeyEvent>

MyView::MyView(QWidget *parent):QGraphicsView(parent)
{

}

void MyView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
        scale(1.2,1.2);
        break;
    case Qt::Key_Minus:
        scale(1/1.2,1/1.2);
        break;
    case Qt::Key_Right:
        rotate(30);
        break;
    }
    QGraphicsView::keyPressEvent(event);//在视图的事件处理函数的最后一定要调用QGraphicsView类的keyPressEvent()函数，不然在场景或者图形项中就无法再接收到该事件了
}


