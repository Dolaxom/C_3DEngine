#include "s21_world.h"

#include "math/s21_matrix4x4.h"
#include "s21_camera.h"

int main(int argc, char **argv) {
  vector test = {5, 2, 3, 4};
  matrix4x4 test_matrix = {
      {{2, 5, 3, 4}, {5, 3, 1, 2}, {1, 2, 6, 2}, {6, 2, 1, 5}}};

  vector result;
  s21_mult_matrix_on_vector(&test_matrix, &test, &result);
  printf("%f %f %f %f", result.x, result.y, result.z, result.w);

  return S21_OK;
}
