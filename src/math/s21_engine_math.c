#include "s21_engine_math.h"

void s21_scale(mesh_t *mesh, vector vector_new_size) {
  for (int polygon = 0; polygon < mesh->count_of_polygons; polygon++) {
    s21_calculate_scale_matrix(vector_new_size, mesh->polygons[polygon]);
  }
}