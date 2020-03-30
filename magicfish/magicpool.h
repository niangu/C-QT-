#ifndef MAGICPOOL_H
#define MAGICPOOL_H

#include <QWidget>
#include "magicfish.h"
#include "QTime"
#include "qdebug.h"

class MagicPool : public QWidget
{
    Q_OBJECT
public:
    explicit MagicPool(QWidget *parent = 0);
    ~MagicPool();

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    bool startCircle;           //开始绘制按下处的圆
    int radius;                 //圆半径
    double moveStep;            //每次移动的步长
    QColor circleColor;         //按下处圆的颜色
    QPoint circlePos;           //按下处的坐标

    MagicFish *fish;            //魔法鱼
    QPainterPath path;          //移动的路径

    QTimer *timerCircle;        //绘制圆定时器
    QTimer *timerMove;          //移动定时器

private:
    double calcIncludedAngle(const QPointF &center, const QPointF &head, const QPointF &touch);
    double getLength(const QPointF &pos1, const QPointF &pos2);
    QPointF calcPoint(const QPointF &pos, double length, double angle);
    double qDegreesToRadians(double degrees);
    double qRadiansToDegrees(double radians);

private slots:
    void doPress();
    void updateValue();
    void updateMove();
    void updatePress();
};

#endif // MAGICPOOL_H
