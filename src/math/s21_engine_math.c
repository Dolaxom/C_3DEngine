#include "s21_engine_math.h"

float s21_degree_to_radian(float degree) {
  return degree * 3.141593 / 180;
}

void s21_scale(mesh_t *mesh, float new_x, float new_y, float new_z) {
  vector vector_new_size = { new_x, new_y, new_z, 1.0 };
  mesh->scale = vector_new_size;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_scale_matrix(mesh->scale, mesh->polygons[polygon]);
  }
}

void s21_rotate_y(mesh_t *mesh, float degree) {
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_y_matrix(degree, mesh->polygons[polygon]);
  }
}

void s21_rotate_x(mesh_t *mesh, float degree) {
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_x_matrix(degree, mesh->polygons[polygon]);
  }
}

void s21_rotate_z(mesh_t *mesh, float degree) {
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_z_matrix(degree, mesh->polygons[polygon]);
  }
}