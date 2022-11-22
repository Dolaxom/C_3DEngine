#include "s21_mesh.h"

void copy_polygons(mesh_t original_mesh) {
    for (int i = 0; i < original_mesh.count_of_polygons; i++) {
        for (int j = 0; j < original_mesh.polygons[i].count_of_points; j++) {
            original_mesh.polygons_copy[i].points[j] = original_mesh.polygons[i].points[j];
        }
    }
}

mesh_t parse_obj_file(char* path_to_file, int* error_code) {
    *error_code = S21_OK;
    mesh_t result_mesh;
    initial_allocation(&result_mesh);
    result_mesh = file_parser(path_to_file, error_code, result_mesh);

    return result_mesh;
}

// helpers
mesh_t file_parser(const char *path_to_file, int *error_code, mesh_t result_mesh) {
    char str_from_file[64];
    vector *tmp_array_of_points = NULL;
    char coordinate_x[12];
    char coordinate_y[12];
    char coordinate_z[12];
    char point[12];

    int points_count = 0;
    int polygons_count = 0;

    int index = 0;

    check_file(path_to_file, error_code, str_from_file, coordinate_x, coordinate_y,
               coordinate_z, point, &index, &result_mesh, &tmp_array_of_points, &points_count, &polygons_count);
    if (!(*error_code)) {
        result_mesh.count_of_points = points_count;
        result_mesh.count_of_polygons = polygons_count;
        free(tmp_array_of_points);
    }
    return result_mesh;
}

void check_file(const char *path_to_file, int *error_code, char *str_from_file, char *coordinate_x,
                char *coordinate_y, char *coordinate_z, char *point, int *index, mesh_t *result_mesh,
                vector **tmp_array_of_points, int *points_count, int *polygons_count) {
    FILE* file;
    if ((file = fopen(path_to_file, "r")) != NULL) {
        find_faces_and_points(file, str_from_file, coordinate_x, coordinate_y, coordinate_z, point, index,
                              result_mesh, tmp_array_of_points,
                              points_count, polygons_count);
        fclose(file);
    } else {
        *error_code = S21_FILE;
    }
}

void find_faces_and_points(FILE *file, char *str_from_file, char *coordinate_x, char *coordinate_y, char *coordinate_z,
                           char *point, int *index, mesh_t *result_mesh, vector **tmp_array_of_points,
                           int *points_count, int *polygons_count) {
    while (fgets(str_from_file, 64, file)) {
        memset_iterations(coordinate_x, coordinate_y, coordinate_z, point);
        size_t i = 2;
        if (str_from_file[0] == 'v') {
            get_points_from_file(str_from_file, coordinate_x, coordinate_y, coordinate_z, i, tmp_array_of_points,
                                 points_count, index);
        } else if (str_from_file[0] == 'f') {
            get_faces_from_file(str_from_file, (*tmp_array_of_points), point, i, result_mesh, polygons_count,
                                index);
        }
    }
}

void get_faces_from_file(const char *str_from_file, const vector *tmp_array_of_points, char *point, size_t i,
                         mesh_t *result_mesh, int *polygons_count, int *index) {
    (*polygons_count)++;
    int *points_tmp = NULL;
    int counts = 0;
    while (str_from_file[i] != '\0' && str_from_file[i] != '\n') {
        while (str_from_file[i] != ' ' &&
               str_from_file[i] != '\0' && str_from_file[i] != '\n') {
            point[(*index)] = str_from_file[i];
            (*index)++;
            i++;
        }

        points_tmp = (int*)realloc(points_tmp, (counts + 1) * sizeof(int));
        if (points_tmp == NULL) {
            exit(S21_REALLOC);
        }

        points_tmp[counts] = atoi(point);
        memset(point, 0, 12);
        counts++;
        if (str_from_file[i] == ' ') {
            i++;
        }
        (*index) = 0;
    }

    int offset_array = 1;
    (*result_mesh).polygons = (polygons_t*)realloc((*result_mesh).polygons, (*polygons_count) * sizeof(polygons_t));
    (*result_mesh).polygons_copy = (polygons_t*)realloc((*result_mesh).polygons_copy, (*polygons_count) * sizeof(polygons_t));
    if ((*result_mesh).polygons == NULL || (*result_mesh).polygons_copy == NULL ) {
        exit(S21_REALLOC);
    }

    (*result_mesh).polygons[(*polygons_count) - offset_array].points = (vector*)malloc(counts * sizeof(vector));
    (*result_mesh).polygons_copy[(*polygons_count) - offset_array].points = (vector*)malloc(counts * sizeof(vector));
    if ((*result_mesh).polygons[(*polygons_count) - offset_array].points == NULL ||
        (*result_mesh).polygons_copy[(*polygons_count) - offset_array].points == NULL) {
        exit(S21_MALLOC);
    }

    for (int z = 0; z < counts; z++) {
        (*result_mesh).polygons[(*polygons_count) - offset_array].points[z] = tmp_array_of_points[points_tmp[z] - offset_array];
    }

    (*result_mesh).polygons[(*polygons_count) - offset_array].count_of_points = counts;
    (*result_mesh).polygons_copy[(*polygons_count) - offset_array].count_of_points = counts;
    free(points_tmp);
}

void
get_points_from_file(const char *str_from_file, char *coordinate_x, char *coordinate_y, char *coordinate_z, size_t i,
                     vector **tmp_array_of_points, int *points_count, int *index) {
    (*points_count)++;
    // parse X
    for (i = 2; i < strlen(str_from_file);) {
        if (str_from_file[i] == ' ') {
            i++;
            break;
        }
        coordinate_x[(*index)] = str_from_file[i];
        (*index)++;
        i++;
    }
    (*index) = 0;

    // parse Y
    for (; i < strlen(str_from_file);) {
        if (str_from_file[i] == ' ') {
            i++;
            break;
        }
        coordinate_y[(*index)] = str_from_file[i];
        (*index)++;
        i++;
    }
    (*index) = 0;

    // parse Z
    for (; i < strlen(str_from_file);) {
        coordinate_z[(*index)] = str_from_file[i];
        (*index)++;
        i++;
    }
    (*index) = 0;

    float tmp_x = atof(coordinate_x);
    float tmp_y = atof(coordinate_y);
    float tmp_z = atof(coordinate_z);

    (*tmp_array_of_points) = (vector*)realloc((*tmp_array_of_points), (*points_count) * sizeof(vector));
    if ((*tmp_array_of_points) == NULL) {
        exit(S21_REALLOC);
    }

    int offset_array = 1;
    (*tmp_array_of_points)[(*points_count) - offset_array].x = tmp_x;
    (*tmp_array_of_points)[(*points_count) - offset_array].y = tmp_y;
    (*tmp_array_of_points)[(*points_count) - offset_array].z = tmp_z;
    (*tmp_array_of_points)[(*points_count) - offset_array].w = 1;
}

void memset_iterations(char *coordinate_x, char *coordinate_y, char *coordinate_z, char *point) {
    memset(coordinate_x, 0, 12);
    memset(coordinate_y, 0, 12);
    memset(coordinate_z, 0, 12);
    memset(point, 0, 12);
}

void initial_allocation(mesh_t *result_mesh) {
    result_mesh->polygons = (polygons_t*)malloc(sizeof(polygons_t));
    result_mesh->polygons_copy = (polygons_t*)malloc(sizeof(polygons_t) * 2);
    if (result_mesh->polygons == NULL ||
        result_mesh->polygons_copy == NULL) {
        exit(S21_MALLOC);
    }
}