#include "s21_mesh.h"

mesh_t parse_obj_file(char *path_to_file) {
  mesh_t result_mesh;
  result_mesh.polygons = malloc(sizeof(polygons_t));

  FILE* file;
  char str_from_file[64];

  int points_count = 0;
  int polygons_count = 0;
  vector *arr_points_tmp;

  char coordinate_x[12];
  char coordinate_y[12];
  char coordinate_z[12];

  char point_of_polygon[12];

  if ((file = fopen(path_to_file, "r")) != NULL) {
    while (fgets(str_from_file, 64, file)) {
      memset(coordinate_x, 0, 12);
      memset(coordinate_y, 0, 12);
      memset(coordinate_z, 0, 12);
      memset(point_of_polygon, 0, 12);

      // point
      if (str_from_file[0] == 'v') {

        points_count++;
      }
    }
  }

  return result_mesh;
}

mesh_t test_cube() {
  mesh_t result_mesh;

  result_mesh.count_of_polygons = 12;
  result_mesh.polygons = malloc(12 * sizeof(polygons_t));
  for (int i = 0; i < 12; i++) {
    result_mesh.polygons[i].points = (vector*)malloc(3 * sizeof(vector));
    result_mesh.polygons[i].count_of_points = 3;
  }

  vector points[8] = { {1, 1, -1}, {1, -1, -1}, {1, 1, 1}, {1, -1, 1}, {-1, 1, -1}, {-1, -1, -1}, {-1, 1, 1}, {-1, -1, 1} };

  result_mesh.polygons[0].points[0] = points[4];
  result_mesh.polygons[0].points[1] = points[2];
  result_mesh.polygons[0].points[2] = points[0];

  result_mesh.polygons[1].points[0] = points[2];
  result_mesh.polygons[1].points[1] = points[7];
  result_mesh.polygons[1].points[2] = points[3];

  result_mesh.polygons[2].points[0] = points[6];
  result_mesh.polygons[2].points[1] = points[5];
  result_mesh.polygons[2].points[2] = points[7];

  result_mesh.polygons[3].points[0] = points[1];
  result_mesh.polygons[3].points[1] = points[7];
  result_mesh.polygons[3].points[2] = points[5];

  result_mesh.polygons[4].points[0] = points[0];
  result_mesh.polygons[4].points[1] = points[3];
  result_mesh.polygons[4].points[2] = points[1];

  result_mesh.polygons[5].points[0] = points[4];
  result_mesh.polygons[5].points[1] = points[1];
  result_mesh.polygons[5].points[2] = points[5];

  result_mesh.polygons[6].points[0] = points[4];
  result_mesh.polygons[6].points[1] = points[6];
  result_mesh.polygons[6].points[2] = points[2];

  result_mesh.polygons[7].points[0] = points[2];
  result_mesh.polygons[7].points[1] = points[6];
  result_mesh.polygons[7].points[2] = points[7];

  result_mesh.polygons[8].points[0] = points[6];
  result_mesh.polygons[8].points[1] = points[4];
  result_mesh.polygons[8].points[2] = points[5];

  result_mesh.polygons[9].points[0] = points[1];
  result_mesh.polygons[9].points[1] = points[3];
  result_mesh.polygons[9].points[2] = points[7];

  result_mesh.polygons[10].points[0] = points[0];
  result_mesh.polygons[10].points[1] = points[2];
  result_mesh.polygons[10].points[2] = points[3];

  result_mesh.polygons[11].points[0] = points[4];
  result_mesh.polygons[11].points[1] = points[0];
  result_mesh.polygons[11].points[2] = points[1];

  return result_mesh;
}
