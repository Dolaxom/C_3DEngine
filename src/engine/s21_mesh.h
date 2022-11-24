#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "s21_engine.h"

typedef struct Polygons_s {
  vector* points;
  int count_of_points;
} polygons_t;

typedef struct Mesh_s {
  polygons_t* polygons;
  polygons_t* polygons_copy;
  vector* v_points;
  unsigned int* queue;
  int count_of_polygons;
  int count_of_points;
  unsigned int size_of_queue;
  vector scale;
  vector rotation;
  vector location;
} mesh_t;

mesh_t parse_obj_file(char* path_to_file, int* error_code);
void copy_polygons(mesh_t original_mesh);
void copy_points(mesh_t original_mesh);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_MESH_H_
