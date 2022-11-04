#include "s21_camera.h"

void fleeglut_init(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("3DViewer");
  glutDisplayFunc(display);
}

void display() {
  display_init();
  mesh_t render_mesh = test_cube();
  s21_scale(&render_mesh, 0.5, 0.5, 0.5);
  rendering_mesh(render_mesh);

  glutSwapBuffers();
}

void display_init() {
  glutPostRedisplay();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void rendering_mesh(mesh_t mesh) {
  for (int polygon = 0; polygon < mesh.count_of_polygons; polygon++) {
    glLineWidth(0.01);
    glBegin(GL_TRIANGLES);
    for (int point = 0; point < 3; point++) {
        glColor3f(1, 1, 1);
        glVertex3f(mesh.polygons[polygon].points[point].x, mesh.polygons[polygon].points[point].y, mesh.polygons[polygon].points[point].z);
    }
    glEnd();
  }
}