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
  void setProjection(int new_projection);
  void setMeshpath(QString new_meshpath);
  void setColors(QString new_bgcolor, QString new_vertcolor, QString new_edgecolor);
  void setSizes(double new_vertsize, double new_edgesize);
  void setStyles(QString new_vertstyle, QString new_edgestyle);
  void setErrcode(int new_code);
  int getErrcode();

 private:
  void updateProjection();
  void initMesh(char *path_to_mesh);
  void renderMesh();
  void displayMesh();
};

#endif  // OPENGLWIDGET_H
