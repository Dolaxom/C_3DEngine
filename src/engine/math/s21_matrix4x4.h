#ifndef SRC_MATH_S21_MATRIX4X4_H_
#define SRC_MATH_S21_MATRIX4X4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../s21_mesh.h"

typedef struct matrix_struct {
  float matrix[4][4];
} matrix4x4;

void s21_mult_matrix_on_vector(matrix4x4 *A, vector *B, vector *res);
matrix4x4 s21_scale_matrix_reference(vector new_size_vector);
void s21_calculate_scale_matrix(vector new_size_vector, polygons_t polygon);
matrix4x4 s21_rotation_y_matrix_reference(float degree);
void s21_calculate_rotation_y_matrix(float degree, polygons_t polygon);
matrix4x4 s21_rotation_x_matrix_reference(float degree);
void s21_calculate_rotation_x_matrix(float degree, polygons_t polygon);
matrix4x4 s21_rotation_z_matrix_reference(float degree);
void s21_calculate_rotation_z_matrix(float degree, polygons_t polygon);

#ifdef __cplusplus
}
#endif

#endif  // SRC_MATH_S21_MATRIX4X4_H_