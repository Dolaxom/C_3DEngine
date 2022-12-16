#include "s21_tests.h"

void print_div(char chr) {
  for (int i = 0; i < 49; i++) {
    printf("%c", chr);
  }
  printf("\n");
}

void run_test(Suite *thesuit) {
  print_div('~');

  SRunner *therunner = srunner_create(thesuit);

  srunner_set_fork_status(therunner, CK_NOFORK);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_ntests_failed(therunner);
  srunner_free(therunner);

  print_div('.');
  printf("\n");
}
