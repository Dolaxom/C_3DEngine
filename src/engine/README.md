# screen.c
## void render_tris(Mesh mesh)
We use **for** loop instead of:

    // first polygon
     glBegin(GL_TRIANGLES);
         glColor3f(0, 0, 0);
        
         glVertex3f(mesh.polygons[0].points[0].x, mesh.polygons[0].points[0].z, mesh.polygons[0].points[0].y);
         glVertex3f(mesh.polygons[0].points[1].x, mesh.polygons[0].points[1].z, mesh.polygons[0].points[1].y);
         glVertex3f(mesh.polygons[0].points[2].x, mesh.polygons[0].points[2].z, mesh.polygons[0].points[2].y);
     glEnd();

    // second polygon
     glBegin(GL_TRIANGLES);
         glVertex3f(mesh.polygons[1].points[0].x, mesh.polygons[1].points[0].z, mesh.polygons[1].points[0].y);
         glVertex3f(mesh.polygons[1].points[1].x, mesh.polygons[1].points[1].z, mesh.polygons[1].points[1].y);
         glVertex3f(mesh.polygons[1].points[2].x, mesh.polygons[1].points[2].z, mesh.polygons[1].points[2].y);
    glEnd();