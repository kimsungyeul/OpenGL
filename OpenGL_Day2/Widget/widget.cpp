#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    rectPosX = 0.0f;
    rectPosY = 0.0f;
    rectSize = 250;

    xStep = 5.0f;
    yStep = 5.0f;

    setWindowTitle("Hello OpenGL");
    resize(600, 600);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(timerFunction()));
    timer->start(1000/60);
}

Widget::~Widget()
{

}

void Widget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h)
{
    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void Widget::paintGL()
{
    /*// TRIANGLES
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLES);
        GLfloat x = -0.8;
        GLfloat y = 0.4;
        for(int i=0; i<6; i++){
            glVertex2f(x, y);
            x += 0.3;
            y *= -1;
        };
    glEnd();

    glFlush();
    */

    /*// TRIANGLE_STRIP
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLE_STRIP);
        GLfloat x = -0.8;
        GLfloat y = 0.4;
        for(int i=0; i<6; i++){
            if(i%2 == 0) {
                glColor3f(1.0, 0.0, 0.0);
            } else {
                glColor3f(0.0, 1.0, 0.0);
            }

            glVertex2f(x, y);
            x += 0.3;
            y *= -1;
        };
    glEnd();

    glFlush();
    */

    /*// TRIANGLE_FAN
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.35, 0.35);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.5, 0.0);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.35, -0.35);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.0, -0.5);
    glEnd();

    glFlush();
    */

    /* // glRectf() 함수
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glRectf(-0.8, 0.8, 0.8, -0.8);

    glFlush();
    */

    /* // GL_POLYGON
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, 0.0);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.0, -0.5);
    glEnd();

    glFlush();
    */

    /*// GL_TRIANGLES_다각형
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, 0.0);
        glVertex2f(0.0, 0.0);

        glVertex2f(0.0, 0.0);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.0, -0.5);
    glEnd();

    glFlush();
    */

}

void Widget::timerFunction()
{
    if(rectPosX > windowWidth-rectSize || rectPosX < -windowWidth)
        xStep = -xStep;

    if(rectPosY > windowHeight || rectPosY < -windowHeight + rectSize)
        yStep = -yStep;

    rectPosX += xStep;
    rectPosY += yStep;

    if(rectPosX > (windowWidth - rectSize + xStep))
        rectPosX = windowWidth - rectSize -1;
    else if(rectPosX < -(windowWidth + xStep))
        rectPosX = -windowWidth - 1;

    if(rectPosY > (windowHeight + yStep))
        rectPosY = windowHeight -1;
    else if(rectPosY < -(windowHeight - rectSize + yStep))
        rectPosY = -windowHeight + rectSize -1;

    repaint();
}
