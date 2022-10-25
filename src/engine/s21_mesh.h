#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#include <string.h>
#include "s21_engine.h"

typedef struct Polygon {
    vec3D points[3];
    int count_points;
} Polygon;

typedef struct Mesh {
    Polygon *polygons;
    int count_polygons;
} Mesh;

Mesh mesh_copy(Mesh original);

Mesh plane();
Mesh cube();
Mesh cube_many_polygons();

Mesh mesh_main();

#endif  // SRC_S21_CALCULATOR_H_