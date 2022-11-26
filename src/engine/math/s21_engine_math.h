#ifndef SRC_MATH_S21_ENGINE_MATH_H_
#define SRC_MATH_S21_ENGINE_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "s21_matrix4x4.h"

float s21_degree_to_radian(float degree);
void s21_scale(mesh_t *mesh, float new_x, float new_y, float new_z);
void s21_fast_scale(mesh_t *mesh, float new_x, float new_y, float new_z);
void s21_rotate_y(mesh_t *mesh, float degree);
void s21_rotate_x(mesh_t *mesh, float degree);
void s21_rotate_z(mesh_t *mesh, float degree);

#ifdef __cplusplus
}
#endif

#endif  // SRC_MATH_S21_ENGINE_MATH_H_