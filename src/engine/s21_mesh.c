#include "s21_mesh.h"

Mesh plane() {
    Mesh plane;
    plane.polygons = malloc(2 * sizeof(Polygon));
    if (plane.polygons == NULL) {
        exit(1);    
    }

    vec3D points[4] = { {-0.5, 0, 0.5}, {0.5, 0, 0.5}, {-0.5, 0, -0.5}, {0.5, 0, -0.5} };

    plane.polygons[0].points[0] = points[1];
    plane.polygons[0].points[1] = points[3];
    plane.polygons[0].points[2] = points[2];

    plane.polygons[1].points[0] = points[0];
    plane.polygons[1].points[1] = points[1];
    plane.polygons[1].points[2] = points[2];

    return plane;
}
