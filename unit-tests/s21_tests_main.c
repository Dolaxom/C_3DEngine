#include "s21_tests.h"

//// TESTS

START_TEST(test_err) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_ERR;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_ERR; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    printf("error code: [%d] | error test result: ", errcode);
    if (errcode != OK) {
      printf(COLOR_GREEN "OK\n" COLOR_RESET);
    } else {
      printf(COLOR_RED "FAIL\n" COLOR_RESET);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_unary) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_UNARY;
  static double answers[] = ANSW_UNARY;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_UNARY; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_addsub) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_ADDSUB;
  static double answers[] = ANSW_ADDSUB;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_ADDSUB; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_mult) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_MULT;
  static double answers[] = ANSW_MULT;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_MULT; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}

START_TEST(test_div) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_DIV;
  static double answers[] = ANSW_DIV;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_DIV; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_pow) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_POW;
  static double answers[] = ANSW_POW;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_POW; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_mod) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_MOD;
  static double answers[] = ANSW_MOD;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_MOD; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_functs) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_FUNCTS;
  static double answers[] = ANSW_FUNCTS;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_FUNCTS; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_var_1) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_VAR_1;
  static double answers[] = ANSW_VAR_1;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_VAR_1; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_var_2) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;

  static char testcases[][NMAX_TEST] = CASE_VAR_2;
  static double answers[] = ANSW_VAR_2;

  printf("\n");

  for (int i = 0; i < NUM_VAR_2; i++) {
    printf("input: \"%s\" \n", testcases[i]);
    errcode = process_input(testcases[i], &head_nums, &head_ops, NULL, FALSE);

    if (s_get_size(head_nums) == 1 && s_get_size(head_ops) == 0) {
      double result = 0;
      convert_str_to_double(head_nums->value, &result);

      printf("s21 = %lf | answ = %lf | result: ", result, answers[i]);
      if (result == answers[i] && errcode == OK) {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      } else if (errcode != OK) {
        printf(COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
        failure++;
      } else {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
        failure++;
      }
    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

START_TEST(test_graphs) {
  int failure = 0;
  int errcode = OK;
  node_t *head_nums = NULL;
  node_t *head_ops = NULL;
  graph_t graph = init_graph();

  static char testcases[][NMAX_TEST] = CASE_GRAPHS;
  static double answers[] = ANSW_GRAPHS;

  print_div('~');
  printf("\n");

  for (int i = 0; i < NUM_GRAPHS; i++) {
    printf("input: \"%s\" \n", testcases[i]);

    size_t result_size = 20;
    errcode = update_graph(&graph, NMIN_GRAPH, NMAX_GRAPH, NMIN_GRAPH,
                           NMAX_GRAPH, N_STEP);
    errcode = calculate_graph(testcases[i], &head_nums, &head_ops, &graph);

    if (s_get_size(head_ops) == 0 && errcode == OK) {
      printf(
          "domain = -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10\n");
      printf("codomain = ");

      for (size_t j = 0; j < result_size && failure == 0; j++) {
        if (graph.codomain[j] == answers[j]) {
          printf("%lf ", graph.codomain[j]);
        } else {
          failure++;
        }
      }

      printf("\nresult: ");
      if (failure > 0) {
        printf(COLOR_RED "FAIL\n" COLOR_RESET);
      } else {
        printf(COLOR_GREEN "OK\n" COLOR_RESET);
      }

    } else {
      printf("result:" COLOR_MAGENTA "ERROR [%d]\n" COLOR_RESET, errcode);
      failure++;
    }

    s_destroy_all(&head_nums);
    s_destroy_all(&head_ops);
    free_graph(&graph);
    printf("\n");
  }

  print_div('.');

  s_destroy_all(&head_nums);
  s_destroy_all(&head_ops);

  if (failure > 0) {
    ck_abort();
  }
}
END_TEST

//// SUITES

Suite *suite_err() {
  Suite *s = suite_create("suite_err");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_err);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_unary() {
  Suite *s = suite_create("suite_unary");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_unary);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_addsub() {
  Suite *s = suite_create("suite_addsub");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_addsub);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_mult() {
  Suite *s = suite_create("suite_mult");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_mult);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_div() {
  Suite *s = suite_create("suite_div");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_div);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_pow() {
  Suite *s = suite_create("suite_pow");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_pow);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_mod() {
  Suite *s = suite_create("suite_mod");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_mod);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_functs() {
  Suite *s = suite_create("suite_functs");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_functs);

  suite_add_tcase(s, tc);

  return s;
}

Suite *suite_var() {
  Suite *s = suite_create("suite_var");

  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");

  tcase_add_test(tc_1, test_var_1);
  tcase_add_test(tc_2, test_var_2);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);

  return s;
}

Suite *suite_graphs() {
  Suite *s = suite_create("suite_graphs");

  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_graphs);

  suite_add_tcase(s, tc);

  return s;
}

//// MAIN

int main() {
  printf("\n");

  Suite *s_err = suite_err();
  Suite *s_unary = suite_unary();
  Suite *s_addsub = suite_addsub();
  Suite *s_mult = suite_mult();
  Suite *s_div = suite_div();
  Suite *s_pow = suite_pow();
  Suite *s_mod = suite_mod();
  Suite *s_functs = suite_functs();
  Suite *s_var = suite_var();
  Suite *s_graphs = suite_graphs();

  run_test(s_err);
  run_test(s_unary);
  run_test(s_addsub);
  run_test(s_mult);
  run_test(s_div);
  run_test(s_pow);
  run_test(s_mod);
  run_test(s_functs);
  run_test(s_var);
  run_test(s_graphs);

  return 0;
}