#include "widget.h"

#include <QTimer>

#ifdef Q_OS_MACOS
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#define ONE 1

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    xAngle = yAngle = zAngle = 0;
    rotation = 0;
    drawInOrtho = GL_TRUE;

    setWindowTitle("OpenGL Cube3D");
    resize(300, 300);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout( )), SLOT(update( )));
    timer->start(250);
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
    glOrtho(-10, 10, -10, 10, -10, 10);
    glClearColor(0.5, 0.5, 0.5, 0.0);
}

void Widget::paintGL( )
{
    // ?뺤쑁硫댁껜??媛?硫대뱾???ㅼ젙
    // ?뺤쑁硫댁껜?닿린 ?뚮Ц??6媛쒖쓽 face 瑜??ㅼ젙?덈떎.
    // 諛⑺뼢???뚮Ц???쒖꽌???쇨??깆씠 ?덈떎.
    static GLubyte front[]  = {3,0,2,1}; 	// front face
    static GLubyte back[]   = {6,5,7,4}; 	// back face
    static GLubyte top[]    = {2,6,3,7}; 	// top face
    static GLubyte bottom[] = {5,1,4,0}; 	// bottom face
    static GLubyte left[]   = {7,4,3,0}; 		// left face
    static GLubyte right[]  = {2,1,6,5}; 		// right face

    // X,Y,Z 濡???醫뚰몴(瑗?????대떎.
    // ?덈? ?ㅻ㈃ face ?먯꽌 ?ㅼ젙??0 ? (-5,-5,-,5) ?대떎.
    static GLshort vertices[] = {-5,-5,-5,  5,-5,-5,  5,5,-5,
                       -5,5,-5,  -5,-5,5,   5,-5,5,   5,5,5,  -5,5,5};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);       // 3李⑥썝??媛앹껜瑜?洹몃┫ ???ъ슜
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

    if(!drawInOrtho)
      glTranslated(0, 0, -30);

    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);

    // Y 異?湲곗??쇰줈 45???뚯쟾(Rotate)
    glRotated(45, ONE, 0, 0);
    glRotated(rotation++, 0, ONE,0);

    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    // ?ъ슜??vertex 瑜??깅줉
    glVertexPointer(3, GL_SHORT, 0, vertices);

    // 6媛쒖쓽 face 瑜?媛곴컖 Draw
    // 媛?face 瑜??ㅻⅨ ?됱쑝濡??쒗쁽?쒕떎.
    glColor4d(ONE,0,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, front);

    glColor4d(0,ONE,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, back);

    glColor4d(0,0,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, top);

    glColor4d(ONE,ONE,0,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, bottom);

    glColor4d(0,ONE,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, left);

    glColor4d(ONE,0,ONE,0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, right);

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush( );
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key( )) {

    case Qt::Key_1:
        yAngle += 2;
        break;
    case Qt::Key_2:
        yAngle -= 2;
        break;
    case Qt::Key_3:
        xAngle += 2;
        break;
    case Qt::Key_4:
        xAngle -= 2;
        break;
    case Qt::Key_5:
        zAngle += 2;
        break;
    case Qt::Key_6:
        zAngle -= 2;
        break;
    case Qt::Key_0:
        xAngle = yAngle = zAngle = 0.0;
        break;
    };

    QString str = QString("Cube3D : x : %1, y : %2, z : %3")
                 .arg(xAngle).arg(yAngle).arg(zAngle);
    setWindowTitle(str);
    update( );
}
