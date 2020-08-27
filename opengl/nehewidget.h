#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QOpenGLBuffer>
#include<QObject>

class QOpenGLShaderProgram;
class QOpenGLTexture;


class NeHeWidget:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    NeHeWidget(QWidget* parent=0,const char* name=0,bool fs=false);
    void setParam(float ****vec,float ****vec2);
    void setParam2(QVector<float>*x_1,QVector<float>*y_1,QVector<float>*z_1,QVector<float>*r1,QVector<float>*g1,QVector<float>*b1,QVector<float>*a1);
    ~NeHeWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void keyPressEvent(QKeyEvent* e);
    //void mousePressEvent(QMouseEvent *e) override;
    //void mouseReleaseEvent(QMouseEvent *e) override;
    //void timerEvent(QTimerEvent *) override;
protected:
    bool fullscreen;
    GLfloat rTri;
    GLfloat rQuad;
    GLfloat ***vertices = new float**[576];
    GLfloat ***colors = new float**[576];
    GLfloat ****vertices2;
    GLfloat ****colors2;
    QVector<float>x;
    QVector<float>y;
    QVector<float>z;
    QVector<float>r;
    QVector<float>g;
    QVector<float>b;
    QVector<float>a;
    int count =0;

   GLfloat m_xRot; //x旋转角度
   GLfloat m_yRot; //y旋转角度
   GLfloat m_xSpeed; //x旋转速度
   GLfloat m_ySpeed; //旋转速度
   GLfloat m_Deep;    //深入屏幕的距离
   GLfloat m_x;
   GLfloat m_y;
};

#endif // NEHEWIDGET_H
