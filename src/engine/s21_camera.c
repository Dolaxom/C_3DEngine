#include "s21_camera.h"

int main(int argc, char **argv) {
  init_mesh("../materials/raw/monkey.obj");
  init_fleeglut(argc, argv);
  glutMainLoop();
  // TODO: free()
  return S21_OK;
}

float deg = 1.0f;
void display() {
  init_display();
  init_camera();
  setup_mesh();
  render_mesh(main_mesh);

  glutSwapBuffers();
  printf("DEBUG: Input degrees to y rotation:"); // TODO remove it later
  scanf("%f", &deg);
}

static void init_fleeglut(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("3DViewer");
  glutDisplayFunc(display);
}

static void init_display() {
  glutPostRedisplay();
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void init_camera() {
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

static void render_mesh() {
  setup_render();

  main_mesh.legacy_render ? render() : fast_render();
}

static void init_mesh(char *path_to_file) {
  int error = 0;
  main_mesh = parse_obj_file(path_to_file, &error);
}

void s21_location(float x, float y, float z) {
  glTranslatef(x, y, z);
}

static void setup_mesh() {
  if (main_mesh.legacy_render) {
    copy_polygons(main_mesh);
    s21_location(0.0f, 0.0f, -3.5f);
    s21_rotate_x(&main_mesh, s21_degree_to_radian(0));
    s21_rotate_y(&main_mesh, s21_degree_to_radian(deg));
    s21_rotate_z(&main_mesh, s21_degree_to_radian(0));
    s21_scale(&main_mesh, 1, 1, 1);
  } else {
    copy_points(main_mesh);
    s21_location(0.0f, 0.0f, -3.5f);
    s21_fast_rotate_x(&main_mesh, s21_degree_to_radian(0));
    s21_fast_rotate_y(&main_mesh, s21_degree_to_radian(deg));
    s21_fast_rotate_z(&main_mesh, s21_degree_to_radian(0));
    s21_fast_scale(&main_mesh, 1, 1, 1);
  }
}

static void render() {
  for (int polygon = 0; polygon < main_mesh.count_of_polygons; polygon++) {
    glVertexPointer(4, GL_FLOAT, 0, main_mesh.polygons_copy[polygon].points);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POLYGON, 0, main_mesh.polygons_copy[polygon].count_of_points);
    if (0) { // set points (2)
      glDrawArrays(GL_POINTS, 0, main_mesh.polygons_copy[polygon].count_of_points);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

static void fast_render() {
  glVertexPointer(4, GL_FLOAT, 0, main_mesh.v_points_copy);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_TRIANGLES, main_mesh.size_of_queue, GL_UNSIGNED_INT, main_mesh.queue);
  if (0) { // set points (3)
    glDrawElements(GL_POINTS, main_mesh.size_of_queue, GL_UNSIGNED_INT, main_mesh.queue);    
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

static void setup_render() {
  glLineWidth(0.01); // set line width
  glColor3f(1, 1, 1); // set color of lines

  if (0) { // set dotter-line
    glLineStipple(1, 0x00F0);
    glEnable(GL_LINE_STIPPLE);
  }

  if (0) { // set points (1)
    glPointSize(5); // set size of points
  }
}