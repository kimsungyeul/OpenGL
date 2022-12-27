#ifndef WIDGET_H
#define WIDGET_H

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QWidget>

#include <GL/glut.h>
#include <GL/glu.h>

struct bullet {
    float ypos;
    float xpos;
    float speed;
    bullet *next;
};

struct enemy {
    float ypos;
    float xpos;
    float speed;
    enemy *next;
};

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    enum game { go, stop };

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    GLuint filter;          // which filter to use
    GLuint texture[4];      // Storage for 3 textures
    GLuint base;

    bullet *headB;
    bullet *tailB;
    bullet *currentB;

    bool firstShot;
    bool enemyAround;
    float tankPosHoriz;
    float lastShot;
    float newShot;
    float lastMove, newMove;
    int score;

    enemy normalEnemy;

    GLUquadricObj *quadratic;

    QTimer timer;

    void updateBullet();
    void updateEnemy();
    int loadGLTextures();

    void drawRandomBlock( );
    void checkScore( );
    int checkCollision( );
    int randomMinMax(int min, int max = 0);

private:
    void initializeGL( ) override;
    void paintGL( ) override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateTimer();
};
#endif // WIDGET_H
