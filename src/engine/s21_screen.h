#ifndef SRC_ENGINE_S21_SCREEN_H
#define SRC_ENGINE_S21_SCREEN_H

#include <GL/freeglut.h>
#include "s21_engine.h"
#include "s21_mesh.h"
#include "math/s21_matrix_based.h"
#include "math/s21_engine_math.h"

void display();
void s21_render_tris(Mesh mesh);
void s21_setup_settings();
void s21_test_transform(Mesh mesh, float move);
float move = 0.0;

Mesh main_mesh;

#endif  // SRC_ENGINE_S21_SCREEN_H
