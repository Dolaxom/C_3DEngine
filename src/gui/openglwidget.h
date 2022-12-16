#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtEvents>

#include "../../libs/QtGifImage-master/src/gifimage/qgifimage.h"
#include "../engine/math/s21_engine_math.h"

#define GL_SILENCE_DEPRECATION

class OpenGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  OpenGLWidget(QWidget *parent = nullptr);
  void clearMesh();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void setMeshpath(QString new_meshpath);
  void setProjection(int new_projection);
  void setPosition(float new_x, float new_y, float new_z);
  void setRotation(float new_x, float new_y, float new_z, bool new_auto);
  void setScale(float new_x, float new_y, float new_z);
  void setColors(QColor new_bgcolor, QColor new_vertcolor,
                 QColor new_edgecolor);
  void setSizes(double new_vertsize, double new_edgesize);
  void setStyles(int new_vertstyle, int new_edgestyle);
  int getErrcode();
  int getPolygonsCount();
  int getPointsCount();
  void screen(QString filename, QString fileext);
  void recordStart();
  void recordFinish(QString filename, QString fileext);

 signals:
  void autorotValueChanged(bool newstate);
  void posValueChanged(float newpos_x, float newpos_y, float newpos_z);
  void rotValueChanged(float newrot_x, float newrot_y, float newrot_z);
  void scaleValueChanged(float newscale_x, float newscale_y, float newscale_z);

 private slots:
  void record();
  void autoRotateLaunch();
  void autoRotate();
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  void processMouseMovement(QMouseEvent *event);
  void processMouseRotation(QMouseEvent *event);
  QVector2D getMouseDirection(QMouseEvent *event);
  void updateProjection();
  void initMesh(char *path_to_mesh);
  int setupMesh();
  void setupRender();
  void renderMesh();
  void renderModeDefault();
  void renderModeFast();
  void displayMesh();
  void s21_location(float x, float y, float z);

  int errcode = 0;
  mesh_t mesh;
  QString current_meshpath = NULL;
  GLdouble aspect_w = 0.0;
  GLdouble aspect_h = 0.0;
  const GLdouble range = 1.0;
  const GLdouble near_dist = 0.5;
  const GLdouble far_dist = 500.0;

  QGifImage *gif = NULL;
  QTimer *gif_timer = NULL;
  const int gif_interval = 1000 / 10;

  bool auto_rotation = false;
  QTimer *auto_timer = NULL;
  const int auto_interval = 50;

  bool is_lbutton_down = false;
  bool is_rbutton_down = false;
  int prev_mousepos_x = 0;
  int prev_mousepos_y = 0;
  const float speed = 0.05f;

  int projection = 0;
  float pos_x = 0;
  float pos_y = 0;
  float pos_z = 0;
  float rot_x = 0;
  float rot_y = 0;
  float rot_z = 0;
  float scale_x = 0;
  float scale_y = 0;
  float scale_z = 0;
  QColor color_bg;
  QColor color_vert;
  QColor color_edge;
  GLfloat vertsize = 0.0f;
  GLfloat edgesize = 5.00f;
  int vertstyle = 0;
  int edgestyle = 0;
};

#endif  // OPENGLWIDGET_H
