#include "s21_mesh.h"

void copy_polygons(mesh_t original_mesh) {
  for (int i = 0; i < original_mesh.count_of_polygons; i++) {
    for (int j = 0; j < original_mesh.polygons[i].count_of_points; j++) {
      original_mesh.polygons_copy[i].points[j] = original_mesh.polygons[i].points[j];
    }
  }
}

void copy_points(mesh_t original_mesh) {
  for (int i = 0; i < original_mesh.count_of_points; i++) {
    original_mesh.v_points_copy[i] = original_mesh.v_points[i];
  }
}

mesh_t parse_obj_file(char* path_to_file, int* error_code) {
  mesh_t result_mesh;
  *error_code = S21_OK;
  result_mesh.legacy_render = 0;
  result_mesh.polygons = malloc(sizeof(polygons_t));
  result_mesh.polygons_copy = malloc(sizeof(polygons_t) * 2);
  result_mesh.queue = malloc(0);
  if (result_mesh.polygons == NULL ||
    result_mesh.polygons_copy == NULL) {

    exit(S21_MALLOC);
  }

  FILE* file;
  char str_from_file[64];

  result_mesh.v_points = malloc(1);
  result_mesh.v_points_copy = malloc(2);
  char coordinate_x[12];
  char coordinate_y[12];
  char coordinate_z[12];
  char point[12];

  int points_count = 0;
  int polygons_count = 0;
  size_t queue_count = 0;

  int index = 0;

  if ((file = fopen(path_to_file, "r")) != NULL) {
    while (fgets(str_from_file, 64, file)) {
      memset(coordinate_x, 0, 12);
      memset(coordinate_y, 0, 12);
      memset(coordinate_z, 0, 12);
      memset(point, 0, 12);
      size_t i = 2;
      if (str_from_file[0] == 'v') {
        points_count++;
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
        
        result_mesh.v_points = realloc(result_mesh.v_points, points_count * sizeof(vector));
        result_mesh.v_points_copy = realloc(result_mesh.v_points_copy, points_count * sizeof(vector));
        if (result_mesh.v_points == NULL ||
            result_mesh.v_points_copy == NULL ) {
            exit(S21_REALLOC);
        }

        int offset_array = 1;
        result_mesh.v_points[points_count - offset_array].x = tmp_x;
        result_mesh.v_points[points_count - offset_array].y = tmp_y;
        result_mesh.v_points[points_count - offset_array].z = tmp_z;
        result_mesh.v_points[points_count - offset_array].w = 1;

      } else if (str_from_file[0] == 'f') {
        polygons_count++;
        int *points_tmp = NULL;
        int current_points_count = 0;
        while (str_from_file[i] != '\0' && str_from_file[i] != '\n') {
          while (str_from_file[i] != ' ' &&
                str_from_file[i] != '\0' && str_from_file[i] != '\n') {
            point[index] = str_from_file[i];
            index++;
            i++;
          }

          points_tmp = realloc(points_tmp, (current_points_count + 1) * sizeof(int));
          if (points_tmp == NULL) {
              exit(S21_REALLOC);
          }

          points_tmp[current_points_count] = atoi(point);
          memset(point, 0, 12);
          current_points_count++;
          if (str_from_file[i] == ' ') {
            i++;
          }
          index = 0;
        }

        int offset_array = 1;
        result_mesh.polygons = realloc(result_mesh.polygons, polygons_count * sizeof(polygons_t));
        result_mesh.polygons_copy = realloc(result_mesh.polygons_copy, polygons_count * sizeof(polygons_t));
        if (result_mesh.polygons == NULL || result_mesh.polygons_copy == NULL ) {
            exit(S21_REALLOC);
        }

        result_mesh.polygons[polygons_count - offset_array].points = (vector*)malloc(current_points_count * sizeof(vector));
        result_mesh.polygons_copy[polygons_count - offset_array].points = (vector*)malloc(current_points_count * sizeof(vector));
        if (result_mesh.polygons[polygons_count - offset_array].points == NULL ||
        result_mesh.polygons_copy[polygons_count - offset_array].points == NULL) {
          exit(S21_MALLOC);
        }

        for (int z = 0; z < current_points_count; z++) {
          result_mesh.polygons[polygons_count - offset_array].points[z] = result_mesh.v_points[points_tmp[z] - offset_array];
        }
        result_mesh.queue = realloc(result_mesh.queue, (queue_count + current_points_count) * sizeof(size_t));

        for (int k = 0; k < current_points_count; k++) {
          result_mesh.queue[queue_count] = points_tmp[k] - offset_array;
          queue_count++;
        }
        result_mesh.polygons[polygons_count - offset_array].count_of_points = current_points_count;
        result_mesh.polygons_copy[polygons_count - offset_array].count_of_points = current_points_count;

        if (current_points_count > 3) {
          result_mesh.legacy_render = 1;
        }
        free(points_tmp);
      }
    }
    fclose(file);
  } else {
    *error_code = S21_FILE;
  }
  if (!(*error_code)) {
      result_mesh.count_of_points = points_count;
      result_mesh.count_of_polygons = polygons_count;
      result_mesh.size_of_queue = queue_count;
  }

  return result_mesh;
}
