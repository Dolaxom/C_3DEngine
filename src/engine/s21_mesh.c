#include "s21_mesh.h"

mesh_t parse_obj_file(char *path_to_file) {
  mesh_t result_mesh;
  result_mesh.polygons = malloc(sizeof(polygons_t));
  if (result_mesh.polygons == NULL) {
    exit(S21_MALLOC);
  }

  FILE* file;
  char str_from_file[64];

  vector *tmp_array_of_points = NULL;
  char coordinate_x[12];
  char coordinate_y[12];
  char coordinate_z[12];
  char point[12];

  int points_count = 0;
  int polygons_count = 0;

  int index = 0;

  if ((file = fopen(path_to_file, "r")) != NULL) {
    while (fgets(str_from_file, 64, file)) {
      memset(coordinate_x, 0, 12);
      memset(coordinate_y, 0, 12);
      memset(coordinate_z, 0, 12);
      memset(point, 0, 12);
      if (str_from_file[0] == 'v') {
        points_count++;
        size_t i = 0;
        // parse X
        for (i = 2; i < strlen(str_from_file);) {
            if (str_from_file[i] == ' ') {
                i++;
                break;
            }
            coordinate_x[index] = str_from_file[i];
            index++;
            i++;
        }
        index = 0;

        // parse Y
        for (; i < strlen(str_from_file);) {
            if (str_from_file[i] == ' ') {
                i++;
                break;
            }
            coordinate_y[index] = str_from_file[i];
            index++;
            i++;
        }
        index = 0;

        // parse Z
        for (; i < strlen(str_from_file);) {
            coordinate_z[index] = str_from_file[i];
            index++;
            i++;
        }
        index = 0;

        float tmp_x = atof(coordinate_x);
        float tmp_y = atof(coordinate_y);
        float tmp_z = atof(coordinate_z);
        tmp_array_of_points = realloc(tmp_array_of_points, points_count * sizeof(vector));
        if (tmp_array_of_points == NULL) {
            exit(S21_REALLOC);
        }

        int offset_array = 1;
        tmp_array_of_points[points_count - offset_array].x = tmp_x;
        tmp_array_of_points[points_count - offset_array].y = tmp_y;
        tmp_array_of_points[points_count - offset_array].z = tmp_z;
      } else if (str_from_file[0] == 'f') {
        size_t i = 2;
        polygons_count++;
        int *points_tmp = NULL;
        int counts = 0;
        while (str_from_file[i] != '\0' && str_from_file[i] != '\n') {
          while (str_from_file[i] != ' ' &&
          str_from_file[i] != '\0' && str_from_file[i] != '\n') {
            point[index] = str_from_file[i];
            index++;
            i++;
          }
          points_tmp = realloc(points_tmp, (counts + 1) * sizeof(int));
          if (points_tmp == NULL) {
              exit(S21_REALLOC);
          }
          points_tmp[counts] = atoi(point);
          memset(point, 0, 12);
          counts++;
          if (str_from_file[i] == ' ') {
            i++;
          }
          index = 0;
        }

        result_mesh.polygons = realloc(result_mesh.polygons, polygons_count * sizeof(polygons_t));
        if (result_mesh.polygons == NULL) {
            exit(S21_REALLOC);
        }
        result_mesh.polygons[polygons_count - 1].points = (vector*)malloc(counts * sizeof(vector));
        if (result_mesh.polygons[polygons_count - 1].points == NULL) {
          exit(S21_MALLOC);
        }
        for (int z = 0; z < counts; z++) {
          result_mesh.polygons[polygons_count - 1].points[z] = tmp_array_of_points[points_tmp[z] - 1];
        }
        result_mesh.polygons[polygons_count - 1].count_of_points = counts;
        free(points_tmp);
      }
    }
    fclose(file);
  } else {
    printf("\n%d\n", S21_FILE);
    exit(S21_FILE);
  }
  result_mesh.count_of_polygons = polygons_count;
  free(tmp_array_of_points);
  printf("\nReading file: success\n");
  return result_mesh;
}
