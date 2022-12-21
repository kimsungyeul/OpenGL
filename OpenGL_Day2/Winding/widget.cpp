#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    bCullFace = GL_FALSE;
    bCcwFront = GL_TRUE;

    setWindowTitle("OpenGL Culling3D");
    resize(600, 600);
}

Widget::~Widget()
{

}

void Widget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(bCullFace) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    glFrontFace(bCcwFront ? GL_CCW : GL_CW);

    /* // 원점좌표고정후 그리기
    // CCW
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.9, -0.5);
        glVertex2f(-0.1, -0.5);
    glEnd();

    // CW
    glBegin(GL_POLYGON);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.9, -0.5);
        glVertex2f(0.1, -0.5);
    glEnd();
    */

    // 원점좌표이동으로 그리기
    glPushMatrix( );
    glTranslatef(-0.5f, 0.0f, 0.0f);
    // CCW
    glBegin(GL_POLYGON);
      glVertex2f(0.0, 0.5);
      glVertex2f(-0.4, -0.5);
      glVertex2f(0.4, -0.5);
    glEnd( );
    glTranslatef(1.0f, 0.0f, 0.0f);
    // CW
    glBegin(GL_POLYGON);
      glVertex2f(0.0, 0.5);
      glVertex2f(0.4, -0.5);
      glVertex2f(-0.4, -0.5);
    glEnd( );
    glPopMatrix( );
    glFlush();
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()){
    case Qt::Key_Up:
        bCullFace = GL_TRUE;
        break;
    case Qt::Key_Down:
        bCullFace = GL_FALSE;
        break;
    case Qt::Key_Left:
        bCcwFront = GL_TRUE;
        break;
    case Qt::Key_Right:
        bCcwFront = GL_FALSE;
        break;
    };

    QString str = QString("Cull : %1, Front : %2")
            .arg(bCullFace ? "ON" : "OFF").arg(bCcwFront ? "CCW" : "CW");
    setWindowTitle(str);
    update();
}
