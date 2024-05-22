#include "tetris_tests.h"

int main() {
  int failed_tests = 0;
  Suite *tetris_tests[] = {game_parameters_tests_suite(),
                           game_mechanics_tests_suite(), fsm_test_suite(),
                           NULL};

  for (int i = 0; tetris_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(tetris_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed_tests += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("\n=========== \033[31mFAILED\033[0m: %d =============\n\n",
         failed_tests);

  return failed_tests == 0 ? 0 : 1;
}
