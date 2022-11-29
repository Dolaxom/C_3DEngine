#include "openglwidget.h"

#include <QtEvents>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    this->setMouseTracking(true);
}

// PUBLIC

void OpenGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
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
  glClearColor(rgb_bg[0], rgb_bg[1], rgb_bg[2], 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  updateProjection();
  renderMesh();
}

void OpenGLWidget::setMeshpath(QString new_meshpath) {
    if (new_meshpath != current_meshpath) {
        char *meshpath = (char*)malloc(sizeof(char) * (new_meshpath.length() + 1));

        if (meshpath) {
            current_meshpath = new_meshpath;
            strncpy(meshpath, new_meshpath.toStdString().c_str(), (new_meshpath.length() + 1));
            initMesh(meshpath);
            update();
            free(meshpath);
        } else {
            errcode = -100;
        }
    }
}

void OpenGLWidget::setProjection(int new_projection) {
    projection = new_projection;
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

void OpenGLWidget::setColors(float *bgcolor, float *vertcolor, float *edgecolor) {
    updateColor(rgb_bg, bgcolor);
    updateColor(rgb_vert, vertcolor);
    updateColor(rgb_edge, edgecolor);
}

void OpenGLWidget::setSizes(double new_vertsize, double new_edgesize) {
    vertsize = new_vertsize;
    edgesize = new_edgesize;
}

void OpenGLWidget::setStyles(int vertstyle_index, int edgestyle_index) {
    vertstyle = vertstyle_index;
    edgestyle = edgestyle_index;
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

void OpenGLWidget::screen(QString filename, QString fileext) {
    this->grabFramebuffer().save(filename, fileext.toStdString().c_str());
}

void OpenGLWidget::recordStart() {
    gif = new QGifImage();
    gif_timer = new QTimer(this);

    gif->setDefaultDelay(gif_interval);

    connect(gif_timer, SIGNAL(timeout()), this, SLOT(record()));
    gif_timer->start(gif_interval);
}

void OpenGLWidget::recordFinish(QString filename, QString fileext) {
    gif_timer->stop();
    disconnect(gif_timer, SIGNAL(timeout()), this, SLOT(record()));
    qDebug() << "disconnect";

    if (!filename.isNull()) {
        gif->save(filename + fileext);
    }

    delete gif;
    delete gif_timer;
}

// PRIVATE SLOTS

void OpenGLWidget::record() {
    QPixmap frame(this->size());
    this->render(&frame);

    QImage img = frame.toImage();
    gif->addFrame(img, gif_interval);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // restrict to openglwindow
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        pos_z -= 0.05f;
    } else if (event->angleDelta().y() < 0) {
        pos_z += 0.05f;
    }
    emit posValueChanged(pos_x, pos_y, pos_z);
    update();
}

// PRIVATE

void OpenGLWidget::updateColor(float *color, float *sourcecolor) {
    if (color && sourcecolor) {
        for (int i = 0; i < 3; i++) {
            color[i] = sourcecolor[i];
        }
    }
}

void OpenGLWidget::updateProjection() {
  if (projection == 0) {    // perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float left_value = -((float)this->width() / 1000) / 2;
    float right_value = ((float)this->width() / 1000) / 2;
    float top_value = -((float)this->height() / 1000) / 2;
    float down_value = ((float)this->height() / 1000) / 2;
    glFrustum(left_value, right_value, top_value, down_value, near_dist, far_dist);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  } else {                  // orthogonal
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
    mesh_t old_mesh = mesh;
    mesh = parse_obj_file(path_to_mesh, &errcode);

    if (errcode == 0) {
        s21_location(0.0f, 0.0f, 0.0f);
        s21_scale(&mesh, 1.0f, 1.0f, 1.0f);
        s21_rotate_x(&mesh, 0.0f);
        s21_rotate_y(&mesh, 0.0f);
        s21_rotate_z(&mesh, 0.0f);
    } else {
        mesh = old_mesh;
    }
}

void OpenGLWidget::setupMesh() {
  if (mesh.legacy_render) {
    copy_polygons(mesh);
    s21_location(pos_x, pos_y, pos_z);
    s21_rotate_x(&mesh, s21_degree_to_radian(rot_x));
    s21_rotate_y(&mesh, s21_degree_to_radian(rot_y));
    s21_rotate_z(&mesh, s21_degree_to_radian(rot_z));
    s21_scale(&mesh, scale_x, scale_y, scale_z);
  } else {
    copy_points(mesh);
    s21_location(pos_x, pos_y, pos_z);
    s21_fast_rotate_x(&mesh, s21_degree_to_radian(rot_x));
    s21_fast_rotate_y(&mesh, s21_degree_to_radian(rot_y));
    s21_fast_rotate_z(&mesh, s21_degree_to_radian(rot_z));
    s21_fast_scale(&mesh, scale_x, scale_y, scale_z);
  }
}

void OpenGLWidget::setupRender() {
  glLineWidth(edgesize);
  glColor3f(rgb_edge[0], rgb_edge[1], rgb_edge[2]);

  if (edgestyle != 0) {
    glLineStipple(1, 0x00F0);
    glEnable(GL_LINE_STIPPLE);
  } else {

  }

  if (vertstyle != 0) {
    glPointSize(vertsize);
  }
}

void OpenGLWidget::renderMesh() {
      setupMesh();
      setupRender();
      mesh.legacy_render ? renderModeDefault() : renderModeFast();
}

void OpenGLWidget::renderModeDefault() {
  for (int polygon = 0; polygon < mesh.count_of_polygons; polygon++) {
    glVertexPointer(4, GL_FLOAT, 0, mesh.polygons_copy[polygon].points);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POLYGON, 0, mesh.polygons_copy[polygon].count_of_points);

    if (vertstyle == 1) {           // circle
      // should draw circle points
      glDrawArrays(GL_POINTS, 0, mesh.polygons_copy[polygon].count_of_points);
    } else if (vertstyle == 2) {    // square
      glDrawArrays(GL_POINTS, 0, mesh.polygons_copy[polygon].count_of_points);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OpenGLWidget::renderModeFast() {
  glVertexPointer(4, GL_FLOAT, 0, mesh.v_points_copy);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_TRIANGLES, mesh.size_of_queue, GL_UNSIGNED_INT, mesh.queue);

  if (vertstyle == 1) {             // circle
    // should draw circle points
    glDrawElements(GL_POINTS, mesh.size_of_queue, GL_UNSIGNED_INT, mesh.queue);
  } else if (vertstyle == 2) {      // square
    glDrawElements(GL_POINTS, mesh.size_of_queue, GL_UNSIGNED_INT, mesh.queue);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLWidget::s21_location(float x, float y, float z) {
  glTranslatef(x, y, z);
}
