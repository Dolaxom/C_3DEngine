#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#include "s21_engine.h"

typedef struct Polygon {
    vec3D points[3];
    int count_points;
} Polygon;

typedef struct Mesh {
    Polygon *polygons;
    int count_polygons;
} Mesh;

int s21_mesh_info(Mesh mesh);

Mesh plane();
Mesh cube();

#endif  // SRC_S21_CALCULATOR_H_