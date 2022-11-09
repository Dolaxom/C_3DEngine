#ifndef SRC_S21_CAMERA_H_
#define SRC_S21_CAMERA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "math/s21_engine_math.h"

void fleeglut_init(int argc, char **argv);
void display();
void display_init();
void camera_init();
void rendering_mesh(mesh_t mesh);
void mesh_init(char *path_to_file);
void s21_location(float x, float y, float z);
int display_change(); 

mesh_t render_mesh;

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_CAMERA_H_