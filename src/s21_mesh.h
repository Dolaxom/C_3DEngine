#ifndef SRC_S21_MESH_H_
#define SRC_S21_MESH_H_

typedef struct Vec3D {
    double x;
    double y;
    double z;
} vec3D;

typedef struct Polygon {
    vec3D points[3];
} polygon;

typedef struct Mesh
{
    Polygon *polygons;
} mesh;



#endif  // SRC_S21_CALCULATOR_H_
