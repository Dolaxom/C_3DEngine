#include "s21_camera.h"

int main(int argc, char **argv) {
  mesh_init("materials/raw/building.obj");
  fleeglut_init(argc, argv);
  glutMainLoop();

  return S21_OK;
}

void fleeglut_init(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("3DViewer");
  glutDisplayFunc(display);
}

float deg = 0.0f;
void display() {
  display_init();
  camera_init();

  copy_polygons(render_mesh);
  s21_location(0.0f, 0.0f, -150.5f);
  s21_rotate_x(&render_mesh, s21_degree_to_radian(0));
  s21_rotate_y(&render_mesh, s21_degree_to_radian(deg));
  s21_rotate_z(&render_mesh, s21_degree_to_radian(0));
  s21_scale(&render_mesh, 1, 1, 1);
  rendering_mesh(render_mesh);
  glutSwapBuffers();
  printf("DEBUG: Input degrees to y rotation:"); // TODO remove it later
  scanf("%f", &deg);
}

void display_init() {
  glutPostRedisplay();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void camera_init() {
  GLdouble fov = 90.0;
  GLdouble aspect = 1.0;
  GLdouble near_dist = 0.5;
  GLdouble far_dist = 500.0;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, aspect, near_dist, far_dist);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void rendering_mesh(mesh_t mesh) {
  for (int polygon = 0; polygon < mesh.count_of_polygons; polygon++) {
    glLineWidth(0.01);
    glBegin(GL_POLYGON);
    for (int point = 0; point < mesh.polygons[polygon].count_of_points;
         point++) {
      glColor3f(1, 1, 1);
      glVertex3f(mesh.polygons_copy[polygon].points[point].x,
                 mesh.polygons_copy[polygon].points[point].y,
                 mesh.polygons_copy[polygon].points[point].z);
    }
    glEnd();
  }
}

void mesh_init(char *path_to_file) {
  render_mesh = parse_obj_file(path_to_file);
  s21_scale(&render_mesh, 1.0f, 1.0f, 1.0f);
  s21_rotate_x(&render_mesh, 0.0f);
  s21_rotate_y(&render_mesh, 0.0f);
  s21_rotate_z(&render_mesh, 0.0f);
}

void s21_location(float x, float y, float z) {
  glTranslatef(x, y, z);
}