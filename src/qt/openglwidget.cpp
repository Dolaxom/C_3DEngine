#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

void OpenGLWidget::initializeGL() {
    // initializeGL();

    glEnable(GL_DEPTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);     // get x y from qgraphicsview widget
}

void OpenGLWidget::paintGL() {
    //QColor *color = new QColor();
    // color->setNamedColor(Qt::red);

    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
