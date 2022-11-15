#include "openglwidget.h"

int projection = 0;
QString meshstr = NULL;
QString bgcolorstr = NULL;
QString vertcolorstr = NULL;
QString edgecolorstr = NULL;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

void OpenGLWidget::setValues(QString mesh, int projection_index, QString bg_color) {
    projection = projection_index;
    meshstr = mesh;
    bgcolorstr = bg_color;

    qDebug() << projection << meshstr << bgcolorstr;
}

void OpenGLWidget::initializeGL() {
//    QWidget *parent = static_cast<QWidget *>(this->parent());
//    if (parent) {
//        resizeGL(parent->width(), parent->height());
//    }

    glEnable(GL_DEPTH_TEST);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    qDebug() << "init";

    //paintGL();
}

void OpenGLWidget::resizeGL(int w, int h) {
    resize(w, h);
    glViewport(0, 0, w, h);

    //glOrtho(-1, 1, -1, 1, -1000.0f, 1000.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

    if (projection == 0) {
        glFrustum(-10, 10, -10, 10, -10, 10);       // last two: 1 is camera to front, 2 is camera to back (space)
        // glTranslatef(0, 0, 8);
    } else {
        glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glRotatef(180, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);

    glVertex3d(0, 0, -1.0f);
    glVertex3d(1, 0, -1.0f);
    glVertex3d(0, 1, -1.0f);
//    glVertex2d(0, 0);
//    glVertex2d(1, 0);
//    glVertex2d(0, 1);

    glEnd();
}
