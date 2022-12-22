#include "widget.h"
#include "qtglut.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    xAngle = yAngle = zAngle = 0;
    setWindowTitle("OpenGL GLUT3D");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
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

    glPushMatrix();

    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    //glutWireTeapot(0.3);

    glPushMatrix();
    glTranslatef(-0.6, 0.6, 0.0);
    glutWireCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -0.6, 0.0);
    glutWireSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, 0.6, 0.0);
    //glutWireCone(0.3, 0.6, 20, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, -0.6, 0.0);
    glutWireTorus(0.1, 0.2, 20, 20);
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
        yAngle += 2;
        break;
    case Qt::Key_Down:
        yAngle -= 2;
        break;
    case Qt::Key_Left:
        xAngle -= 2;
        break;
    case Qt::Key_Right:
        xAngle += 2;
        break;
//    case Qt::Key_1:
//        polygonMode = GL_POINT;
//        break;
//    case Qt::Key_2:
//        polygonMode = GL_LINE;
//        break;
//    case Qt::Key_3:
//        polygonMode = GL_FILL;
//        break;
//    case Qt::Key_4:
//        shadeMode = GL_SMOOTH;
//        break;
//    case Qt::Key_5:
//        shadeMode = GL_FLAT;
//        break;
    }

//    QString str = QString("Pyramid3D -> x: %1, y: %2, z: %3").arg(xAngle)
//            .arg(yAngle).arg(zAngle);
//    setWindowTitle(str);
    update();

}
