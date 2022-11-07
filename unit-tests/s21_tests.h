#ifndef UNIT_TESTS_S21_TESTS_H_
#define UNIT_TESTS_S21_TESTS_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/s21_calc.h"
#include "s21_testcases.h"

#define COLOR_RED "\x1B[31m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_MAGENTA "\x1B[35m"
#define COLOR_RESET "\x1B[0m"

#define NMAX_TEST 1000

void print_div(char chr);
void run_test(Suite *thesuit);

#endif  // UNIT_TESTS_S21_TESTS_H_
