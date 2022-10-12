#include "s21_screen.h"
#include <unistd.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3DViewer");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

float move = 0.0;
void display() {
    Mesh mesh = cube();
    vec3D size = {0.5, 0.5, 0.5};
    mesh.count_polygons = 12;
    s21_scale(&mesh, size);
    s21_rotation_x(&mesh, 0.1);
    s21_rotation_y(&mesh, move);
    move += 0.01;
    usleep(10000);
    // s21_rotation_x(&mesh, 0.1);
    // s21_rotation_z(&mesh, 0.1);
    printf("%f %f %f\n", mesh.polygons[0].points[0].x, mesh.polygons[0].points[0].y, mesh.polygons[0].points[0].z);
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
