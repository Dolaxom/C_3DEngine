#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Vec3D {
    double x;
    double y;
    double z;
} vec3D;

typedef struct Polygon {
    vec3D points[3];
} Polygon;

typedef struct Mesh {
    Polygon *polygons;
} Mesh;

Mesh plane();

#endif  // SRC_S21_CALCULATOR_H_
