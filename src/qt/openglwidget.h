#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // OPENGLWIDGET_H
