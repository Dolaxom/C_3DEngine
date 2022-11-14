#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) {       // : QOpenGLWidget(parent)

}

void OpenGLWidget::initializeGL() {
    // initializeGL();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    qDebug() << "init";
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);     // get w h from qgraphicsview widget
}

void OpenGLWidget::paintGL() {
    //QColor *color = new QColor();
    // color->setNamedColor(Qt::red);

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);  // | GL_DEPTH_BUFFER_BIT

    QWidget *parent = static_cast<QWidget *>(this->parent());

    if (parent) {
        resizeGL(parent->width(), parent->height());
        qDebug() << "has parent" << "|" << parent->width() << parent->height();
    } else {
        //qDebug() << "null parent";
    }

}
