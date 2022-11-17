#include "openglwidget.h"

int errcode = 0;
mesh_t mesh;
GLdouble fov = 90.0;
GLdouble aspect_w = 0.0;
GLdouble aspect_h = 0.0;
GLdouble range = 2.0;
GLdouble near_dist = 0.5;
GLdouble far_dist = 500.0;
int projection = 0;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  qDebug() << "init";
}

void OpenGLWidget::resizeGL(int w, int h) {
  if (h == 0) h = 1;
  if (w == 0) w = 1;

  aspect_w = (GLfloat)w / (GLfloat)h;
  aspect_h = (GLfloat)h / (GLfloat)w;

  resize(w, h);
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // qDebug() << projection << w << "&" << h << " | " << aspect_w << aspect_h <<
  // " | resizeGL";

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void OpenGLWidget::paintGL() {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  updateProjection();

  displayMesh();
}

void OpenGLWidget::updateProjection() {
  if (projection == 0) {
    if (this->width() >= this->height()) {
      glFrustum(-range * aspect_w, range * aspect_w, -range, range, -near_dist,
                far_dist);
    } else {
      glFrustum(-range, range, -range * aspect_h, range * aspect_h, -near_dist,
                far_dist);
    }

    //        const GLdouble pi = 3.1415926535897932384626433832795;
    //        GLdouble fw, fh;

    //        fh = tan( fov / 360 * pi ) * near_dist;
    //        fw = fh * aspect_w;

    //        glFrustum(-fw * aspect_w, fw * aspect_w, -fh * aspect_h, fh *
    //        aspect_h, -near_dist, far_dist);
  } else {
    if (this->width() >= this->height()) {
      glOrtho(-range * aspect_w, range * aspect_w, -range, range, near_dist,
              far_dist);
    } else {
      glOrtho(-range, range, -range * aspect_h, range * aspect_h, near_dist,
              far_dist);
    }
  }
}

void OpenGLWidget::initMesh(char *path_to_mesh) {
    int errcode = 0;
    mesh = parse_obj_file(path_to_mesh, &errcode);

    // glTranslatef(0.0f, 0.0f, -150.5f);
    s21_scale(&mesh, 1.0f, 1.0f, 1.0f);
    s21_rotate_x(&mesh, 0.0f);
    s21_rotate_y(&mesh, 0.0f);
    s21_rotate_z(&mesh, 0.0f);

    //qDebug() << errcode;
}

void OpenGLWidget::renderMesh() {
  for (int polygon = 0; polygon < mesh.count_of_polygons; polygon++) {
    glLineWidth(0.01);
    glBegin(GL_POLYGON);
    for (int point = 0; point < mesh.polygons[polygon].count_of_points;
         point++) {
      glColor3f(1, 1, 1);
      glVertex3f(mesh.polygons_copy[polygon].points[point].x,
                 mesh.polygons_copy[polygon].points[point].y,
                 mesh.polygons_copy[polygon].points[point].z);
    }
    glEnd();
  }
}

void OpenGLWidget::displayMesh() {
  if (errcode == 0) {
      copy_polygons(mesh);

        //  if (projection == 1) {
        //    glTranslatef(0.0f, 0.0f, -150.5f);
        //  }

      s21_rotate_x(&mesh, s21_degree_to_radian(0));
      s21_rotate_y(&mesh, s21_degree_to_radian(0));
      s21_rotate_z(&mesh, s21_degree_to_radian(0));
      s21_scale(&mesh, 1, 1, 1);

      renderMesh();
  }
}

void OpenGLWidget::setProjection(int new_projection) {
    projection = new_projection;
}

void OpenGLWidget::setMeshpath(QString new_meshpath) {
    qDebug() << new_meshpath;
    char *meshpath = (char*)malloc(sizeof(char) * (new_meshpath.length() + 1));

    if (meshpath) {
        strncpy(meshpath, new_meshpath.toStdString().c_str(), (new_meshpath.length() + 1));
        initMesh(meshpath);
        update();
        free(meshpath);
    } else {
        errcode = -100;
    }

    qDebug() << errcode;
}

void OpenGLWidget::setColors(QString new_bgcolor, QString new_vertcolor, QString new_edgecolor) {

}

void OpenGLWidget::setSizes(double new_vertsize, double new_edgesize) {

}

void OpenGLWidget::setStyles(QString new_vertstyle, QString new_edgestyle) {

}

void OpenGLWidget::setErrcode(int new_code) {
    errcode = new_code;
}

int OpenGLWidget::getErrcode() {
    return errcode;
}
