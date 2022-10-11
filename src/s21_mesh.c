#include <GL/freeglut.h>
#include "s21_mesh.h"

Mesh plane() {
    Mesh plane;
    plane.polygons = malloc(2 * sizeof(plane));

    vec3D points[4] = { {-1, 0, 1}, {1, 0, 1}, {-1, 0, -1}, {1, 0, -1} };

    plane.polygons[0].points[0] = points[1];
    plane.polygons[0].points[1] = points[3];
    plane.polygons[0].points[2] = points[2];

    plane.polygons[1].points[0] = points[0];
    plane.polygons[1].points[1] = points[1];
    plane.polygons[1].points[2] = points[2];

    return plane;
}

void display() {
    Mesh aboba = plane();

    // printf("%f %f %f")

    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(10);
    //GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0, 0, 0);
        
        glVertex3f(aboba.polygons[0].points[0].x, aboba.polygons[0].points[0].y, aboba.polygons[0].points[0].z);
        glVertex3f(aboba.polygons[0].points[1].x, aboba.polygons[0].points[1].y, aboba.polygons[0].points[1].z);
        glVertex3f(aboba.polygons[0].points[2].x, aboba.polygons[0].points[2].y, aboba.polygons[0].points[2].z);

        glVertex3f(aboba.polygons[1].points[0].x, aboba.polygons[0].points[0].y, aboba.polygons[0].points[0].z);
        glVertex3f(aboba.polygons[1].points[1].x, aboba.polygons[0].points[1].y, aboba.polygons[0].points[1].z);
        glVertex3f(aboba.polygons[1].points[2].x, aboba.polygons[0].points[2].y, aboba.polygons[0].points[2].z);

        // glVertex3f(-0.5, 0.5, 0);

        // glVertex3f(0.5, 0.5, 0);

        // glVertex3f(-0.5, -0.5, 0);
        
        // glVertex3f(0.5, -0.5, 0);

    glEnd();


    glutSwapBuffers();
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
