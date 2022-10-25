#include "s21_mesh.h"

Mesh mesh_main() {
    char path_to_obj_file[128] = "../materials/raw/krossovok.obj";
    Mesh object;

    object.polygons = malloc(sizeof(Polygon));
    FILE *file;
    char str_from_file[64];

    int size_points = 0;
    int size_polygons = 0;
    vec3D *tmp_array_of_points = NULL;

    char coordinate_x[12];
    char coordinate_y[12];
    char coordinate_z[12];

    char point_1[12];
    char point_2[12];
    char point_3[12];

    int id = 0;

    if ((file = fopen(path_to_obj_file, "r")) != NULL) {
        while (fgets(str_from_file, 64, file)) {
            memset(coordinate_x, 0, 12);
            memset(coordinate_y, 0, 12);
            memset(coordinate_z, 0, 12);
            memset(point_1, 0, 12);
            memset(point_2, 0, 12);
            memset(point_3, 0, 12);
            if (str_from_file[0] == 'v') {
                size_points++;
                size_t i = 0;
                // parse X
                for (i = 2; i < strlen(str_from_file);) {
                    if (str_from_file[i] == ' ') {
                        i++;
                        break;
                    }
                    coordinate_x[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                // parse y
                for (; i < strlen(str_from_file);) {
                    if (str_from_file[i] == ' ') {
                        i++;
                        break;
                    }
                    coordinate_y[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                // parse z
                for (; i < strlen(str_from_file);) {
                    coordinate_z[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                float tmp_x = atof(coordinate_x);
                float tmp_y = atof(coordinate_y);
                float tmp_z = atof(coordinate_z);
                tmp_array_of_points = realloc(tmp_array_of_points, size_points * sizeof(vec3D));
                if (tmp_array_of_points == NULL) {
                    exit(REALLOC_ERROR);
                }

                tmp_array_of_points[size_points - 1].x = tmp_x;
                tmp_array_of_points[size_points - 1].y = tmp_y;
                tmp_array_of_points[size_points - 1].z = tmp_z;
            } else if (str_from_file[0] == 'f') {
                size_t i = 0;
                size_polygons++;
                // parse point_1
                for (i = 2; i < strlen(str_from_file);) {
                    if (str_from_file[i] == ' ') {
                        i++;
                        break;
                    }
                    point_1[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                // parse point_2
                for (;i < strlen(str_from_file);) {
                    if (str_from_file[i] == ' ') {
                        i++;
                        break;
                    }
                    point_2[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                // parse point_3
                for (; i < strlen(str_from_file);) {
                    point_3[id] = str_from_file[i];
                    id++;
                    i++;
                }
                id = 0;

                int index_1 = atoi(point_1);
                int index_2 = atoi(point_2);
                int index_3 = atoi(point_3);
                // printf("\nARRAY OF POLYGONS:\n");
                // printf("f %d %d %d\n", index_1, index_2, index_3);
                object.polygons = realloc(object.polygons, size_polygons * sizeof(Polygon));
                object.polygons[size_polygons - 1].points[0] = tmp_array_of_points[index_1 - 1];
                object.polygons[size_polygons - 1].points[1] = tmp_array_of_points[index_2 - 1];
                object.polygons[size_polygons - 1].points[2] = tmp_array_of_points[index_3 - 1];
            }
        }
        fclose(file);
    } else {
        printf("\n%d\n", FILE_NOT_FIND);
        exit(FILE_NOT_FIND);
    }
    object.polygons->count_points = size_points;
    object.count_polygons = size_polygons;

    free(tmp_array_of_points);
    printf("\nReading file: success\n");
    return object;
}

Mesh mesh_copy(Mesh original) {
    Mesh new_mesh;

    new_mesh.count_polygons = original.count_polygons;
    new_mesh.polygons = malloc(new_mesh.count_polygons * sizeof(Polygon));
    for (int i = 0; i < new_mesh.count_polygons; i++) {
        for (int j = 0; j < 3; j++)
        {
            new_mesh.polygons[i].points[j] = original.polygons[i].points[j];
        }
    }

    return new_mesh;
}

Mesh plane() {
    Mesh plane;
    plane.polygons = malloc(2 * sizeof(Polygon));
    if (plane.polygons == NULL) {
        exit(MALLOC_ERROR);    
    }

    vec3D points[4] = { {-1, 0, 1}, {1, 0, 1}, {-1, 0, -1}, {1, 0, -1} };

    plane.polygons[0].points[0] = points[1];
    plane.polygons[0].points[1] = points[3];
    plane.polygons[0].points[2] = points[2];

    plane.polygons[1].points[0] = points[0];
    plane.polygons[1].points[1] = points[1];
    plane.polygons[1].points[2] = points[2];

    return plane;
}

Mesh cube() {
    Mesh cube;
    cube.polygons = malloc(12 * sizeof(Polygon));

    vec3D points[8] = { {1, 1, -1}, {1, -1, -1}, {1, 1, 1}, {1, -1, 1}, {-1, 1, -1}, {-1, -1, -1}, {-1, 1, 1}, {-1, -1, 1} };

    cube.polygons[0].points[0] = points[4];
    cube.polygons[0].points[1] = points[2];
    cube.polygons[0].points[2] = points[0];

    cube.polygons[1].points[0] = points[2];
    cube.polygons[1].points[1] = points[7];
    cube.polygons[1].points[2] = points[3];

    cube.polygons[2].points[0] = points[6];
    cube.polygons[2].points[1] = points[5];
    cube.polygons[2].points[2] = points[7];

    cube.polygons[3].points[0] = points[1];
    cube.polygons[3].points[1] = points[7];
    cube.polygons[3].points[2] = points[5];

    cube.polygons[4].points[0] = points[0];
    cube.polygons[4].points[1] = points[3];
    cube.polygons[4].points[2] = points[1];

    cube.polygons[5].points[0] = points[4];
    cube.polygons[5].points[1] = points[1];
    cube.polygons[5].points[2] = points[5];

    cube.polygons[6].points[0] = points[4];
    cube.polygons[6].points[1] = points[6];
    cube.polygons[6].points[2] = points[2];

    cube.polygons[7].points[0] = points[2];
    cube.polygons[7].points[1] = points[6];
    cube.polygons[7].points[2] = points[7];

    cube.polygons[8].points[0] = points[6];
    cube.polygons[8].points[1] = points[4];
    cube.polygons[8].points[2] = points[5];

    cube.polygons[9].points[0] = points[1];
    cube.polygons[9].points[1] = points[3];
    cube.polygons[9].points[2] = points[7];

    cube.polygons[10].points[0] = points[0];
    cube.polygons[10].points[1] = points[2];
    cube.polygons[10].points[2] = points[3];

    cube.polygons[11].points[0] = points[4];
    cube.polygons[11].points[1] = points[0];
    cube.polygons[11].points[2] = points[1];

    return cube;
}

Mesh cube_many_polygons() {
    Mesh cube;
    cube.polygons = malloc(20 * sizeof(Polygon));

    vec3D points[12] = { {-1, 1, -1}, {1, 1, 1}, {1, 1, -1}, {-1, -1, 1}, {1, -1, 1}, {-1, 1, 1}, {-1, -1, -1}, {1, -1, -1}, {-1, 0, 0}, {0, -0, 1}, {1, 0, 0}, {0, 0, -1} };

    cube.polygons[0].points[0] = points[0];
    cube.polygons[0].points[1] = points[1];
    cube.polygons[0].points[2] = points[2];

    cube.polygons[1].points[0] = points[9];
    cube.polygons[1].points[1] = points[3];
    cube.polygons[1].points[2] = points[4];

    cube.polygons[2].points[0] = points[8];
    cube.polygons[2].points[1] = points[6];
    cube.polygons[2].points[2] = points[3];

    cube.polygons[3].points[0] = points[7];
    cube.polygons[3].points[1] = points[3];
    cube.polygons[3].points[2] = points[6];

    cube.polygons[4].points[0] = points[10];
    cube.polygons[4].points[1] = points[4];
    cube.polygons[4].points[2] = points[7];

    cube.polygons[5].points[0] = points[11];
    cube.polygons[5].points[1] = points[7];
    cube.polygons[5].points[2] = points[6];

    cube.polygons[6].points[0] = points[0];
    cube.polygons[6].points[1] = points[5];
    cube.polygons[6].points[2] = points[1];

    cube.polygons[7].points[0] = points[5];
    cube.polygons[7].points[1] = points[3];
    cube.polygons[7].points[2] = points[9];

    cube.polygons[8].points[0] = points[0];
    cube.polygons[8].points[1] = points[6];
    cube.polygons[8].points[2] = points[8];

    cube.polygons[9].points[0] = points[7];
    cube.polygons[9].points[1] = points[4];
    cube.polygons[9].points[2] = points[3];

    cube.polygons[10].points[0] = points[1];
    cube.polygons[10].points[1] = points[4];
    cube.polygons[10].points[2] = points[10];

    cube.polygons[11].points[0] = points[2];
    cube.polygons[11].points[1] = points[7];
    cube.polygons[11].points[2] = points[11];

    cube.polygons[12].points[0] = points[5];
    cube.polygons[12].points[1] = points[8];
    cube.polygons[12].points[2] = points[3];

    cube.polygons[13].points[0] = points[5];
    cube.polygons[13].points[1] = points[0];
    cube.polygons[13].points[2] = points[8];

    cube.polygons[14].points[0] = points[1];
    cube.polygons[14].points[1] = points[5];
    cube.polygons[14].points[2] = points[9];

    cube.polygons[15].points[0] = points[1];
    cube.polygons[15].points[1] = points[9];
    cube.polygons[15].points[2] = points[4];

    cube.polygons[16].points[0] = points[2];
    cube.polygons[16].points[1] = points[10];
    cube.polygons[16].points[2] = points[7];

    cube.polygons[17].points[0] = points[2];
    cube.polygons[17].points[1] = points[1];
    cube.polygons[17].points[2] = points[10];

    cube.polygons[18].points[0] = points[0];
    cube.polygons[18].points[1] = points[11];
    cube.polygons[18].points[2] = points[6];

    cube.polygons[19].points[0] = points[0];
    cube.polygons[19].points[1] = points[2];
    cube.polygons[19].points[2] = points[11];

    return cube;
}
