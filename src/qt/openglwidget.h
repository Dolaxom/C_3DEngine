#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLShaderProgram>

#include "../engine/math/s21_engine_math.h"

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    //void updateValues(QString mesh, int projection_index, QString bg_color);
    void updateProjection();

private:
    void initMesh();
    void renderMesh();
    void displayMesh();
};

#endif // OPENGLWIDGET_H
