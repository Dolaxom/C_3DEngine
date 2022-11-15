#include "openglwidget.h"
#include "../engine/math/s21_engine_math.h"

mesh_t mesh;
float deg = 0.0f;
GLdouble fov = 90.0;
GLdouble aspect_w = 0.0;
GLdouble aspect_h = 0.0;
GLdouble range = 2.0;
GLdouble near_dist = 0.5;
GLdouble far_dist = 500.0;
int projection = 0;
QString meshstr = NULL;
QString bgcolorstr = NULL;
QString vertcolorstr = NULL;
QString edgecolorstr = NULL;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

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

    // qDebug() << projection << w << "&" << h << " | " << aspect_w << aspect_h << " | resizeGL";

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    updateProjection();

    displayMesh();

    //glRotatef(90, 0, 0, 1);

//    glBegin(GL_TRIANGLES);
//    glColor3f(1, 1, 1);

//    glVertex3d(0, 0, -1.0f);
//    glVertex3d(1, 0, -1.0f);
//    glVertex3d(0, 1, -1.0f);

    glEnd();
}

void OpenGLWidget::updateValues(QString newmesh, int projection_index, QString bg_color) {
    projection = projection_index;
    meshstr = newmesh;
    bgcolorstr = bg_color;

    initMesh();
    update();

    qDebug() << projection << meshstr << bgcolorstr;
}

void OpenGLWidget::updateProjection() {
    if (projection == 0) {
        if (this->width() >= this->height()) {
            glFrustum(-range * aspect_w, range * aspect_w, -range, range, -near_dist, far_dist);
        } else {
            glFrustum(-range, range, -range * aspect_h, range * aspect_h, -near_dist, far_dist);
        }

//        const GLdouble pi = 3.1415926535897932384626433832795;
//        GLdouble fw, fh;

//        fh = tan( fov / 360 * pi ) * near_dist;
//        fw = fh * aspect_w;

//        glFrustum(-fw * aspect_w, fw * aspect_w, -fh * aspect_h, fh * aspect_h, -near_dist, far_dist);
    } else {
        if (this->width() >= this->height()) {
            glOrtho(-range * aspect_w, range * aspect_w, -range, range, near_dist, far_dist);
        } else {
            glOrtho(-range, range, -range * aspect_h, range * aspect_h, near_dist, far_dist);
        }
    }
}

void OpenGLWidget::initMesh() {
  // concat meshstr and pathstr & turn it to char*
  QString qpath = "../../materials/raw/monkey.obj";
  char *path_to_file = (char *)malloc(sizeof(char) * 255);

  if (path_to_file) {
      strncpy(path_to_file, qpath.toStdString().c_str(), 255);
      mesh = parse_obj_file(path_to_file);
      s21_scale(&mesh, 1.0f, 1.0f, 1.0f);
      s21_rotate_x(&mesh, 0.0f);
      s21_rotate_y(&mesh, 0.0f);
      s21_rotate_z(&mesh, 0.0f);
      free(path_to_file);
  }
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
  copy_polygons(mesh);
  //glTranslatef(0.0f, 0.0f, -150.5f);
  s21_rotate_x(&mesh, s21_degree_to_radian(0));
  s21_rotate_y(&mesh, s21_degree_to_radian(deg));
  s21_rotate_z(&mesh, s21_degree_to_radian(0));
  s21_scale(&mesh, 1, 1, 1);
  renderMesh();
  // glutSwapBuffers();
  // printf("DEBUG: Input degrees to y rotation:"); // TODO remove it later
  // scanf("%f", &deg);
}
