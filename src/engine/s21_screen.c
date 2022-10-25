#include "s21_screen.h"
#include <unistd.h>

int choice;

int main(int argc, char **argv) {
    scanf("%d", &choice);
    glutInit(&argc, argv);
    s21_setup_settings();
    glutDisplayFunc(display);
    
    glutMainLoop();

    free(main_mesh.polygons);
    return 0;
}

void display() {
    if (choice) {
        float new_transform;
        scanf("%f", &new_transform);
        if (new_transform == 999) {
            choice = 0;
        } else {
            move = s21_to_radians(new_transform);
        }
    } else {
        move += 0.01;
    }

    glutPostRedisplay();
    duplicate_mesh = mesh_copy(main_mesh);
    s21_test_transform(duplicate_mesh, move);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glBlendFunc(GL_ONE, GL_ZERO);
    // glEnable(GL_BLEND);

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Display all points and lines
    s21_render_tris(duplicate_mesh);

    glutSwapBuffers();
    free(duplicate_mesh.polygons);
    usleep(100);
    // exit(1);
}

void s21_render_tris(Mesh mesh) {
    for (int polygon = 0; polygon < mesh.count_polygons; polygon++) {
        glLineWidth(0.01);
        glBegin(GL_TRIANGLES);
        for (int point = 0; point < 3; point++) {
            glColor3f(1, 1, 1);
            glVertex3f(mesh.polygons[polygon].points[point].x, mesh.polygons[polygon].points[point].y, mesh.polygons[polygon].points[point].z);
        }
        glEnd();
    }
}

void s21_setup_settings() {
    main_mesh = mesh_main();
    // glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("3DViewer");
}

void s21_test_transform(Mesh mesh, float move) {
    vec3D size = {0.5, -0.5, 0.5};
    vec3D translate = {0.0, 0.0, -3.0};
    vec3D rotation = {0, move, 0};
    s21_rotation(&mesh, rotation);
    s21_translate(&mesh, translate);
    s21_projection(&mesh, 1.77777, s21_to_radians(18), 3000, 0.0);
    // s21_orthogonal(&mesh, 0, 1.28, 0, 0.72, 100, -0.1);
    s21_scale(&mesh, size);
}
