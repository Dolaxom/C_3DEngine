#include "s21_screen.h"

// int main() {
//     Mesh mesh = plane();
//     mesh.count_polygons = 2;
//     vec3D size = {0.5, 0.5, 0.5};
//     s21_scale(&mesh, size);
//     // s21_calc_scale_matrix(&mesh.polygons[0].points[0], size);

//     // printf("%f %f %f\n", mesh.polygons[0].points[0].x, mesh.polygons[0].points[0].y, mesh.polygons[0].points[0].z);
//     // printf("%f %f %f\n", mesh.polygons[0].points[1].x, mesh.polygons[0].points[1].y, mesh.polygons[0].points[1].z);
//     // printf("%f %f %f\n", mesh.polygons[0].points[2].x, mesh.polygons[0].points[2].y, mesh.polygons[0].points[2].z);
    

//     free(mesh.polygons);
// }


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
    vec3D size = {0.5, 0.5, 0.5};
    mesh.count_polygons = 2;
    s21_scale(&mesh, size);
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
