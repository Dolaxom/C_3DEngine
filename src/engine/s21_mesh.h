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
  int count_of_polygons;
  int count_of_points;
  vector scale;
  vector rotation;
  vector location;
} mesh_t;

mesh_t parse_obj_file(char* path_to_file, int* error_code);
void copy_polygons(mesh_t original_mesh);

// helpers
mesh_t file_parser(const char *path_to_file, int *error_code, mesh_t result_mesh);
void initial_allocation(mesh_t *result_mesh);
void memset_iterations(char *coordinate_x, char *coordinate_y, char *coordinate_z, char *point);
void find_faces_and_points(FILE *file, char *str_from_file, char *coordinate_x, char *coordinate_y, char *coordinate_z,
                           char *point, int *index, mesh_t *result_mesh, vector **tmp_array_of_points,
                           int *points_count, int *polygons_count);
void check_file(const char *path_to_file, int *error_code, char *str_from_file, char *coordinate_x,
                char *coordinate_y, char *coordinate_z, char *point, int *index, mesh_t *result_mesh,
                vector **tmp_array_of_points, int *points_count, int *polygons_count);
void get_faces_from_file(const char *str_from_file, const vector *tmp_array_of_points, char *point, size_t i,
                         mesh_t *result_mesh, int *polygons_count, int *index);
void
get_points_from_file(const char *str_from_file, char *coordinate_x, char *coordinate_y, char *coordinate_z, size_t i,
                     vector **tmp_array_of_points, int *points_count, int *index);


#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_MESH_H_
