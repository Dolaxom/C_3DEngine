#ifndef SRC_S21_CAMERA_H_
#define SRC_S21_CAMERA_H_

#include "s21_engine.h"
#include "s21_mesh.h"
#include "math/s21_engine_math.h"

void fleeglut_init(int argc, char **argv);
void display();
void display_init();
void rendering_mesh(mesh_t mesh);

#endif  // SRC_S21_CAMERA_H_