#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLShaderProgram>

#include "../engine/math/s21_engine_math.h"

class OpenGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  OpenGLWidget(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void screen(QString filename, QString fileext);
  void setMeshpath(QString new_meshpath);
  void setProjection(int projection_index);
  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);
  void setScale(float x, float y, float z);
  void setColors(float *bgcolor, float *vertcolor, float *edgecolor);
  void setSizes(double new_vertsize, double new_edgesize);
  void setStyles(int vertstyle_index, int edgestyle_index);
  //void setErrcode(int new_code);
  int getErrcode();
  int getPolygonsCount();
  int getPointsCount();

 private:
  void updateColor(float *color, float *sourcecolor);
  void updateProjection();
  void initMesh(char *path_to_mesh);
  void renderMesh();
  void displayMesh();

  GLdouble range = 1.0;
  GLdouble near_dist = 0.5;
  GLdouble far_dist = 500.0;
};

#endif  // OPENGLWIDGET_H
