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
  matrix_t matrix_1;
  s21_create_matrix(4, 4, &matrix_1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_1.matrix[i][j] = real_matrix.matrix[i][j];
    }
  }
  double real_result;
  double expected_result = 0.125;
  s21_determinant(&matrix_1, &real_result);
  //;
  ck_assert_ldouble_eq_tol(real_result, expected_result, 1e-6);
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(rotation_y_matrix_reference) {}
END_TEST

//// SUITES

Suite *suite_core() {
  Suite *s = suite_create("suite_core");

  TCase *tc_1 = tcase_create("tc_degree_to_radian");
  TCase *tc_2 = tcase_create("tc_scale_matrix_reference");
  TCase *tc_3 = tcase_create("tc_rotation_y_matrix_reference");

  tcase_add_test(tc_1, degree_to_radian);
  tcase_add_test(tc_2, scale_matrix_reference);
  tcase_add_test(tc_3, rotation_y_matrix_reference);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);

  return s;
}

//// MAIN

int main() {
  printf("\n");

  Suite *s_core = suite_core();
  run_test(s_core);

  return 0;
}