#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
bool eventFilter(QObject *watched, QEvent *event);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
void keyPressEvent(QKeyEvent *event);
void keyReleaseEvent(QKeyEvent *event);
void timerEvent(QTimerEvent *event);
private:
    Ui::Widget *ui;
    QPoint offset;    //用来存储鼠标指针位置与窗口位置的差值
    bool keyUp;//向上方向键按下的标志
    bool keyLeft;//向左方向键按下的标志
    bool move;//是否完成了一次移动
    int id1,id2,id3;
private slots:
    void timerUpdate();
};

#endif // WIDGET_H
