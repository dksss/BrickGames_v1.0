#include "tetris_tests.h"

START_TEST(fsm_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  bool hold = false;

  init_params(&params, &info, &figure);
  get_params(&params);

  ck_assert_int_eq(params.state, START_GAME);

  userInput(NO_INPUT, hold);
  ck_assert_int_eq(params.state, START_GAME);

  userInput(Start, hold);
  ck_assert_int_eq(params.state, SPAWN_FIG);

  UserAction_t action[] = {Left,   Left,   Right,  Right, Up,
                           Action, Action, Action, Action};

  for (int i = 0; i < 9; i++) {
    userInput(action[i], hold);
    ck_assert_int_eq(params.state, MOVING_FIG);
  }

  params.state = SHIFT_FIG;
  userInput(NO_INPUT, hold);
  ck_assert_int_eq(params.state, MOVING_FIG);

  userInput(Down, hold);
  ck_assert_int_eq(params.state, ATTACHING);

  userInput(NO_INPUT, hold);
  ck_assert_int_eq(params.state, SPAWN_FIG);

  info.field[1][1] = 1;
  userInput(Down, hold);
  ck_assert_int_eq(params.state, GAMEOVER);

  userInput(Terminate, hold);
  ck_assert_int_eq(params.state, EXIT_GAME);

  free_params(&params);
}
END_TEST

START_TEST(fsm_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  bool hold = false;

  init_params(&params, &info, &figure);
  get_params(&params);

  ck_assert_int_eq(params.state, START_GAME);

  userInput(NO_INPUT, hold);
  ck_assert_int_eq(params.state, START_GAME);

  userInput(Terminate, hold);
  ck_assert_int_eq(params.state, EXIT_GAME);

  free_params(&params);
}
END_TEST

START_TEST(fsm_test_3) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  bool hold = false;

  init_params(&params, &info, &figure);
  get_params(&params);

  ck_assert_int_eq(params.state, START_GAME);

  params.state = GAMEOVER;
  userInput(NO_INPUT, hold);
  ck_assert_int_eq(params.state, GAMEOVER);

  userInput(Start, hold);
  ck_assert_int_eq(params.state, SPAWN_FIG);

  free_params(&params);
}
END_TEST

Suite* fsm_test_suite() {
  Suite* fsm_test_suite = suite_create("\033[33mFSM_test\033[0m");

  TCase* fsm_tc = tcase_create("FSM_test");
  tcase_add_test(fsm_tc, fsm_test_1);
  tcase_add_test(fsm_tc, fsm_test_2);
  tcase_add_test(fsm_tc, fsm_test_3);
  suite_add_tcase(fsm_test_suite, fsm_tc);

  return fsm_test_suite;
}