#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLShaderProgram>

#include <QTimer>
#include "../../libs/QtGifImage-master/src/gifimage/qgifimage.h"
#include "../engine/math/s21_engine_math.h"

class OpenGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  OpenGLWidget(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void setMeshpath(QString new_meshpath);
  void setProjection(int projection_index);
  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);
  void setScale(float x, float y, float z);
  void setColors(float *bgcolor, float *vertcolor, float *edgecolor);
  void setSizes(double new_vertsize, double new_edgesize);
  void setStyles(int vertstyle_index, int edgestyle_index);
  int getErrcode();
  int getPolygonsCount();
  int getPointsCount();
  void screen(QString filename, QString fileext);
  void recordStart();
  void recordFinish(QString filename, QString fileext);

signals:
  void poszValueChanged(float value);
  //void posValueChanged(float newpos_x, float newpos_y, float newpos_z);
  //void rotValueChanged(float newrot_x, float newrot_y, float newrot_z);
  //void scaleValueChanged(float newscale_x, float newscale_y, float newscale_z);

private slots:
  void record();
  void mousePressEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  void updateColor(float *color, float *sourcecolor);
  void updateProjection();
  void initMesh(char *path_to_mesh);
  void setupMesh();
  void setupRender();
  void renderMesh();
  void renderModeDefault();
  void renderModeFast();
  void displayMesh();
  void s21_location(float x, float y, float z);

  int errcode = 0;
  bool is_dirty = false;
  mesh_t mesh;
  QString current_meshpath = NULL;
  GLdouble aspect_w = 0.0;
  GLdouble aspect_h = 0.0;
  const GLdouble range = 1.0;
  const GLdouble near_dist = 0.5;
  const GLdouble far_dist = 500.0;

  QGifImage *gif = NULL;
  QTimer *gif_timer = NULL;
  const int gif_interval = 1000/10;

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
  GLclampf rgb_bg[3] = {0, 0, 0};
  GLclampf rgb_vert[3] = {1, 1, 1};
  GLclampf rgb_edge[3] = {1, 1, 1};
  GLfloat vertsize = 0.0f;
  GLfloat edgesize = 5.00f;
  int vertstyle = 0;
  int edgestyle = 0;
};

#endif  // OPENGLWIDGET_H
