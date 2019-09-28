#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QTimer;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    QTimer *timer;
    int angle;
    //双缓冲绘图
   //缓冲区
    QPixmap pix;
    //临时缓存区
    QPixmap tempPix;
    QPoint startPoint;
    QPoint endPoint;
    //是否正在绘图的标志、
    bool isDrawing;
};

#endif // WIDGET_H
