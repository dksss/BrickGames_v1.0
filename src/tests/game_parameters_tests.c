#include "tetris_tests.h"

START_TEST(init_info_test_1) {
  GameInfo_t info = {0};

  init_info(&info);

  ck_assert_ptr_nonnull(&info.field);
  ck_assert_ptr_nonnull(&info.next);
  ck_assert_int_eq(info.score, 0);
  ck_assert_int_ge(info.high_score, 0);
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.speed, 1);
  ck_assert_int_eq(info.pause, 0);

  info.field = free_array(info.field, FIELD_HEIGHT);
  info.next = free_array(info.next, FIGURE_HEIGHT);
}
END_TEST

START_TEST(init_params_test_1) {
  Game_params_t params = {0};
  GameInfo_t info = {0};
  Figure_t figure = {0};

  init_params(&params, &info, &figure);

  ck_assert_ptr_nonnull(&params.info);
  ck_assert_ptr_nonnull(&params.figure);
  ck_assert_int_eq(params.state, START_GAME);
  ck_assert_int_ge(params.figure->next_fig, 0);
  ck_assert_int_le(params.figure->next_fig, 6);
  ck_assert_int_ge(params.figure->cur_fig, 0);
  ck_assert_int_le(params.figure->cur_fig, 6);

  free_params(&params);
}
END_TEST

START_TEST(get_array_test_1) {
  int** field = NULL;
  int height = 5, width = 5;

  field = get_array(height, width);

  ck_assert_ptr_nonnull(field);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) ck_assert_int_eq(field[i][j], 0);

  field = free_array(field, height);
}
END_TEST

START_TEST(get_params_test_1) {
  Game_params_t params = {0};
  GameInfo_t info = {0};
  Figure_t figure = {0};

  init_params(&params, &info, &figure);

  Game_params_t* new_params = NULL;
  new_params = get_params(&params);

  ck_assert_ptr_nonnull(new_params);

  free_params(&params);
}
END_TEST

START_TEST(get_params_test_2) {
  Game_params_t params = {0};
  GameInfo_t info = {0};
  Figure_t figure = {0};

  init_params(&params, &info, &figure);
  get_params(&params);

  Game_params_t* new_params = NULL;
  new_params = get_params(NULL);

  ck_assert_ptr_nonnull(new_params);
  ck_assert_int_eq(new_params == &params, 1);

  free_params(&params);
}
END_TEST

START_TEST(free_array_test) {
  int** field = NULL;
  int height = 5, width = 5;

  field = get_array(height, width);
  field = free_array(field, height);

  ck_assert_ptr_null(field);
}
END_TEST

START_TEST(free_params_test_1) {
  Game_params_t params = {0};
  GameInfo_t info = {0};
  Figure_t figure = {0};

  init_params(&params, &info, &figure);
  free_params(&params);

  ck_assert_ptr_null(params.info->next);
}
END_TEST

START_TEST(reset_info_test_1) {
  GameInfo_t info = {0};
  init_info(&info);

  info.field[0][0] = 1;
  info.field[3][1] = 1;
  info.field[15][5] = 1;
  info.field[19][5] = 1;

  info.score = 777;
  info.level = 5;
  info.speed = 10;

  reset_info(&info);

  ck_assert_int_eq(info.score, 0);
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.speed, 1);
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) ck_assert_int_eq(info.field[i][j], 0);

  info.field = free_array(info.field, FIELD_HEIGHT);
  info.next = free_array(info.next, FIGURE_HEIGHT);
}
END_TEST

START_TEST(clear_field_test_1) {
  GameInfo_t info = {0};
  info.field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  info.field[0][0] = 1;
  info.field[3][1] = 1;
  info.field[15][5] = 1;
  info.field[18][5] = 1;

  clear_field(info.field, FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) ck_assert_int_eq(info.field[i][j], 0);

  info.field = free_array(info.field, FIELD_HEIGHT);
}
END_TEST

START_TEST(get_hiscore_test_1) {
  int hiscore = 50;

  hiscore = get_hiscore();

  ck_assert_int_eq(hiscore, 0);
}
END_TEST

START_TEST(get_hiscore_test_2) {
  int hiscore = 0, expected_hiscore = 1500;
  set_hiscore(1500);

  hiscore = get_hiscore();

  ck_assert_int_eq(hiscore, expected_hiscore);
}
END_TEST

START_TEST(set_hiscore_test_1) {
  int expected_hiscore = 1500;
  int hiscore = get_hiscore();

  ck_assert_int_eq(hiscore, expected_hiscore);
}
END_TEST

START_TEST(updateCurrentState_test) {
  Game_params_t params;
  GameInfo_t info;
  Figure_t fig;

  init_params(&params, &info, &fig);
  get_params(&params);

  GameInfo_t check_info = updateCurrentState();

  ck_assert_int_eq(info.high_score, check_info.high_score);
  ck_assert_int_eq(info.score, check_info.score);
  ck_assert_int_eq(info.speed, check_info.speed);
  ck_assert_int_eq(info.level, check_info.level);
  ck_assert_int_eq(info.pause, check_info.pause);

  free_params(&params);
}
END_TEST

Suite* game_parameters_tests_suite() {
  Suite* game_parameters_tests_suite =
      suite_create("\033[33mGame_parameters_tests\033[0m");

  TCase* init_tests_tc = tcase_create("Init_tests");
  tcase_add_test(init_tests_tc, init_info_test_1);
  tcase_add_test(init_tests_tc, init_params_test_1);
  tcase_add_test(init_tests_tc, get_array_test_1);
  tcase_add_test(init_tests_tc, get_params_test_1);
  tcase_add_test(init_tests_tc, get_params_test_2);
  suite_add_tcase(game_parameters_tests_suite, init_tests_tc);

  TCase* free_tests_tc = tcase_create("Free_tests_tc");
  tcase_add_test(free_tests_tc, free_array_test);
  tcase_add_test(free_tests_tc, free_params_test_1);
  suite_add_tcase(game_parameters_tests_suite, free_tests_tc);

  TCase* reset_tests_tc = tcase_create("Tests_for_resets");
  tcase_add_test(free_tests_tc, reset_info_test_1);
  tcase_add_test(free_tests_tc, clear_field_test_1);
  suite_add_tcase(game_parameters_tests_suite, reset_tests_tc);

  TCase* hiscore_tests_tc = tcase_create("High_score_tests");
  tcase_add_test(hiscore_tests_tc, get_hiscore_test_1);
  tcase_add_test(hiscore_tests_tc, get_hiscore_test_2);
  tcase_add_test(hiscore_tests_tc, set_hiscore_test_1);
  suite_add_tcase(game_parameters_tests_suite, hiscore_tests_tc);

  TCase* updateCurrentState_tc = tcase_create("Test_for_updateCurrentState");
  tcase_add_test(updateCurrentState_tc, updateCurrentState_test);
  suite_add_tcase(game_parameters_tests_suite, updateCurrentState_tc);

  return game_parameters_tests_suite;
}
