#include "s21_screen.h"
#include <unistd.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("3DViewer");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

float move = 0.0;
void display() {
    Mesh mesh = cube();
    vec3D size = {0.5, 0.5, 0.5};
    vec3D translate = {0.0, 0.0, -3.0};
    mesh.count_polygons = 12;
    mesh.polygons->count_points = 8;
    s21_rotation_x(&mesh, move);
    s21_rotation_y(&mesh, move);
    s21_translate(&mesh, translate);
    s21_rotation_z(&mesh, move);
    s21_projection(&mesh, 1.77777, to_radians(45), 3000, 0.0);
    s21_scale(&mesh, size);
    move += 0.01;
    usleep(10000);
    mesh_info(mesh);
    printf("polygon1: x%f y%f z%f\n", mesh.polygons[0].points[0].x, mesh.polygons[0].points[0].y, mesh.polygons[0].points[0].z);
    printf("polygon2: x%f y%f z%f\n", mesh.polygons[1].points[0].x, mesh.polygons[1].points[0].y, mesh.polygons[1].points[0].z);
    printf("\e[H\e[2J\e[3J");
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_BLEND);
    // Smooth lines
    glEnable(GL_LINE_SMOOTH);               
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    render_tris(mesh);

    glutSwapBuffers();
    glutPostRedisplay();
    free(mesh.polygons);
}

void render_tris(Mesh mesh) {
    for (int polygon = 0; polygon < mesh.count_polygons; polygon++) {
        glBegin(GL_TRIANGLES);
        for (int point = 0; point < 3; point++) {
            glColor3f(0, 0, 0);
            glVertex3f(mesh.polygons[polygon].points[point].x, mesh.polygons[polygon].points[point].y, mesh.polygons[polygon].points[point].z);
        }
        glEnd();
    }
}
