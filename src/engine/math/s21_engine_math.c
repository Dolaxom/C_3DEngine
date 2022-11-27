#include "s21_engine_math.h"

float s21_degree_to_radian(float degree) {
  return degree * 3.141593 / 180;
}

void s21_scale(mesh_t *mesh, float new_x, float new_y, float new_z) {
  if (mesh->scale.x == 1 && mesh->scale.y == 1 && mesh->scale.z == 1 &&
    new_x == 1 && new_y == 1 && new_z == 1) {
    return;
  }
  vector vector_new_size = { new_x, new_y, new_z, 1.0 };
  mesh->scale = vector_new_size;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_scale_matrix(mesh->scale, mesh->polygons_copy[polygon]);
  }
}

void s21_fast_scale(mesh_t *mesh, float new_x, float new_y, float new_z) {
  if (mesh->scale.x == 1 && mesh->scale.y == 1 && mesh->scale.z == 1 &&
    new_x == 1 && new_y == 1 && new_z == 1) {
    return;
  }
  vector vector_new_size = { new_x, new_y, new_z, 1.0 };
  mesh->scale = vector_new_size;
  for (int i = 0; i < mesh->count_of_points; i++) {
    s21_fast_calculate_scale_matrix(mesh->scale, &mesh->v_points_copy[i]);
  }
}

void s21_rotate_x(mesh_t *mesh, float degree) {
  if (mesh->rotation.x == 0 && degree == 0) {
    return;
  }
  mesh->rotation.x = degree;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_x_matrix(mesh->rotation.x, mesh->polygons_copy[polygon]);
  }
}

void s21_fast_rotate_x(mesh_t *mesh, float degree) {
  if (mesh->rotation.x == 0 && degree == 0) {
    return;
  }
  mesh->rotation.x = degree;
  for (int i = 0; i < mesh->count_of_points; i++) {
    s21_fast_calculate_rotation_y_matrix(mesh->rotation.x, &mesh->v_points_copy[i]);
  }
}

void s21_rotate_y(mesh_t *mesh, float degree) {
  if (mesh->rotation.y == 0 && degree == 0) {
    return;
  }
  mesh->rotation.y = degree;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_y_matrix(mesh->rotation.y, mesh->polygons_copy[polygon]);
  }
}

void s21_fast_rotate_y(mesh_t *mesh, float degree) {
  if (mesh->rotation.y == 0 && degree == 0) {
    return;
  }
  mesh->rotation.y = degree;
  for (int i = 0; i < mesh->count_of_points; i++) {
    s21_fast_calculate_rotation_y_matrix(mesh->rotation.y, &mesh->v_points_copy[i]);
  }
}

void s21_rotate_z(mesh_t *mesh, float degree) {
  if (mesh->rotation.z == 0 && degree == 0) {
    return;
  }
  mesh->rotation.z = degree;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_rotation_z_matrix(mesh->rotation.z, mesh->polygons_copy[polygon]);
  }
}

void s21_fast_rotate_z(mesh_t *mesh, float degree) {
  if (mesh->rotation.z == 0 && degree == 0) {
    return;
  }
  mesh->rotation.y = degree;
  for (int i = 0; i < mesh->count_of_points; i++) {
    s21_fast_calculate_rotation_z_matrix(mesh->rotation.z, &mesh->v_points_copy[i]);
  }
}