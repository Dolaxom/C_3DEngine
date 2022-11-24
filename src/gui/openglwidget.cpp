#include "openglwidget.h"
#include "GL/glu.h"

int errcode = 0;
mesh_t mesh;
int projection = 0;
GLdouble aspect_w = 0.0;
GLdouble aspect_h = 0.0;
float pos_x = 0;
float pos_y = 0;
float pos_z = 0;
float rot_x = 0;
float rot_y = 0;
float rot_z = 0;
float scale_x = 0;
float scale_y = 0;
float scale_z = 0;


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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float left_value = -((float)this->width() / 1000) / 2; //-0.369
    float right_value = ((float)this->width() / 1000) / 2;
    float top_value = -((float)this->height() / 1000) / 2; // -393500
    float down_value = ((float)this->height() / 1000) / 2;
    glFrustum(left_value, right_value, top_value, down_value, near_dist, far_dist);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

     glTranslatef(0.0f, 0.0f, -5.0f); // TODO REMOVE LATER
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (this->width() >= this->height()) {
      glOrtho(-range * aspect_w, range * aspect_w, -range, range, near_dist,
              far_dist);
    } else {
      glOrtho(-range, range, -range * aspect_h, range * aspect_h, near_dist,
              far_dist);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}

void OpenGLWidget::initMesh(char *path_to_mesh) {
    errcode = 0;
    mesh = parse_obj_file(path_to_mesh, &errcode);

    // glTranslatef(0.0f, 0.0f, -150.5f);
    s21_scale(&mesh, 1.0f, 1.0f, 1.0f);
    s21_rotate_x(&mesh, 0.0f);
    s21_rotate_y(&mesh, 0.0f);
    s21_rotate_z(&mesh, 0.0f);

    qDebug() << "initmesh errcode = " << errcode;
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

      glTranslatef(pos_x, pos_y, pos_z);

      s21_rotate_x(&mesh, s21_degree_to_radian(rot_x));
      s21_rotate_y(&mesh, s21_degree_to_radian(rot_y));
      s21_rotate_z(&mesh, s21_degree_to_radian(rot_z));
      s21_scale(&mesh, scale_x, scale_y, scale_z);

      renderMesh();
  }
}

void OpenGLWidget::setProjection(int new_projection) {
    projection = new_projection;
}

void OpenGLWidget::setMeshpath(QString new_meshpath) {
    char *meshpath = (char*)malloc(sizeof(char) * (new_meshpath.length() + 1));

    if (meshpath) {
        strncpy(meshpath, new_meshpath.toStdString().c_str(), (new_meshpath.length() + 1));
        initMesh(meshpath);
        update();
        free(meshpath);
    } else {
        errcode = -100;
    }

    qDebug() << new_meshpath;
    qDebug() << "setmeshpath errcode = " << errcode;
}

void OpenGLWidget::setPosition(float x, float y, float z) {
    pos_x = x;
    pos_y = y;
    pos_z = z;
}

void OpenGLWidget::setRotation(float x, float y, float z) {
    rot_x = x;
    rot_y = y;
    rot_z = z;
}

void OpenGLWidget::setScale(float x, float y, float z) {
    scale_x = x;
    scale_y = y;
    scale_z = z;
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

int OpenGLWidget::getPolygonsCount() {
    return mesh.count_of_polygons;
}

int OpenGLWidget::getPointsCount() {
    return mesh.count_of_points;
}
