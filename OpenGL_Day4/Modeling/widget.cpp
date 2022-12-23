#include "widget.h"
#include <GL/glut.h>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), Action(0)
{
    setWindowTitle("OpenGL Modeling");
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
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* // 주전자 그리기, 이동
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glutWireTeapot(0.2);

    glPushMatrix();
    glTranslatef(0.6, 0.0, 0.0);
    glutWireTeapot(0.2);
    glPopMatrix();

    //glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glutWireTeapot(0.2);
    glPopMatrix();

    glFlush();
    */

    /* // scale, 반전
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(-2.0, 3.0, 1.0);       // 양수면 scale, 음수면 뒤집기

    glutWireTeapot(0.2);

    glPopMatrix();
    */

    /*// 회전
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90.0,1.0, 0.0, 0.0);       // 양수면 scale, 음수면 뒤집기

    glutWireTeapot(0.4);

    glPopMatrix();
    glFlush();
    */

    /* // 복합변환1(teapot)
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1.5, 1.5, 1.0);            // 좌표이동후 확대하는것과 확대후 좌표이동하는건 다르게보임
    glTranslatef(0.5, 0.5, 0.0);        // 좌표가확대될시 이동범위가 달라지기때문

    glutWireTeapot(0.2);
    glPopMatrix();
    glFlush();
    */
    /* // 복합변환2(triangle)
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.8, 0.2);
    glEnd();

    glRotatef(45.0, 0.0, 0.0, 1.0);

    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.8, 0.2);
    glEnd();

    glPopMatrix();
    glFlush();
    */

    /*// 복합변환3(triangle)
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.8, 0.2);
    glEnd();

    glTranslatef(0.5, 0.5, 0.0);
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, -0.5, 0.0);

    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.8, 0.2);
    glEnd();

    glPopMatrix();
    glFlush();
    */

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);

    switch(event->key()) {
    case Qt::Key_1:
//        yAngle += 2;
        break;
    case Qt::Key_2:
//        yAngle -= 2;
        break;
    case Qt::Key_3:
//        xAngle += 2;
        break;
    case Qt::Key_4:
//        xAngle -= 2;
        break;
    case Qt::Key_5:
//        zAngle += 2;
        break;
    case Qt::Key_6:
//        zAngle -= 2;
        break;
    case Qt::Key_0:
//        xAngle = yAngle = zAngle = 0.0;
        break;

    case Qt::Key_A:
//        ex += 0.1;
        break;
    case Qt::Key_S:
//        ex -= 0.1;
        break;
    case Qt::Key_D:
//        ey -= 0.1;
        break;
    case Qt::Key_F:
//        ex += 0.1;
        break;
    case Qt::Key_G:
//        ez += 0.1;
        break;
    case Qt::Key_H:
//        ez -= 0.1;
        break;
    case Qt::Key_J:
//        ex = ey = ez = 0.0;
        break;
    }

//    QString str = QString("ex : %1, ey : %2, ez : %3")
//            .arg(ex).arg(ey).arg(ez);
//    setWindowTitle(str);

    update();

}
