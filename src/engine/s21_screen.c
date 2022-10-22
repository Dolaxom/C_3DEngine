#include "s21_screen.h"
#include <unistd.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    s21_setup_settings();
    glutDisplayFunc(display);
    
    glutMainLoop();

    return 0;
}

void display() {
    mesh = mesh_main();
    // mesh.count_polygons = 20;
    
    move += 0.01;
    usleep(1000);
    s21_mesh_info(mesh);
    // vec3D size = {0.5, 0.5, 0.5};
    // s21_scale(&mesh, size);
    s21_test_transform(mesh, move);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO);
    glEnable(GL_BLEND);

    // Smooth lines
    // glEnable(GL_LINE_SMOOTH);               
    // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Display all points and lines
    s21_render_tris(mesh);

    glutSwapBuffers();
    glutPostRedisplay();
    free(mesh.polygons);
}

void s21_render_tris(Mesh mesh) {
    for (int polygon = 0; polygon < mesh.count_polygons; polygon++) {
        glLineWidth(0.01);
        glBegin(GL_TRIANGLES);
        for (int point = 0; point < 3; point++) {
            glColor3f(1, 1, 1);
            glVertex3f(mesh.polygons[polygon].points[point].x, mesh.polygons[polygon].points[point].y, mesh.polygons[polygon].points[point].z);
            printf("polygon%d point%d.x = %f\n", polygon, point, mesh.polygons[polygon].points[point].x);
            printf("polygon%d point%d.y = %f\n", polygon, point, mesh.polygons[polygon].points[point].y);
            printf("polygon%d point%d.z = %f\n", polygon, point, mesh.polygons[polygon].points[point].z);
        }
        glEnd();
        printf("\n");
    }
}

void s21_setup_settings() {
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("3DViewer");
}

void s21_test_transform(Mesh mesh, float move) {
    vec3D size = {1, -1, 1};
    vec3D translate = {0.0, 0.0, -5.0};
    s21_rotation_x(&mesh, move);
    s21_rotation_y(&mesh, move);
    s21_translate(&mesh, translate);
    s21_rotation_z(&mesh, move);
    s21_projection(&mesh, 1.77777, s21_to_radians(25), 3000, 0.0);
    s21_scale(&mesh, size);
}
