#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLShaderProgram>

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget(QWidget *parent = nullptr);
    void setValues(QString mesh, int projection_index, QString bg_color);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // OPENGLWIDGET_H
