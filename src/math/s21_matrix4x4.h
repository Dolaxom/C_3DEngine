#include "../s21_engine.h"

typedef struct matrix_struct {
  float matrix[4][4];
} matrix4x4;

void s21_mult_matrix_on_vector(matrix4x4 *A, vector *B, vector *res);