#ifndef SRC_S21_CAMERA_H_
#define SRC_S21_CAMERA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "math/s21_engine_math.h"

void display();
void s21_location(float x, float y, float z);
static void init_fleeglut(int argc, char **argv);
static void init_mesh(char *path_to_file);
static void init_display();
static void setup_render();
static void render_mesh();
static void init_camera();
static void fast_render();
static void setup_mesh();
static void render();

mesh_t main_mesh;

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_CAMERA_H_