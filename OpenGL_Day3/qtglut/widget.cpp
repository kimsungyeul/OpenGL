#include "widget.h"
#include "qtglut.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    xAngle = yAngle = zAngle = 0;
    setWindowTitle("OpenGL QtGLUT");
    resize(600, 600);
}

Widget::~Widget()
{

}

void Widget::initializeGL( ) {
    initializeOpenGLFunctions( );
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix( );
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 0.1f);
    // 와이어 큐브
    glPushMatrix( );
    glTranslatef(-0.6, 0.6, 0.0);
    glutWireCube(0.4);
    glPopMatrix( );

    glColor3f(0.0f, 1.0f, 0.0f);
    // 와이어 구
    glPushMatrix( );
    glTranslatef(-0.6, -0.6, 0.0);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix( );

    glColor3f(1.0f, 1.0f, 0.0f);
    // 와이어 원뿔
    glPushMatrix( );
    glTranslatef(0.6, 0.6, 0.0);
   // glutWireCone(0.3, 0.6, 20, 10);
    glPopMatrix( );

    glColor3f(1.0f, 0.0f, 0.0f);
    // 와이어 도너츠
    glPushMatrix( );
    glTranslatef(0.6, -0.6, 0.0);
    glutWireTorus(0.1, 0.2, 20, 20);
    glPopMatrix( );

    glPopMatrix( );
    glFlush( );
}
