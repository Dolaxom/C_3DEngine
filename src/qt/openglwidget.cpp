#include "openglwidget.h"

bool perspective = true;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

void OpenGLWidget::setValues(bool projection) {
    perspective = projection;
}

void OpenGLWidget::initializeGL() {
    // initializeGL();

    QWidget *parent = static_cast<QWidget *>(this->parent());
    if (parent) {
        resizeGL(parent->width(), parent->height());
    }

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    qDebug() << "init";

    paintGL();
}

void OpenGLWidget::resizeGL(int w, int h) {
    this->resize(w, h);
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
    //QColor *color = new QColor();
    // color->setNamedColor(Qt::red);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);  // | GL_DEPTH_BUFFER_BIT

    // glRotatef(90, 0, 0, 1);

    if (perspective) {
        glFrustum(-1, 1, -1, 1, 2, 12);       // last two: 1 is camera to front, 2 is camera to back (space)
        //glTranslatef(0, 0, 8);
    } else {
        glOrtho(-1, 1, -1, 1, -1000.0f, 1000.0f);
    }

    glBegin(GL_TRIANGLES);

    glColor3f(1, 1, 1);

    glVertex3d(0, 0, -1.5f);
    glVertex3d(1, 0, -1.5f);
    glVertex3d(0, 1, -1.5f);
    glEnd();
}
