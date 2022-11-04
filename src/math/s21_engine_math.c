#include "s21_engine_math.h"

void s21_scale(mesh_t *mesh, float new_x, float new_y, float new_z) {
  vector vector_new_size = { new_x, new_y, new_z, 1.0 };
  mesh->scale = vector_new_size;
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_scale_matrix(mesh->scale, mesh->polygons[polygon]);
  }
}