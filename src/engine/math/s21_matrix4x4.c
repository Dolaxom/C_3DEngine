#include "s21_matrix4x4.h"

void s21_mult_matrix_on_vector(matrix4x4 *A, vector *B, vector *res) {
  res->x = A->matrix[0][0] * B->x + A->matrix[0][1] * B->y +
           A->matrix[0][2] * B->z + A->matrix[0][3] * B->w;
  res->y = A->matrix[1][0] * B->x + A->matrix[1][1] * B->y +
           A->matrix[1][2] * B->z + A->matrix[1][3] * B->w;
  res->z = A->matrix[2][0] * B->x + A->matrix[2][1] * B->y +
           A->matrix[2][2] * B->z + A->matrix[2][3] * B->w;
  res->w = A->matrix[3][0] * B->x + A->matrix[3][1] * B->y +
           A->matrix[3][2] * B->z + A->matrix[3][3] * B->w;
}

matrix4x4 s21_scale_matrix_reference(vector new_size_vector) {
  matrix4x4 result = {{{new_size_vector.x, 0, 0, 0},
                       {0, new_size_vector.y, 0, 0},
                       {0, 0, new_size_vector.z, 0},
                       {0, 0, 0, 1}}};

  return result;
}

void s21_calculate_scale_matrix(vector new_size_vector, polygons_t polygon) {
  matrix4x4 scale_matrix = s21_scale_matrix_reference(new_size_vector);
  for (int i = 0; i < polygon.count_of_points; i++) {
    vector result;
    s21_mult_matrix_on_vector(&scale_matrix, &polygon.points[i], &result);
    polygon.points[i].x = result.x;
    polygon.points[i].y = result.y;
    polygon.points[i].z = result.z;
  }
}

void s21_fast_calculate_scale_matrix(vector new_size_vector, vector* vec) {
  matrix4x4 scale_matrix = s21_scale_matrix_reference(new_size_vector);
  vector result;
  s21_mult_matrix_on_vector(&scale_matrix, vec, &result);
  vec->x = result.x;
  vec->y = result.y;
  vec->z = result.z;
}

matrix4x4 s21_rotation_y_matrix_reference(float degree) {
  matrix4x4 result = {{{cos(degree), 0, sin(degree), 0},
                       {0, 1, 0, 0},
                       {-sin(degree), 0, cos(degree), 0},
                       {0, 0, 0, 1}}};

  return result;
}

void s21_calculate_rotation_y_matrix(float degree, polygons_t polygon) {
  matrix4x4 rotation_matrix = s21_rotation_y_matrix_reference(degree);
  for (int i = 0; i < polygon.count_of_points; i++) {
    vector result;
    s21_mult_matrix_on_vector(&rotation_matrix, &polygon.points[i], &result);
    polygon.points[i].x = result.x;
    polygon.points[i].y = result.y;
    polygon.points[i].z = result.z;
  }
}

matrix4x4 s21_rotation_x_matrix_reference(float degree) {
  matrix4x4 result = {{{1, 0, 0, 0},
                       {0, cos(degree), -sin(degree), 0},
                       {0, sin(degree), cos(degree), 0},
                       {0, 0, 0, 1}}};

  return result;
}

void s21_calculate_rotation_x_matrix(float degree, polygons_t polygon) {
  matrix4x4 rotation_matrix = s21_rotation_x_matrix_reference(degree);
  for (int i = 0; i < polygon.count_of_points; i++) {
    vector result;
    s21_mult_matrix_on_vector(&rotation_matrix, &polygon.points[i], &result);
    polygon.points[i].x = result.x;
    polygon.points[i].y = result.y;
    polygon.points[i].z = result.z;
  }
}

matrix4x4 s21_rotation_z_matrix_reference(float degree) {
  matrix4x4 result = {{{cos(degree), -sin(degree), 0, 0},
                       {sin(degree), cos(degree), 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}}};

  return result;
}

void s21_calculate_rotation_z_matrix(float degree, polygons_t polygon) {
  matrix4x4 rotation_matrix = s21_rotation_z_matrix_reference(degree);
  for (int i = 0; i < polygon.count_of_points; i++) {
    vector result;
    s21_mult_matrix_on_vector(&rotation_matrix, &polygon.points[i], &result);
    polygon.points[i].x = result.x;
    polygon.points[i].y = result.y;
    polygon.points[i].z = result.z;
  }
}