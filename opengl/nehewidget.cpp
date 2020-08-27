#include "nehewidget.h"
#include "util.h"
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include<QKeyEvent>
#include<math.h>
#include<QTime>
#include<thread>
#include<QDir>
#include<QTimer>

NeHeWidget::NeHeWidget(QWidget* parent, const char* name, bool fs )
    : QOpenGLWidget(parent)
{
    rTri = 0;
    rQuad = 0.0;
    fullscreen = fs;
    setGeometry(0,0,640,576);
    if ( fullscreen )
       showFullScreen();

    //test = new QVector<int>(368640,0);
    //QVector<QVector<QVector<float>>>dist_vec_1(576,QVector<QVector<float>>(640,QVector<float>(3,0.0)));
    QVector<float> te(368640,0);
    x = te;
    y = te;
    z = te;
    r = te;
    g = te;
    b = te;
    a = te;
    m_xRot = 0.0f;
    m_yRot = 0.0f;
    m_xSpeed = 0.0f;
    m_ySpeed = 0.0f;
    m_Deep = -5.0f;
    m_x = 0.0f;
    m_y = 0.0f;

    //QTimer *timer = new QTimer(this);                   //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    //timer->start(10);                                   //以10ms为一个计时周期


}
NeHeWidget::~NeHeWidget()
{
}

void NeHeWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0 );
    glOrtho(-100,100,-100,100,-100,100);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void test_display(){
    glPushAttrib(GL_CURRENT_COLOR);
    glColor3f(1.0, 0, 0);
    glBegin(GL_TRIANGLES);
     glVertex3f( 0.0f, 1.0f, 0.0f);     // Top
     glVertex3f(-1.0f,-1.0f, 0.0f);     // Bottom Left
     glVertex3f( 1.0f,-1.0f, 0.0f);     // Bottom Right
    glEnd();           // Finished Drawing The Triangle
    glPopAttrib();
}

void test_display2(){
    glPushAttrib(GL_CURRENT_COLOR);
    glColor3f(1.0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
        glVertex3f( 0.0f, 1.0f, 0.0f);     // Top
        glVertex3f(-1.0f,-1.0f, 0.0f);     // Bottom Left
        glVertex3f( 1.0f,-1.0f, 0.0f);     // Bottom Right
    glEnd();
    glPopAttrib();
}

void test_display3(){
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0, 0, 0);
    glLineWidth(3);
    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f( 1.0f,-1.0f, 5.0f);
    glEnd();
    glPopAttrib();
}

void NeHeWidget::paintGL()
{


   // QTime time;
   // time.start();
    /*
    代码程序运行
    */

    //qDebug()<<"DDDDDDD";
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef( m_x,  m_y, m_Deep );                     //移入屏幕
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);                //绕x轴旋转
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);                //绕y轴旋转

    //glRotated(90.0,1.0,1.0,0);
    glRotatef(-90.0,0.0,0.0,1.0);//依据Z轴旋转90度
    //test_display();
//    test_display2();
    glPushAttrib(GL_CURRENT_BIT);


    glBegin(GL_LINES);
        glColor3f(1.0, 0, 0);
        glVertex3f(+6.4, +5.7, -94);
        glVertex3f(-6.4, +5.7, -94);
        glVertex3f(+6.4, -5.7, -94);
        glVertex3f(-6.4, -5.7, -94);
        glVertex3f(+6.4, -5.7, +5.9);
        glVertex3f(-6.4, -5.7, +5.9);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0, 0);
        glVertex3f(+6.4, +5.7, +5.9);
        glVertex3f(+6.4, +5.7, -94);
        glVertex3f(+6.4, -5.7, -94);
        glVertex3f(+6.4, -5.7, +5.9);
        glVertex3f(+6.4, +5.7, +5.9);
        glVertex3f(-6.4, +5.7, +5.9);
        glVertex3f(-6.4, +5.7, -94);
        glVertex3f(-6.4, -5.7, -94);
        glVertex3f(-6.4, -5.7, +5.9);
        glVertex3f(-6.4, +5.7, +5.9);
        glEnd();
    //glLineWidth(3);
    glPointSize(2);
    glBegin(GL_POINTS);
//    glVertex3f(-6.4, 1, 0);
//    glVertex3f(6.4, 1, 0);
//    glVertex3f(-6.4, 5.7, 0);
//    glVertex3f(6.4, -5.7, 0);
//    glVertex3f(0, 0, 6);
//    glVertex3f(3.2, 2.5,6);
//    std::thread t1([] (QVector<float>x,QVector<float>y,QVector<float>z)
//    {



//    QDir configPath=QDir::currentPath();

//    if(!configPath.exists("config/picture"))//判断需要创建的文件夹是否存在
//    {
//         configPath.mkdir("config");
//        configPath.mkdir("config/picture"); //创建文件夹
//    }
//    if (!configPath.cd("config/picture"))
//    {
//        qWarning("Cannot find the \"/config\\picture\" directory");
//        return;
//    }

//    QFile file(QString("%1%2point%3.csv").arg(configPath.absolutePath()).arg(QDir::separator()).arg(count));
//    QFile file2(QString("%1%2color%3.csv").arg(configPath.absolutePath()).arg(QDir::separator()).arg(count));
//    //QFile file(QString("%1%2dep_info.csv").arg(configPath.absolutePath()).arg(QDir::separator()));
//        if(file.exists())
//    {
//        file.open(QIODevice::Truncate);
//        file.close();
//        file.resize(0);
//    }
//        if(file2.exists())
//    {
//        file2.open(QIODevice::Truncate);
//        file2.close();
//        file2.resize(0);
//    }

//        for(int i=0;i<640;i++)
//        {
//            //QString str;
//            //QString str2;
//            for(int j=0;j<576;j++)
//            {
//               int dist = 640*j+i;
//               //int dist2 = 576*j+i;
//               float x_p = x[dist]/100.0;
//               float y_p = y[dist]/100.0;
//               float z_p = -(z[dist]/400.0);
//               float b_p = r[dist]/255.0;
//               float g_p = g[dist]/255.0;  ///rgb反了
//               float r_p = b[dist]/255.0;
//               //float a_p = a[dist]/255.0;
//                //if(-6.4<x_p<6.4&&-5.7<y_p<5.7&&(-z_p)<4.7){

//                //glColor4f(r_p, g_p, b_p,a_p);
//                glColor3f(r_p, g_p, b_p);
//                //glColor3f(0.0f, 0, 1.0f);
//                glVertex3f(x_p,y_p,z_p);
//               // }
//                //str.append(QString("%1,%2,%3,").arg(x_p).arg(y_p).arg(z_p));
//                //str2.append(QString("%1,%2,%3,").arg(r_p).arg(g_p).arg(b_p));

//                //qDebug()<<QString("x:%1,y:%2,z:%3,r:%4,g:%5,b:%6").arg(z).arg(y).arg(z).arg(r).arg(g).arg(b);
//            }
//        }



        for(int i=0;i<368640;i++)
        {
            float x_p = x[i]/10.0;
            float y_p = y[i]/10.0;
            float z_p = -(z[i]/10.0);
            float b_p = r[i]/255.0;
            float g_p = g[i]/255.0;  ///rgb反了
            float r_p = b[i]/255.0;
            glColor3f(r_p, g_p, b_p);
            glVertex3f(x_p,y_p,z_p);
        }



//                            if(!file.exists())
//                            {
//                                if (file.open(QIODevice::WriteOnly | QIODevice::Append))
//                                {
//                                    QTextStream out(&file);
//                                    out <<str<<endl;
//                                    file.close();
//                                }
//                            }
//                            else
//                            {
//                                if (file.open(QIODevice::WriteOnly | QIODevice::Append))
//                                {
//                                    QTextStream out(&file);
//                                    out <<str<<endl;
//                                    file.close();
//                                }
//                            }
//                            if(!file2.exists())
//                            {
//                                if (file2.open(QIODevice::WriteOnly | QIODevice::Append))
//                                {
//                                    QTextStream out(&file2);
//                                    out <<str2<<endl;
//                                    file2.close();
//                                }
//                            }
//                            else
//                            {
//                                if (file2.open(QIODevice::WriteOnly | QIODevice::Append))
//                                {
//                                    QTextStream out(&file2);
//                                    out <<str2<<endl;
//                                    file2.close();
//                                }
//                            }
       // }

//    },x,y,z);
//    t1.join();


    glEnd();
    glPopAttrib();
    update();
    m_xRot += m_xSpeed;   //x轴旋转
    m_yRot += m_ySpeed;   //y轴旋转
    //count+=1;
//    glBegin(GL_POINTS);
//    glTranslatef( 0,  0.0, 0 );
//    glPointSize(40);
//    glColor3f(1, 0, 0);
//    glVertex3f(0, 0, 0);
    //glFlush();
    //qDebug()<<"代码程序1运行时间："+time.elapsed();

}

void NeHeWidget::resizeGL(int w, int h)
{
    if ( h == 0 )
      {
        h = 1;
      }
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //gluPerspective( 45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0 );
    GLfloat zNear = 0.1;
    GLfloat zFar = 100;                                 //绘制深度的起点和终点，0.1到100
    GLfloat aspect = (GLfloat)w/(GLfloat)h;
    GLfloat fH = tan(GLfloat(90.0/360.0*3.14159))*zNear;
    GLfloat fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void NeHeWidget::setParam(float ****vec, float ****vec2)
{
    vertices2 = vec;
    colors2 = vec2;

//    for(int i=0;i<576;i++)
//    {
//        for(int j=0;j<640;j++)
//        {
//            vertices[i][j][0] = vec[i][j][0];
//            vertices[i][j][1] = vec[i][j][1];
//            vertices[i][j][2] = vec[i][j][2];
//            colors[i][j][0] = vec2[i][j][0];
//            colors[i][j][1] = vec2[i][j][1];
//            colors[i][j][2] = vec2[i][j][2];
//        }
    //    }
}

void NeHeWidget::setParam2(QVector<float> *x_1, QVector<float> *y_1, QVector<float> *z_1,QVector<float>*r1,QVector<float>*g1,QVector<float>*b1,QVector<float>*a1)
{
    x = *x_1;
    y = *y_1;
    z = *z_1;
    r = *r1;
    g = *g1;
    b = *b1;
    a = *a1;

}





void NeHeWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
     {
     case Qt::Key_F2:
       fullscreen = !fullscreen;
       if ( fullscreen )
       {
         showFullScreen();
       }
       else
       {
         showNormal();
         setGeometry( 0, 0, 640, 576);
       }
       update();
       break;
     case Qt::Key_Escape:
       close();
        break;
     case Qt::Key_PageUp:
        m_Deep -= 3.0f;
        break;
     case Qt::Key_PageDown:
        m_Deep += 3.0f;
        break;
     case Qt::Key_Up:
        m_xRot -= 3.0f;
        break;
     case Qt::Key_Down:
        m_xRot += 3.0f;
        break;
     case Qt::Key_Right:
        m_yRot -= 3.0f;
        break;
     case Qt::Key_Left:
        m_yRot += 3.0f;
        break;
     case Qt::Key_A:
        m_y -= 3.0f;
        break;
     case Qt::Key_D:
          m_y += 3.0f;
        break;
     case Qt::Key_W:
        m_x -= 3.0f;
        break;
     case Qt::Key_S:
        m_x += 3.0f;
        break;
}
}

