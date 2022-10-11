#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#include "s21_engine.h"

typedef struct Vec3D {
    float x;
    float y;
    float z;
} vec3D;

typedef struct Polygon {
    vec3D points[3];
} Polygon;

typedef struct Mesh {
    Polygon *polygons;
    int count_polygons;
} Mesh;


Mesh plane();

#endif  // SRC_S21_CALCULATOR_H_