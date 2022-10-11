#include "s21_screen.h"

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

void display() {
    Mesh mesh = plane();
    mesh.count_polygons = 2;
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

    free(mesh.polygons);
}

void render_tris(Mesh mesh) {
    for (int polygon = 0; polygon < mesh.count_polygons; polygon++) {
        glBegin(GL_TRIANGLES);
        for (int point = 0; point < 3; point++) {
            glColor3f(0, 0, 0);
            glVertex3f(mesh.polygons[polygon].points[point].x, mesh.polygons[polygon].points[point].z, mesh.polygons[polygon].points[point].y);
        }
        glEnd();
    }
}
