#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    color_bg = QColor(0, 0, 0);
    color_vert = QColor(1, 1, 1);
    color_edge = QColor(1, 1, 1);

    connect(this, SIGNAL(autorotValueChanged(bool)), this, SLOT(autoRotateLaunch()));
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
  glClearColor(color_bg.redF(), color_bg.greenF(), color_bg.blueF(), 1);
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

void OpenGLWidget::setPosition(float new_x, float new_y, float new_z) {
    pos_x = new_x;
    pos_y = new_y;
    pos_z = new_z;
}

void OpenGLWidget::setRotation(float new_x, float new_y, float new_z, bool new_auto) {
    rot_x = new_x;
    rot_y = new_y;
    rot_z = new_z;

    if (auto_rotation != new_auto) {
        auto_rotation = new_auto;
        emit autorotValueChanged(auto_rotation);
    }
}

void OpenGLWidget::setScale(float new_x, float new_y, float new_z) {
    scale_x = new_x;
    scale_y = new_y;
    scale_z = new_z;
}

void OpenGLWidget::setColors(QColor new_bgcolor, QColor new_vertcolor, QColor new_edgecolor) {
    color_bg = new_bgcolor;
    color_vert = new_vertcolor;
    color_edge = new_edgecolor;
}

void OpenGLWidget::setSizes(double new_vertsize, double new_edgesize) {
    vertsize = new_vertsize;
    edgesize = new_edgesize;
}

void OpenGLWidget::setStyles(int new_vertstyle, int new_edgestyle) {
    vertstyle = new_vertstyle;
    edgestyle = new_edgestyle;
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

void OpenGLWidget::autoRotateLaunch() {
    if (auto_rotation) {
        auto_timer = new QTimer(this);
        connect(auto_timer, SIGNAL(timeout()), this, SLOT(autoRotate()));
        auto_timer->start(auto_interval);
    } else {
        if (auto_timer) {
            auto_timer->stop();
            disconnect(auto_timer, SIGNAL(timeout()), this, SLOT(autoRotate()));
            delete auto_timer;
        }
    }
}

void OpenGLWidget::autoRotate() {
    rot_y += speed * 4;
    emit rotValueChanged(rot_x, rot_y, rot_z);
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->pos().x() < this->width() && event->pos().x() > this->pos().x() &&
        event->pos().y() < this->height() && event->pos().y() > this->pos().y()) {
        Qt::MouseButton mbutton = event->button();

        if (mbutton == Qt::LeftButton) {            // position
            is_lbutton_down = true;
        } else if (mbutton == Qt::RightButton) {    // rotation
            is_rbutton_down = true;
        }

        prev_mousepos_x = event->pos().x();
        prev_mousepos_y = event->pos().y();
        this->setMouseTracking(true);
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (is_lbutton_down) {
        processMouseMovement(event);
        emit posValueChanged(pos_x, pos_y, pos_z);
        update();
    } else if (is_rbutton_down) {
        processMouseRotation(event);
        emit rotValueChanged(rot_x, rot_y, rot_z);
        update();
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (is_lbutton_down) {
        is_lbutton_down = false;
    } else if (is_rbutton_down) {
        is_rbutton_down = false;
    }
    this->setMouseTracking(false);
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        pos_z -= speed;
    } else if (event->angleDelta().y() < 0) {
        pos_z += speed;
    }
    emit posValueChanged(pos_x, pos_y, pos_z);
    update();
}

// PRIVATE

void OpenGLWidget::processMouseMovement(QMouseEvent *event) {
    QVector2D dir = getMouseDirection(event);
    float pos_speed = speed / 2;

    if ((int)dir.x() > 0) {
        pos_x += pos_speed;
    } else if ((int)dir.x() < 0) {
        pos_x -= pos_speed;
    }

    if ((int)dir.y() > 0) {
        pos_y -= pos_speed;
    } else if ((int)dir.y() < 0) {
        pos_y += pos_speed;
    }
}

void OpenGLWidget::processMouseRotation(QMouseEvent *event) {
    QVector2D dir = getMouseDirection(event);
    float rot_speed = speed * 10;

    if ((int)dir.x() > 0) {
        rot_x += rot_speed;
    } else if ((int)dir.x() < 0) {
        rot_x -= rot_speed;
    }

    if ((int)dir.y() > 0) {
        rot_y -= rot_speed;
    } else if ((int)dir.y() < 0) {
        rot_y += rot_speed;
    }
}

QVector2D OpenGLWidget::getMouseDirection(QMouseEvent *event) {
    QVector2D result;
    result.setX(event->pos().x() - prev_mousepos_x);
    result.setY(event->pos().y() - prev_mousepos_y);
    prev_mousepos_x = event->pos().x();
    prev_mousepos_y = event->pos().y();
    return result;
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
  glColor3f(color_edge.redF(), color_edge.greenF(), color_edge.blueF());

  if (edgestyle != 0) {
    glLineStipple(1, 0x00F0);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
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
    glColor3f(color_vert.redF(), color_vert.greenF(), color_vert.blueF());
    if (vertstyle == 1) {           // circle
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDrawArrays(GL_POINTS, 0, mesh.polygons_copy[polygon].count_of_points);
    } else if (vertstyle == 2) {    // square
      glDrawArrays(GL_POINTS, 0, mesh.polygons_copy[polygon].count_of_points);
    }

    if (vertstyle == 1) {
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_BLEND);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OpenGLWidget::renderModeFast() {
  glVertexPointer(4, GL_FLOAT, 0, mesh.v_points_copy);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3f(color_vert.redF(), color_vert.greenF(), color_vert.blueF());
  if (vertstyle == 2) {
    glDrawArrays(GL_POINTS, 0, mesh.count_of_points);
  } else if (vertstyle == 1) {
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDrawArrays(GL_POINTS, 0, mesh.count_of_points);
      glDisable(GL_BLEND);
      glDisable(GL_POINT_SMOOTH);
  }
  glColor3f(color_edge.redF(), color_edge.greenF(), color_edge.blueF());
  glDrawElements(GL_TRIANGLES, mesh.size_of_queue, GL_UNSIGNED_INT, mesh.queue);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLWidget::s21_location(float x, float y, float z) {
  glTranslatef(x, y, z);
}
