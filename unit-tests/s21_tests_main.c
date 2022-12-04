#include "s21_tests.h"

//// TESTS

#include "../libs/matrix-lib/s21_matrix.h"
#include "../src/engine/math/s21_engine_math.h"
#include "../src/engine/math/s21_matrix4x4.h"
#include "../src/engine/s21_engine.h"
#include "../src/engine/s21_mesh.h"

START_TEST(degree_to_radian) {
  float real_result = s21_degree_to_radian(45.0f);
  float expected_result = 0.78539825;
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
}
END_TEST

START_TEST(scale_matrix_reference) {
  vector size = {0.5f, 0.5f, 0.5f, 1.0f};
  matrix4x4 real_matrix = s21_scale_matrix_reference(size);
  lib_matrix_t matrix_1;
  s21_create_matrix(4, 4, &matrix_1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = real_matrix.matrix[i][j];
    }
  }
  double real_result;
  double expected_result = 0.125;
  s21_determinant(&matrix_1, &real_result);
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(rotation_y_matrix_reference) {
  float angle = 45.0f;
  matrix4x4 real_matrix = s21_rotation_y_matrix_reference(angle);
  lib_matrix_t matrix_1;
  s21_create_matrix(4, 4, &matrix_1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = real_matrix.matrix[i][j];
    }
  }
  double real_result;
  double expected_result = 1.0;
  s21_determinant(&matrix_1, &real_result);
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(rotation_x_matrix_reference) {
  float angle = 45.0f;
  matrix4x4 real_matrix = s21_rotation_x_matrix_reference(angle);
  lib_matrix_t matrix_1;
  s21_create_matrix(4, 4, &matrix_1);
  printf("\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = real_matrix.matrix[i][j];
      printf("%f ", matrix_1.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  double real_result;
  double expected_result = 1.0;
  s21_determinant(&matrix_1, &real_result);
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(rotation_z_matrix_reference) {
  float angle = 45.0f;
  matrix4x4 real_matrix = s21_rotation_z_matrix_reference(angle);
  lib_matrix_t matrix_1;
  s21_create_matrix(4, 4, &matrix_1);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = real_matrix.matrix[i][j];
    }
  }
  double real_result;
  double expected_result = 1.0;
  s21_determinant(&matrix_1, &real_result);
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(mesh_init) {
  int failure = 0;
  int errcode = 0;
  mesh_t testmesh;

  testmesh = parse_obj_file("materials/raw/monkey.obj", &errcode);
  if (errcode != 0) {
    failure++;
  }
  testmesh = parse_obj_file("jdhzdsdfdff", &errcode);
  if (errcode == 0) {
    failure++;
  }

  if (failure > 0) {
    ck_abort();
  }
}

START_TEST(mesh_init_values) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);

  if (errcode == 0) {
    s21_scale(&testmesh, 1.0f, 1.0f, 1.0f);
    s21_rotate_x(&testmesh, 0.0f);
    s21_rotate_y(&testmesh, 0.0f);
    s21_rotate_z(&testmesh, 0.0f);

    ck_assert_double_eq_tol(testmesh.scale.x, 1.0f, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.y, 1.0f, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.z, 1.0f, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.x, 0.0f, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.y, 0.0f, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.z, 0.0f, 1e-6);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_rotation) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  float expected_x = 0.0f;
  float expected_y = 0.0f;
  float expected_z = 0.0f;
  float rot_x = 0.0f;
  float rot_y = 0.0f;
  float rot_z = 0.0f;

  if (errcode == 0) {
    s21_scale(&testmesh, 1.0f, 1.0f, 1.0f);
    s21_rotate_x(&testmesh, 0.0f);
    s21_rotate_y(&testmesh, 0.0f);
    s21_rotate_z(&testmesh, 0.0f);

    s21_rotate_x(&testmesh, s21_degree_to_radian(rot_x));
    s21_rotate_y(&testmesh, s21_degree_to_radian(rot_y));
    s21_rotate_z(&testmesh, s21_degree_to_radian(rot_z));

    ck_assert_double_eq_tol(testmesh.rotation.x, expected_x, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.y, expected_y, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.z, expected_z, 1e-6);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_scale) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  float expected_x = 0.0f;
  float expected_y = 0.0f;
  float expected_z = 0.0f;
  float scale_x = 0.0f;
  float scale_y = 0.0f;
  float scale_z = 0.0f;

  if (errcode == 0) {
    s21_scale(&testmesh, 1.0f, 1.0f, 1.0f);
    s21_rotate_x(&testmesh, 0.0f);
    s21_rotate_y(&testmesh, 0.0f);
    s21_rotate_z(&testmesh, 0.0f);

    s21_scale(&testmesh, 1, 1, 1);
    s21_scale(&testmesh, scale_x, scale_y, scale_z);

    ck_assert_double_eq_tol(testmesh.scale.x, expected_x, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.y, expected_y, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.z, expected_z, 1e-6);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_fastrotation) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  float expected_x = 0.0f;
  float expected_y = 0.0f;
  float expected_z = 0.0f;
  float rot_x = 0.0f;
  float rot_y = 0.0f;
  float rot_z = 0.0f;

  if (errcode == 0) {
    s21_fast_scale(&testmesh, 1.0f, 1.0f, 1.0f);
    s21_fast_rotate_x(&testmesh, 0.0f);
    s21_fast_rotate_y(&testmesh, 0.0f);
    s21_fast_rotate_z(&testmesh, 0.0f);

    s21_fast_rotate_x(&testmesh, s21_degree_to_radian(rot_x));
    s21_fast_rotate_y(&testmesh, s21_degree_to_radian(rot_y));
    s21_fast_rotate_z(&testmesh, s21_degree_to_radian(rot_z));

    ck_assert_double_eq_tol(testmesh.rotation.x, expected_x, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.y, expected_y, 1e-6);
    ck_assert_double_eq_tol(testmesh.rotation.z, expected_z, 1e-6);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_fastscale) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  float expected_x = 0.0f;
  float expected_y = 0.0f;
  float expected_z = 0.0f;
  float scale_x = 0.0f;
  float scale_y = 0.0f;
  float scale_z = 0.0f;

  if (errcode == 0) {
    s21_fast_scale(&testmesh, 1.0f, 1.0f, 1.0f);
    s21_fast_rotate_x(&testmesh, 0.0f);
    s21_fast_rotate_y(&testmesh, 0.0f);
    s21_fast_rotate_z(&testmesh, 0.0f);

    s21_fast_scale(&testmesh, 1, 1, 1);
    s21_fast_scale(&testmesh, scale_x, scale_y, scale_z);

    ck_assert_double_eq_tol(testmesh.scale.x, expected_x, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.y, expected_y, 1e-6);
    ck_assert_double_eq_tol(testmesh.scale.z, expected_z, 1e-6);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_polygons) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  int expected = 967;

  if (errcode == 0) {
    copy_polygons(testmesh);
    ck_assert_int_eq(testmesh.count_of_polygons, expected);
  } else {
    ck_abort();
  }
}
END_TEST

START_TEST(mesh_points) {
  int errcode = 0;
  char testpath[300] = "materials/raw/monkey.obj";
  mesh_t testmesh = parse_obj_file(testpath, &errcode);
  int expected = 507;

  if (errcode == 0) {
    copy_points(testmesh);
    ck_assert_int_eq(testmesh.count_of_points, expected);
  } else {
    ck_abort();
  }
}
END_TEST

//// SUITES

Suite *suite_core() {
  Suite *s = suite_create("suite_core");

  TCase *tc_1 = tcase_create("tc_degree_to_radian");
  TCase *tc_2 = tcase_create("tc_scale_matrix_reference");
  TCase *tc_3 = tcase_create("tc_rotation_y_matrix_reference");
  TCase *tc_4 = tcase_create("tc_rotation_x_matrix_reference");
  TCase *tc_5 = tcase_create("tc_rotation_z_matrix_reference");
  TCase *tc_6 = tcase_create("tc_mesh_init");
  TCase *tc_7 = tcase_create("tc_mesh_init_values");
  TCase *tc_8 = tcase_create("tc_mesh_rotation");
  TCase *tc_9 = tcase_create("tc_mesh_scale");
  TCase *tc_10 = tcase_create("tc_mesh_fastrotation");
  TCase *tc_11 = tcase_create("tc_mesh_fastscale");
  TCase *tc_12 = tcase_create("tc_mesh_polygons");
  TCase *tc_13 = tcase_create("tc_mesh_points");

  tcase_add_test(tc_1, degree_to_radian);
  tcase_add_test(tc_2, scale_matrix_reference);
  tcase_add_test(tc_3, rotation_y_matrix_reference);
  tcase_add_test(tc_4, rotation_x_matrix_reference);
  tcase_add_test(tc_5, rotation_z_matrix_reference);
  tcase_add_test(tc_6, mesh_init);
  tcase_add_test(tc_7, mesh_init_values);
  tcase_add_test(tc_8, mesh_rotation);
  tcase_add_test(tc_9, mesh_scale);
  tcase_add_test(tc_10, mesh_fastrotation);
  tcase_add_test(tc_11, mesh_fastscale);
  tcase_add_test(tc_12, mesh_polygons);
  tcase_add_test(tc_13, mesh_points);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);
  suite_add_tcase(s, tc_4);
  suite_add_tcase(s, tc_5);
  suite_add_tcase(s, tc_6);
  suite_add_tcase(s, tc_7);
  suite_add_tcase(s, tc_8);
  suite_add_tcase(s, tc_9);
  suite_add_tcase(s, tc_10);
  suite_add_tcase(s, tc_11);
  suite_add_tcase(s, tc_12);
  suite_add_tcase(s, tc_13);

  return s;
}

//// MAIN

int main() {
  printf("\n");

  Suite *s_core = suite_core();
  run_test(s_core);

  return 0;
}