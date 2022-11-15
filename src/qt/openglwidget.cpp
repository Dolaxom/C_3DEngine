#include "openglwidget.h"

int projection = 0;
QString meshstr = NULL;
QString bgcolorstr = NULL;
QString vertcolorstr = NULL;
QString edgecolorstr = NULL;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

void OpenGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    qDebug() << "init";

    //paintGL();
}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;
    if (w == 0) w = 1;

    GLfloat range = 2.0;
    GLdouble aspect_w = (GLfloat)w / (GLfloat)h;
    GLdouble aspect_h = (GLfloat)h / (GLfloat)w;

    resize(w, h);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // qDebug() << w << "&" << h << " | " << aspect_w << aspect_h;

    if (w >= h) {
        glOrtho(-range * aspect_w, range * aspect_w, -range, range, -range * 2, range * 2);
    } else if (h > w) {
        glOrtho(-range, range, -range * aspect_h, range * aspect_h, -range * 2, range * 2);
    }

//    if (projection == 0) {
//        glFrustum(-10, 10, -10, 10, -10, 10);       // last two: 1 is camera to front, 2 is camera to back (space)
//        // glTranslatef(0, 0, 8);

////        const GLdouble zNear = -30.0, zFar = 30.0, fov = 30.0;
////        this->perspective(fov, aspect, zNear, zFar);
//    } else {
//        glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
//    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void OpenGLWidget::setValues(QString mesh, int projection_index, QString bg_color) {
    projection = projection_index;
    meshstr = mesh;
    bgcolorstr = bg_color;

    qDebug() << projection << meshstr << bgcolorstr;
}

//void OpenGLWidget::setProjection(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {

//}
