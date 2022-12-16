#ifndef S21_MATRIX_S21_MATRIX_H
#define S21_MATRIX_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-07

enum { OK, MATRIX_ERROR, CALC_ERROR };

typedef struct lib_matrix_struct {
  double **matrix;
  int rows;
  int columns;
} lib_matrix_t;

// main
int s21_create_matrix(int rows, int columns, lib_matrix_t *result);
void s21_remove_matrix(lib_matrix_t *A);

int s21_eq_matrix(lib_matrix_t *A, lib_matrix_t *B);

int s21_sum_matrix(lib_matrix_t *A, lib_matrix_t *B, lib_matrix_t *result);
int s21_sub_matrix(lib_matrix_t *A, lib_matrix_t *B, lib_matrix_t *result);

int s21_mult_number(lib_matrix_t *A, double number, lib_matrix_t *result);
int s21_mult_matrix(lib_matrix_t *A, lib_matrix_t *B, lib_matrix_t *result);

int s21_transpose(lib_matrix_t *A, lib_matrix_t *result);

int s21_calc_complements(lib_matrix_t *A, lib_matrix_t *result);

int s21_determinant(lib_matrix_t *A, double *result);

int s21_inverse_matrix(lib_matrix_t *A, lib_matrix_t *result);

// helpers
int s21_init_matrix(int rows, int columns, lib_matrix_t *result);
// void s21_output_matrix(const lib_matrix_t result);
int s21_minor_element(lib_matrix_t *A, lib_matrix_t *result, int rows, int columns);
int s21_minor_matrix(lib_matrix_t *A, lib_matrix_t *result);
int s21_chess_sign_matrix(lib_matrix_t A, lib_matrix_t *result);
int s21_determinant_simple2x2(lib_matrix_t *A, double *result);
int s21_check_matrix(lib_matrix_t *A);

#endif  // S21_MATRIX_S21_MATRIX_H
