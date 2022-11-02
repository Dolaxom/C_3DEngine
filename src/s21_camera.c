#include "s21_camera.h"

void fleeglut_init(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("3DViewer");
  glutDisplayFunc(display);
}

void display() {
  glutPostRedisplay();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glLineWidth(0.01);
  glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(0.0, 1, 0);
  glEnd();

  glutSwapBuffers();
}