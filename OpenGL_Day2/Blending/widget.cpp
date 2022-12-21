#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    alpha = 0.5f;
    src = GL_SRC_ALPHA;
    dest = GL_ONE_MINUS_SRC_ALPHA;

    setWindowTitle("OpenGL Blending");
    resize(600, 600);
}

Widget::~Widget()
{

}

void Widget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0, 1.0);
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

    glEnable(GL_BLEND);
    glBlendFunc(src, dest);

    glColor3f(0, 0, 1);
    glRectf(-0.5, 0.8, 0.5, 0.0);

    glColor4f(1, 0, 0, alpha);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()){
    case Qt::Key_Up:
        alpha += 0.1;
        break;
    case Qt::Key_Down:
        alpha -= 0.1;
        break;
    case Qt::Key_Left:
        src = GL_ONE;
        dest = GL_ZERO;
        break;
    case Qt::Key_Right:
        src = GL_SRC_ALPHA;
        dest = GL_ONE_MINUS_SRC_ALPHA;
        break;
    };

    update();
}
