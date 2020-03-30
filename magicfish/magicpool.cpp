#include "magicpool.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qtimer.h"\

MagicPool::MagicPool(QWidget *parent) : QWidget(parent)
{
    startCircle = false;
    radius = 4;
    moveStep = 0.0;
    circleColor = QColor(34, 163, 169);

    fish = new MagicFish(this);
    fish->setFixedSize(100, 100);

    timerCircle = new QTimer(this);
    timerCircle->setInterval(20);
    connect(timerCircle, SIGNAL(timeout()), this, SLOT(updateValue()));

    timerMove = new QTimer(this);
    timerMove->setInterval(20);
    connect(timerMove, SIGNAL(timeout()), this, SLOT(updateMove()));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePress()));
    timer->start(2000);
}

MagicPool::~MagicPool()
{
    if (timerCircle->isActive()) {
        timerCircle->stop();
    }

    if (timerMove->isActive()) {
        timerMove->stop();
    }
}

void MagicPool::mousePressEvent(QMouseEvent *e)
{
    circlePos = e->pos();
    doPress();
}

void MagicPool::paintEvent(QPaintEvent *e)
{
    if(startCircle) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen;
        pen.setWidth(5);
        pen.setColor(circleColor);
        painter.setPen(pen);
        painter.setBrush(circleColor);
        painter.drawEllipse(circlePos, radius, radius);
    }
}

double MagicPool::calcIncludedAngle(const QPointF &center, const QPointF &head, const QPointF &touch)
{
    double abc = (head.x() - center.x()) * (touch.x() - center.x()) + (head.y() - center.y()) * (touch.y() - center.y());
    double cos_abc = (abc) / qSqrt((head.x() - center.x()) * (head.x() - center.x()) + (head.y() - center.y()) * (head.y() - center.y())) /
                     qSqrt((touch.x() - center.x()) * (touch.x() - center.x()) + (touch.y() - center.y()) * (touch.y() - center.y()));
    double tmp_angle = qRadiansToDegrees(qAcos(cos_abc));
    double direction = (center.x() - touch.x()) * (head.y() - touch.y()) - (center.y() - touch.y()) * (head.x() - touch.x());
    if(direction == 0) {
        if(abc >= 0) {
            return 0;
        } else {
            return 180;
        }
    } else {
        if(direction > 0) {
            return -tmp_angle;
        } else {
            return tmp_angle;
        }
    }
}

double MagicPool::getLength(const QPointF &pos1, const QPointF &pos2)
{
    return qSqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}

QPointF MagicPool::calcPoint(const QPointF &pos, double length, double angle)
{
    double x = qCos(qDegreesToRadians(angle)) * length;
    double y = qSin(qDegreesToRadians(angle - 180)) * length;
    return QPointF(pos + QPointF(x, y));
}

double MagicPool::qDegreesToRadians(double degrees)
{
    return degrees * double(M_PI / 180);
}

double MagicPool::qRadiansToDegrees(double radians)
{
    return radians * double(180 / M_PI);
}

void MagicPool::doPress()
{
    startCircle = true;
    radius = 4;
    moveStep = 0.0;

    QPointF fish_middle = fish->geometry().center();
    QPointF fish_head = fish->geometry().topLeft() + fish->getHeadPos();
    double angle = calcIncludedAngle(fish_middle, fish_head, circlePos);
    double delta = calcIncludedAngle(fish_middle, fish_middle + QPointF(1, 0), fish_head);
    QPointF c = calcPoint(fish_middle, 17 * fish->getHeadLen(), angle / 2 + delta);
    QPointF p(fish->width() / 2, fish->height() / 2);
    path = QPainterPath();
    path.moveTo(this->fish->geometry().topLeft());
    path.cubicTo(fish_head - p, c - p, this->circlePos - p);

    fish->setFinMove(true);
    fish->setWave(2.5);
    timerCircle->start();
    timerMove->start();
}

void MagicPool::updateValue()
{
    radius += 2;
    if(radius >= 40) {
        radius = 4;
        startCircle = false;
        timerCircle->stop();
    }

    update();
}

void MagicPool::updateMove()
{
    double tmp = 0.00;
    if(moveStep >= 0.85) {
        tmp = qSin(qDegreesToRadians(moveStep * 180)) * 0.02;
        fish->setFinMove(false);
        fish->setWave(1.0);
    } else {
        tmp = 0.015 + qCos(qDegreesToRadians(moveStep * 90)) * 0.02;
        fish->setWave(1.0 / (moveStep + 0.1));
    }

    moveStep += tmp;
    if(moveStep >= 1.0 || (1 - moveStep) <= 0.003) {
        moveStep = 0.0;
        path = QPainterPath();
        timerMove->stop();
    } else {
        QPointF p = path.pointAtPercent(moveStep);
        double angle = path.angleAtPercent(moveStep);
        fish->setCurrentAngle(angle);
        fish->move(p.x(), p.y());
        update();
    }
}

void MagicPool::updatePress()
{
    int x = qrand() % width();
    int y = qrand() % height();
    circlePos = QPoint(x, y);
    doPress();
}
