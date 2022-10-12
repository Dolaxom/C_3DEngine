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
