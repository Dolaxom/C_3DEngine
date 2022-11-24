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
  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);
  void setScale(float x, float y, float z);
  void setProjection(int new_projection);
  void setMeshpath(QString new_meshpath);
  void setColors(QString new_bgcolor, QString new_vertcolor, QString new_edgecolor);
  void setSizes(double new_vertsize, double new_edgesize);
  void setStyles(QString new_vertstyle, QString new_edgestyle);
  void setErrcode(int new_code);
  int getErrcode();
  int getPolygonsCount();
  int getPointsCount();

 private:
  void updateProjection();
  void initMesh(char *path_to_mesh);
  void renderMesh();
  void displayMesh();

  GLdouble range = 1.0;
  GLdouble near_dist = 0.5;
  GLdouble far_dist = 500.0;
};

#endif  // OPENGLWIDGET_H
