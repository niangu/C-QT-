#include "myopenglwidget.h"
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include<QKeyEvent>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    translate=-6.0;
    xRot=zRot=0.0;
    yRot=-30.0;

}

void MyOpenGLWidget::initializeGL()
{
    //for(int i=0;i<2;++i)
        //textures[i]=new QOpenGLTexture(QImage(QString("/home/niangu/桌面/QT/绘图动画/myopengl/side%1.png").arg(i+1)).mirrored());
    //为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    //创建顶点着色器
    QOpenGLShader *vshader=new QOpenGLShader(QOpenGLShader::Vertex,this);
    const char *vsrc=
            "in vec4 vPosition;                    \n"
            "in vec4 vColor;                     \n"
            "out vec4 color;                     \n"
            "uniform mat4 matrix;                   \n"
            "void main(){                          \n"
            "   color=vColor;                       \n"
            "   gl_Position=matrix * vPosition;             \n"
            "}                                     \n";
    vshader->compileSourceCode(vsrc);
    //创建片段着色器
    QOpenGLShader *fshader=new QOpenGLShader(QOpenGLShader::Fragment,this);
    const char *fsrc=
            "uniform sampler2D tex;    \n"
            "in vec4 color;           \n"
            "out vec4 fColor;          \n"
            "void main(){               \n"
            "  fColor=color;              \n"
            "}                           \n";
    fshader->compileSourceCode(fsrc);
    //创建着色器程序
    program=new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);
    program->link();
    program->bind();

}
void MyOpenGLWidget::resizeGL(int w, int h)
{

}
void MyOpenGLWidget::paintGL()
{
    int w=width();
    int h=height();
    int side=qMin(w,h);
    glViewport((w-side)/2,(h-side)/2,side,side);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //定点位置
    GLfloat vertices[2][4][3]={
        {{-0.8f,0.8f,0.8f},{-0.8f,-0.8f,0.8f},{0.8f,-0.8f,0.8f},{0.8f,0.8f,0.8f}},
        {{0.8f,0.8f,0.8f},{0.8f,-0.8f,0.8f},{0.8f,-0.8f,-0.8f},{0.8f,0.8f,-0.8f}}
    };
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,48*sizeof(GLfloat));
    GLuint vPosition=program->attributeLocation("vPosition");
    //glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,vertices);
    program->setAttributeBuffer(vPosition,GL_FLOAT,0,3,0);
    glEnableVertexAttribArray(vPosition);
    GLfloat colors[2][4][3]={
        {{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0},{1.0f,1.0f,1.0}},
        {{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,0.1f},{1.0f,1.0f,1.0f}}

    };
    vbo.write(24*sizeof(GLfloat),colors,24*sizeof(GLfloat));
    GLuint vColor=program->attributeLocation("vColor");
    program->setAttributeBuffer(vColor,GL_FLOAT,24*sizeof(GLfloat),3,0);
    glEnableVertexAttribArray(vColor);
    program->setUniformValue("tex",0);
    QMatrix4x4 matrix;
    matrix.perspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    matrix.translate(0,0,translate);
    matrix.rotate(xRot,1.0,0.0,0.0);//绕Y轴逆时针旋转
    matrix.rotate(yRot,0.0,1.0,0.0);
    matrix.rotate(zRot,0.0,0.0,1.0);
    program->setUniformValue("matrix",matrix);

for(int i=0;i<2;i++){
    glDrawArrays(GL_TRIANGLE_FAN,i*4,4);
}
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        xRot+=10;
        break;
    case Qt::Key_Left:
        yRot+=10;
        break;
    case Qt::Key_Right:
        zRot+=10;
        break;
    case Qt::Key_Down:
        translate-=1;
        break;
    case Qt::Key_Space:
        translate+=1;
        break;
    default:
        break;
    }
    update();//更新显示
    QOpenGLWidget::keyPressEvent(event);
}
