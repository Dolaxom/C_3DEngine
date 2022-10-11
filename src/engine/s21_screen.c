#include "s21_screen.h"

void display() {
    Mesh mesh = plane();

    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_BLEND);
    // Сглаживание линий
    glEnable(GL_LINE_SMOOTH);               
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(10);
    glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 0);
        
        glVertex3f(mesh.polygons[0].points[0].x, mesh.polygons[0].points[0].z, mesh.polygons[0].points[0].y);
        glVertex3f(mesh.polygons[0].points[1].x, mesh.polygons[0].points[1].z, mesh.polygons[0].points[1].y);
        glVertex3f(mesh.polygons[0].points[2].x, mesh.polygons[0].points[2].z, mesh.polygons[0].points[2].y);

        glVertex3f(mesh.polygons[1].points[0].x, mesh.polygons[1].points[0].z, mesh.polygons[1].points[0].y);
        glVertex3f(mesh.polygons[1].points[1].x, mesh.polygons[1].points[1].z, mesh.polygons[1].points[1].y);
        glVertex3f(mesh.polygons[1].points[2].x, mesh.polygons[1].points[2].z, mesh.polygons[1].points[2].y);

    glEnd();


    glutSwapBuffers();

    free(mesh.polygons);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("plane");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}