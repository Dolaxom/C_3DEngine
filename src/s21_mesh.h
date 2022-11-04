#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#include "s21_engine.h"

typedef struct Polygons_s {
  vector* points;
  int count_of_points;
} polygons_t;

typedef struct Mesh_s {
  polygons_t* polygons;
  int count_of_polygons;
  vector scale;
  vector rotation;
  vector location;
} mesh_t;

mesh_t parse_obj_file(char *path_to_file);
mesh_t test_cube();
mesh_t test_simple_cube();

#endif  // SRC_S21_MESH_H_