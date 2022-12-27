#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstdlib>
#include <QRandomGenerator>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("OpenGL Tank Game");

    tankPosHoriz = 0.0f;
    firstShot = true;
    headB = NULL;

    srand(time(0));

    resize(500, 500);

    normalEnemy.ypos = 2.5;
    normalEnemy.speed = .02;
    normalEnemy.xpos = -22+(QRandomGenerator::global()->generate()%45);
    normalEnemy.xpos = normalEnemy.xpos*.1;
    enemyAround = FALSE;

    connect(&timer, SIGNAL(timeout()), SLOT(updateTimer()));
    timer.start(1000/60);
}

Widget::~Widget()
{
}

int Widget::loadGLTextures()            // Load Bitmaps And Convert To Textures
{
    int Status = false;                                   // Status Indicator

    QImage* image1 = new QImage("barrel.bmp");
    GLubyte *data1 = image1->bits( );

    glGenTextures(1, &texture[0]);                  // Create Three Textures
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->size().width(),
                      image1->size().height(),
                      GL_RGB, GL_UNSIGNED_BYTE, data1);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);

    QImage* image2 = new QImage("normalshot3.bmp");
    GLubyte *data2 = image2->bits( );
    image2->mirror();
    glGenTextures(1, &texture[1]);                  // Create Three Textures

    // Create MipMapped Texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image2->size().width(),
                      image2->size().height(),
                      GL_BGRA, GL_UNSIGNED_BYTE, data2);

    QImage* image3 = new QImage("ground.bmp");
    GLubyte *data3 = image3->bits( );
    image3->mirror();
    glGenTextures(1, &texture[2]);                  // Create Three Textures

    // Create MipMapped Texture
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image3->size().width(),
                      image3->size().height(),
                      GL_BGRA, GL_UNSIGNED_BYTE, data3);

    QImage* image4 = new QImage("opencom.jpg");
    GLubyte *data4 = image4->bits( );
    glGenTextures(1, &texture[3]);                  // Create Three Textures

    // Create MipMapped Texture
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image4->size().width(),
                      image4->size().height(),
                      GL_BGRA, GL_UNSIGNED_BYTE, data4);

    QImage* image5 = new QImage("closedcom.jpg");
    GLubyte *data5 = image5->bits( );
    image5->mirror();
    glGenTextures(1, &texture[3]);                  // Create Three Textures

    // Create MipMapped Texture
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image5->size().width(),
                      image5->size().height(),
                      GL_BGRA, GL_UNSIGNED_BYTE, data5);
    Status = true;                                    // Set The Status To TRUE

    return Status;                                      // Return The Status
}


void Widget::initializeGL( )
{
    initializeOpenGLFunctions( );
    loadGLTextures();

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
}

void Widget::resizeGL(int w, int h)
{
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Widget::paintGL( )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                   // Reset The View
    glTranslatef(0.0,0.0f,-7.0f);

    //untextured stuff first (drawn in the correct order :D  )
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    //draws the grass
    //glColor3f(0.0, 0.7, 0.0);

        //draws the main part of the tank>>>>>>>>>>>>>>>>>>>>
        glColor3f(0.5, 0.5, 0.5);
        //left side======================================
        glVertex3f((tankPosHoriz-0.4), -1.61f, 1.0f);
        glVertex3f((tankPosHoriz-0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.0f);
        //
        glVertex3f((tankPosHoriz-0.4), -1.61f, 1.0f);
        glVertex3f((tankPosHoriz-0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz-0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz-0.4), -1.71f, 1.0f);
        //
        glVertex3f((tankPosHoriz-0.4), -1.71f, 1.0f);
        glVertex3f((tankPosHoriz-0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.81f, 1.0f);
        //right side=====================================
        glVertex3f((tankPosHoriz+0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz+0.4), -1.61f, 1.0f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.0f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.2f);
        //
        glVertex3f((tankPosHoriz+0.4), -1.61f, 1.0f);
        glVertex3f((tankPosHoriz+0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz+0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz+0.4), -1.71f, 1.0f);
        //
        glVertex3f((tankPosHoriz+0.4), -1.71f, 1.0f);
        glVertex3f((tankPosHoriz+0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.81f, 1.0f);
        //front side=====================================
        //main part
        glVertex3f((tankPosHoriz-0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.2f);
        //left gap fill
        glVertex3f((tankPosHoriz-0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz-0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz-0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.2f);
        //right gap fill
        glVertex3f((tankPosHoriz+0.3), -1.81f, 1.2f);
        glVertex3f((tankPosHoriz+0.4), -1.71f, 1.2f);
        glVertex3f((tankPosHoriz+0.4), -1.61f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.2f);
        //top============================================
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz+0.3), -1.51f, 1.0f);
        glVertex3f((tankPosHoriz-0.3), -1.51f, 1.0f);
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //draws the contrast part of the tank
        glColor3f(0.6, 0.6, 0.6);
        //left side contrast gap
        glVertex3f((tankPosHoriz-0.3), -1.54, 1.21f);
        glVertex3f((tankPosHoriz-0.38), -1.62f, 1.21f);
        glVertex3f((tankPosHoriz-0.38), -1.70f, 1.21f);
        glVertex3f((tankPosHoriz-0.3), -1.78f, 1.21f);
        //right side contrast gap
        glVertex3f((tankPosHoriz+0.3), -1.54, 1.21f);
        glVertex3f((tankPosHoriz+0.38), -1.62f, 1.21f);
        glVertex3f((tankPosHoriz+0.38), -1.70f, 1.21f);
        glVertex3f((tankPosHoriz+0.3), -1.78f, 1.21f);
        //main contrast
        glVertex3f((tankPosHoriz-0.3), -1.78f, 1.21f);
        glVertex3f((tankPosHoriz+0.3), -1.78f, 1.21f);
        glVertex3f((tankPosHoriz+0.3), -1.54f, 1.21f);
        glVertex3f((tankPosHoriz-0.3), -1.54f, 1.21f);
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //turret draw
        //front
        glVertex3f((tankPosHoriz-0.2), -1.41f, 1.2f);
        glVertex3f((tankPosHoriz+0.2), -1.41f, 1.2f);
        glVertex3f((tankPosHoriz+0.2), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz-0.2), -1.51f, 1.2f);
        //right side
        glVertex3f((tankPosHoriz+0.2), -1.41f, 1.0f);
        glVertex3f((tankPosHoriz+0.2), -1.41f, 1.2f);
        glVertex3f((tankPosHoriz+0.2), -1.51f, 1.2f);
        glVertex3f((tankPosHoriz+0.2), -1.51f, 1.0f);
        //left side
        glVertex3f((tankPosHoriz-0.2), -1.41f, 1.2f);
        glVertex3f((tankPosHoriz-0.2), -1.41f, 1.0f);
        glVertex3f((tankPosHoriz-0.2), -1.51f, 1.0f);
        glVertex3f((tankPosHoriz-0.2), -1.51f, 1.2f);
        //top turret
        glVertex3f((tankPosHoriz+0.2), -1.41f, 1.0f);
        glVertex3f((tankPosHoriz-0.2), -1.41f, 1.0f);
        glVertex3f((tankPosHoriz-0.2), -1.41f, 1.2f);
        glVertex3f((tankPosHoriz+0.2), -1.41f, 1.2f);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //barrel draw

    glEnd();
    //TEXTURED DRAWING PART

    //resets the color so the textured surfaces display correctly
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f((tankPosHoriz+0.05), -1.41f, 1.1f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f((tankPosHoriz-0.05), -1.41f, 1.1f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f((tankPosHoriz-0.05), -1.21f, 1.1f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f((tankPosHoriz+0.05), -1.21f, 1.1f);
    glEnd();

    //enemy part
    //glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0f);glVertex3f((normalEnemy.xpos-0.15),
                 normalEnemy.ypos+.4, 1.2f);
        glTexCoord2f(1.0f, 1.0f);glVertex3f((normalEnemy.xpos+0.15),
                 normalEnemy.ypos+.4, 1.2f);
        glTexCoord2f(1.0f, 0.0f);glVertex3f((normalEnemy.xpos+0.15),
                 (normalEnemy.ypos), 1.2f);
        glTexCoord2f(0.0f, 0.0f);glVertex3f((normalEnemy.xpos-0.15),
                 (normalEnemy.ypos), 1.2f);
    glEnd( );


    //grass part
    //glColor3f(0.0, 0.95, 0.0);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(2.5, -1.6f,  1.0f);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(0, -1.6f,  1.0f);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(0, -2.5f,  1.0f);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(2.5, -2.5f,  1.0f);

        glTexCoord2f(0.0f, 0.0f);glVertex3f(0, -1.6f,  1.0f);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-2.5, -1.6f,  1.0f);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-2.5, -2.5f,  1.0f);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(0, -2.5f,  1.0f);
    glEnd();

    if(headB != NULL) {
        //draws the bullets
        glColor3f(1.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBegin(GL_QUADS);
            currentB = headB;
            glColor3f(1.0, 1.0, 1.0);
            while(currentB != NULL) {
                glTexCoord2f(0.0f, 0.0f); glVertex3f((currentB->xpos-.07), (currentB->ypos),  1.09f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f((currentB->xpos+.07), (currentB->ypos),  1.09f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f((currentB->xpos+.07), (currentB->ypos+.2),  1.09f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f((currentB->xpos-.07), (currentB->ypos+.2),  1.09f);
                currentB = currentB->next;
            };
        glEnd();
    }

    glFlush();
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    int x, y;
    x = ev->x();
    y = ev->y();

    update();
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
    case Qt::Key_X:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case Qt::Key_Escape:
        qApp->quit();
        break;
    case Qt::Key_Left:
        (tankPosHoriz > -2.5)?tankPosHoriz -= .06f:tankPosHoriz=2.4;
        break;
    case Qt::Key_Right:
        (tankPosHoriz < 2.5)?tankPosHoriz += .06f:tankPosHoriz=-2.4;
        break;
    case Qt::Key_Space:
    {
        bullet *shot;
        shot = new bullet;
        if(firstShot == TRUE) {
            headB = shot;
            currentB = headB;
            tailB = currentB;
            tailB->next = NULL;
            currentB->xpos = tankPosHoriz;
            currentB->ypos = -1.3;
            currentB->speed = .03;
            currentB->next = NULL;
            firstShot = false;
        } else {
            currentB = tailB;
            currentB->next = shot;
            currentB = shot;
            currentB->next = NULL;
            currentB->xpos = tankPosHoriz;
            currentB->ypos = -1.3;
            currentB->speed = .03;
            tailB = currentB;
        }
        lastShot = newShot;
    }

        break;
    default:
        break;
    }

    update();
}

void Widget::updateTimer()
{
    lastMove = newMove;

    checkScore( );

    if(firstShot == FALSE)
        updateBullet();
    if(enemyAround == FALSE) {
        normalEnemy.ypos = 2.5;
        normalEnemy.speed = .02;
        normalEnemy.xpos = -22+(QRandomGenerator::global()->generate()%45);
        normalEnemy.xpos = normalEnemy.xpos*.1;
        enemyAround = TRUE;
    }

    if (checkCollision( ) == go) {
        score += 10;
        snakeList.append(QPoint(snakeList[snakeList.count( ) - 1].x( ),
                         snakeList[snakeList.count( ) - 1].y( )));
        drawRandomBlock( );
    } else if (checkCollision( ) == stop) {
        levelText = "Game Over!!";
        timer.stop( );
        update( );
        return;
    }

    updateEnemy();

    update();
}

void Widget::updateBullet() {
    currentB = headB;
    if(currentB->ypos > 2.5) {
        if(currentB->next != NULL) {
            currentB = currentB->next;
            delete headB;
            headB = currentB;
            qDebug("updateBullet: currentB");
        }
        else {
            firstShot = TRUE;
            qDebug("updateBullet: firstShot");
        }
    }

    while(currentB != NULL) {
        currentB->ypos = (currentB->ypos + currentB->speed);
        currentB = currentB->next;
    }
}

void Widget::updateEnemy()
{
    if(normalEnemy.ypos > - 1.7)
    {
        normalEnemy.ypos = normalEnemy.ypos - normalEnemy.speed;
    }
    else
    {
        enemyAround = FALSE;
        qDebug("updateEnemy:enemyAround");
    }
}

void Widget::checkScore( )
{
}

int Widget::checkCollision( )
{
    if ((-80 + normalEnemy.xpos) == blockX && 80 + normalEnemy.ypos == blockY &&
            (-72 + normalEnemy.xpos) == blockX + 8 && 72 + normalEnemy.ypos == blockY - 8)
        return go;
    if ((-80 + xpos) >= 92 || (-80 + xpos) <= -100 ||
            (80 + ypos) >= 100 || (80 + ypos) <= -92)
        return stop;

    for (int i = 1; i < snakeList.count( ); i++) {
        if (xpos == snakeList[i].x( ) && ypos == snakeList[i].y( ))
            return stop;
    };

    return -1;
}

void Widget::drawRandomBlock( )
{
    int neg = randomMinMax(-5, 5);
    blockX = randomMinMax(11) * 8 * (neg > 0 ? 1 : -1);
    neg = randomMinMax(-5, 5);
    blockY = randomMinMax(11) * 8 * (neg > 0 ? 1 : -1);
}
