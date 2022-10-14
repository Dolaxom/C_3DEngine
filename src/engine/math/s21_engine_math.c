#include "s21_engine_math.h"

float to_radians(float degree) {
    return degree * 3.141593 / 180;
}


int s21_calc_scale_matrix(vec3D *point, vec3D size_vector) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t scale_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_scale_matrix(size_vector, &scale_matrix4x4);

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&scale_matrix4x4, &vector, &mul_result);

  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  s21_remove_matrix(&vector);
  s21_remove_matrix(&scale_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_scale_matrix(vec3D size_vector, matrix_t *result) {
  s21_create_matrix(4, 4, result); 
  
  result->matrix[0][0] = size_vector.x;
  result->matrix[1][1] = size_vector.y;
  result->matrix[2][2] = size_vector.z;
  result->matrix[3][3] = 1;

  return OK;
}

int s21_scale(Mesh *mesh, vec3D size_vector) {
    for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
        for (int point = 0; point < 3; point++) {
            s21_calc_scale_matrix(&mesh->polygons[polygon].points[point], size_vector);
        }
    }

    return OK;
}


int s21_translate_matrix(vec3D position_vector, matrix_t *result) {
  s21_create_matrix(4, 4, result); 
  
  result->matrix[0][0] = 1;
  result->matrix[0][3] = position_vector.x;
  result->matrix[1][1] = 1;
  result->matrix[1][3] = position_vector.y;
  result->matrix[2][2] = 1;
  result->matrix[2][3] = position_vector.z;
  result->matrix[3][3] = 1;

  return OK;
}

int s21_calc_translate_matrix(vec3D *point, vec3D position_vector) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t scale_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_translate_matrix(position_vector, &scale_matrix4x4);

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&scale_matrix4x4, &vector, &mul_result);

  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  s21_remove_matrix(&vector);
  s21_remove_matrix(&scale_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_translate(Mesh *mesh, vec3D position_vector) {
    for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
        for (int point = 0; point < 3; point++) {
            s21_calc_translate_matrix(&mesh->polygons[polygon].points[point], position_vector);
        }
    }

    return OK;
}





int s21_rotation_matrix_y(float rot, matrix_t *result) {
  s21_create_matrix(4, 4, result);

  result->matrix[0][0] = cos(rot);
  result->matrix[0][2] = sin(rot);
  result->matrix[1][1] = 1;
  result->matrix[2][0] = -sin(rot);
  result->matrix[2][2] = cos(rot);
  result->matrix[3][3] = 1;

  return OK;
}

int s21_calc_rotation_matrix_y(vec3D *point, float rot) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t scale_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_rotation_matrix_y(rot, &scale_matrix4x4);

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&scale_matrix4x4, &vector, &mul_result);

  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  s21_remove_matrix(&vector);
  s21_remove_matrix(&scale_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_rotation_y(Mesh *mesh, float rot) {
    for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
        for (int point = 0; point < 3; point++) {
            s21_calc_rotation_matrix_y(&mesh->polygons[polygon].points[point], rot);
        }
    }

    return OK;
}


int s21_rotation_matrix_z(float rot, matrix_t *result) {
  s21_create_matrix(4, 4, result);

  result->matrix[0][0] = cos(rot);
  result->matrix[0][1] = -sin(rot);
  result->matrix[1][0] = sin(rot);
  result->matrix[1][1] = cos(rot);
  result->matrix[2][2] = 1;
  result->matrix[3][3] = 1;

  return OK;
}

int s21_calc_rotation_matrix_z(vec3D *point, float rot) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t scale_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_rotation_matrix_z(rot, &scale_matrix4x4);

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&scale_matrix4x4, &vector, &mul_result);

  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  s21_remove_matrix(&vector);
  s21_remove_matrix(&scale_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_rotation_z(Mesh *mesh, float rot) {
    for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
        for (int point = 0; point < 3; point++) {
            s21_calc_rotation_matrix_z(&mesh->polygons[polygon].points[point], rot);
        }
    }

    return OK;
}



int s21_rotation_matrix_x(float rot, matrix_t *result) {
  s21_create_matrix(4, 4, result);

  result->matrix[0][0] = 1;
  result->matrix[1][1] = cos(rot);
  result->matrix[1][2] = -sin(rot);
  result->matrix[2][1] = sin(rot);
  result->matrix[2][2] = cos(rot);
  result->matrix[3][3] = 1;

  return OK;
}

int s21_calc_rotation_matrix_x(vec3D *point, float rot) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t scale_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_rotation_matrix_x(rot, &scale_matrix4x4);

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&scale_matrix4x4, &vector, &mul_result);

  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  s21_remove_matrix(&vector);
  s21_remove_matrix(&scale_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_rotation_x(Mesh *mesh, float rot) {
  for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
      for (int point = 0; point < 3; point++) {
          s21_calc_rotation_matrix_x(&mesh->polygons[polygon].points[point], rot);
      }
  }

  return OK;
}


int s21_projection_matrix(float aspect, float fov, float far, float near, matrix_t *result) {
  s21_create_matrix(4, 4, result);

  result->matrix[0][0] = 1/(aspect * tan(fov));
  result->matrix[1][1] = 1/tan(fov);
  result->matrix[2][2] = far / (far - near);
  result->matrix[2][3] = -( (far * near) / (far - near) );
  result->matrix[3][2] = 1;

  return OK;
}


int s21_calc_projection_matrix(vec3D *point, float aspect, float fov, float far, float near) {
  matrix_t vector = {NULL, 0, 0};
  matrix_t projection_matrix4x4 = {NULL, 0, 0};
  matrix_t mul_result = {NULL, 0, 0};
  s21_create_matrix(4, 1, &vector);
  s21_projection_matrix(aspect, fov, far, near, &projection_matrix4x4);
  float old_z = point->z;

  vector.matrix[0][0] = point->x;
  vector.matrix[1][0] = point->y;
  vector.matrix[2][0] = point->z;
  vector.matrix[3][0] = 1;

  s21_mult_matrix(&projection_matrix4x4, &vector, &mul_result);


  point->x = mul_result.matrix[0][0];
  point->y = mul_result.matrix[1][0];
  point->z = mul_result.matrix[2][0];

  point->x = point->x / old_z;
  point->y = point->y / old_z;
  point->z = point->z / old_z;

  s21_remove_matrix(&vector);
  s21_remove_matrix(&projection_matrix4x4);
  s21_remove_matrix(&mul_result);

  return OK;
}

int s21_projection(Mesh *mesh, float aspect, float fov, float far, float near) {
  for (int polygon = 0; polygon < mesh->count_polygons; polygon++) {
      for (int point = 0; point < 3; point++) {
          s21_calc_projection_matrix(&mesh->polygons[polygon].points[point], aspect, fov, far, near);
      }
  }

  return OK;
}