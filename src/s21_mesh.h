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
} mesh_t;

mesh_t parse_obj_file();

#endif  // SRC_S21_MESH_H_