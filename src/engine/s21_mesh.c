#include "s21_mesh.h"

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
