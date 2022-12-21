#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    GLfloat xAngle, yAngle, zAngle;
    // 3D pyramid
    //GLboolean bDepthTest;
    //GLboolean bCullFace;

    // polygon Mode
    GLenum polygonMode;
    GLenum shadeMode;

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // WIDGET_H
