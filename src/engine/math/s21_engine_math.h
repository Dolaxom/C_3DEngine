#include "s21_matrix_based.h"

float to_radians(float degree);

int s21_scale_matrix(vec3D size_vector, matrix_t *result);
int s21_calc_scale_matrix(vec3D *point, vec3D size_vector);
int s21_scale(Mesh *mesh, vec3D size_vector);

int s21_translate_matrix(vec3D position_vector, matrix_t *result);
int s21_calc_translate_matrix(vec3D *point, vec3D position_vector);
int s21_translate(Mesh *mesh, vec3D position_vector);

int s21_rotation_matrix_y(float rot, matrix_t *result);
int s21_calc_rotation_matrix_y(vec3D *point, float rot);
int s21_rotation_y(Mesh *mesh, float rot);

int s21_rotation_matrix_z(float rot, matrix_t *result);
int s21_calc_rotation_matrix_z(vec3D *point, float rot);
int s21_rotation_z(Mesh *mesh, float rot);

int s21_rotation_matrix_x(float rot, matrix_t *result);
int s21_calc_rotation_matrix_x(vec3D *point, float rot);
int s21_rotation_x(Mesh *mesh, float rot);

int s21_projection_matrix(float aspect, float fov, float far, float near, matrix_t *result);
int s21_calc_projection_matrix(vec3D *point, float aspect, float fov, float far, float near);
int s21_projection(Mesh *mesh, float aspect, float fov, float far, float near);