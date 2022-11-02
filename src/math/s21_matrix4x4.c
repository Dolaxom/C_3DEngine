#include "s21_matrix4x4.h"

void s21_mult_matrix_on_vector(matrix4x4 *A, vector *B, vector *res) {
    res->x = A->matrix[0][0] * B->x + A->matrix[0][1] * B->y + A->matrix[0][2] * B->z + A->matrix[0][3] * B->w;
    res->y = A->matrix[1][0] * B->x + A->matrix[1][1] * B->y + A->matrix[1][2] * B->z + A->matrix[1][3] * B->w;
    res->z = A->matrix[2][0] * B->x + A->matrix[2][1] * B->y + A->matrix[2][2] * B->z + A->matrix[2][3] * B->w;
    res->w = A->matrix[3][0] * B->x + A->matrix[3][1] * B->y + A->matrix[3][2] * B->z + A->matrix[3][3] * B->w;
}