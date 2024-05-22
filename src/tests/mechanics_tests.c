#include "tetris_tests.h"

extern const int tetraminoes[FIGURES_COUNT][FIG_CEILS];

START_TEST(get_tetramino_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);

  ck_assert_int_lt(figure.next_fig, 7);
  ck_assert_int_ge(figure.next_fig, 0);

  free_params(&params);
}
END_TEST

START_TEST(get_tetramino_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);

  ck_assert_int_lt(figure.next_fig, 7);
  ck_assert_int_ge(figure.next_fig, 0);

  int expected_cur_fig = figure.next_fig;

  spawn_figure(&params);

  ck_assert_int_eq(expected_cur_fig, figure.cur_fig);

  free_params(&params);
}
END_TEST

START_TEST(get_tetramino_test_3) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);

  ck_assert_int_lt(figure.next_fig, 7);
  ck_assert_int_ge(figure.next_fig, 0);

  int expected_cur_fig = figure.next_fig;

  spawn_figure(&params);

  ck_assert_int_eq(expected_cur_fig, figure.cur_fig);

  int** expected_next = get_array(FIGURE_HEIGHT, FIGURE_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int y = tetraminoes[figure.next_fig][i] / 4;
    int x = tetraminoes[figure.next_fig][i] % 4;

    expected_next[y][x] = 1;
  }

  for (int i = 0; i < FIGURE_HEIGHT; i++)
    for (int j = 0; j < FIGURE_WIDTH; j++)
      ck_assert_int_eq(info.next[i][j], expected_next[i][j]);

  expected_next = free_array(expected_next, FIGURE_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(spawn_figure_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  for (int i = 0; i < FIG_CEILS; i++) {
    ck_assert_int_eq(figure.ceils[i].x, expected_fig_ceils[i].x);
    ck_assert_int_eq(figure.ceils[i].y, expected_fig_ceils[i].y);
  }

  free_params(&params);
}
END_TEST

START_TEST(add_or_clear_figure_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(add_or_clear_figure_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);
  add_or_clear_figure(&params, CLEAR);

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_left_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x - 1;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  move_left(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_left_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x = tetraminoes[figure.cur_fig][i] % 4;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  for (int i = 0; i < FIELD_WIDTH - FIGURE_WIDTH; i++) move_left(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_right_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x + 1;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  move_right(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_right_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  figure.next_fig = 2;
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x = tetraminoes[figure.cur_fig][i] % 4 + 7;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  for (int i = 0; i < 10; i++) move_right(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_down_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y + (FIELD_HEIGHT - 2);

    expected_field[y][x] = 1;
  }

  move_down(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(move_down_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y + (FIELD_HEIGHT - 2);

    expected_field[y][x] = 1;
  }

  move_down(&params);
  move_down(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(rotate_figure_test) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4 + 1;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  shift_figure(&params);

  for (int i = 0; i < 4; i++) rotate_figure(&params);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  expected_field = free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(pause_game_test_1) {
  GameInfo_t info = {0};
  info.pause = 0;

  pause_game(&info);

  ck_assert_int_eq(info.pause, 1);
}
END_TEST

START_TEST(pause_game_test_2) {
  GameInfo_t info = {0};
  info.pause = 1;

  pause_game(&info);

  ck_assert_int_eq(info.pause, 0);
}
END_TEST

START_TEST(check_collision_test_1) {
  Figure_t true_figure = {0};
  true_figure.ceils[0].x = 1;
  true_figure.ceils[0].y = 1;
  true_figure.ceils[1].x = 2;
  true_figure.ceils[1].y = 1;
  true_figure.ceils[2].x = 3;
  true_figure.ceils[2].y = 1;
  true_figure.ceils[3].x = 4;
  true_figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  bool check = check_collision(field, &true_figure);
  ck_assert_int_eq(check, false);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_collision_test_2) {
  Figure_t figure = {0};
  figure.ceils[0].x = 1;
  figure.ceils[0].y = 1;
  figure.ceils[1].x = -2;
  figure.ceils[1].y = 1;
  figure.ceils[2].x = 3;
  figure.ceils[2].y = 1;
  figure.ceils[3].x = 4;
  figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  bool check = check_collision(field, &figure);
  ck_assert_int_eq(check, true);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_collision_test_3) {
  Figure_t figure = {0};
  figure.ceils[0].x = 1;
  figure.ceils[0].y = 1;
  figure.ceils[1].x = FIELD_WIDTH;
  figure.ceils[1].y = 1;
  figure.ceils[2].x = 3;
  figure.ceils[2].y = 1;
  figure.ceils[3].x = 4;
  figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  bool check = check_collision(field, &figure);
  ck_assert_int_eq(check, true);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_collision_test_4) {
  Figure_t figure = {0};
  figure.ceils[0].x = 1;
  figure.ceils[0].y = 1;
  figure.ceils[1].x = 2;
  figure.ceils[1].y = 1;
  figure.ceils[2].x = 3;
  figure.ceils[2].y = -1;
  figure.ceils[3].x = 4;
  figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  bool check = check_collision(field, &figure);
  ck_assert_int_eq(check, true);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_collision_test_5) {
  Figure_t figure = {0};
  figure.ceils[0].x = 1;
  figure.ceils[0].y = 1;
  figure.ceils[1].x = 2;
  figure.ceils[1].y = 1;
  figure.ceils[2].x = 3;
  figure.ceils[2].y = FIELD_HEIGHT;
  figure.ceils[3].x = 4;
  figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  bool check = check_collision(field, &figure);
  ck_assert_int_eq(check, true);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_collision_test_6) {
  Figure_t figure = {0};
  figure.ceils[0].x = 1;
  figure.ceils[0].y = 1;
  figure.ceils[1].x = 2;
  figure.ceils[1].y = 1;
  figure.ceils[2].x = 3;
  figure.ceils[2].y = 1;
  figure.ceils[3].x = 4;
  figure.ceils[3].y = 1;

  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  field[1][2] = 1;

  bool check = check_collision(field, &figure);
  ck_assert_int_eq(check, true);

  field = free_array(field, FIELD_HEIGHT);
}
END_TEST

START_TEST(check_gameover_test_1) {
  GameInfo_t info = {0};
  init_info(&info);

  bool check = check_gameover(&info);
  ck_assert_int_eq(check, false);

  free_array(info.field, FIELD_HEIGHT);
  free_array(info.next, FIGURE_HEIGHT);
}
END_TEST

START_TEST(check_gameover_test_2) {
  GameInfo_t info = {0};
  init_info(&info);

  info.field[1][1] = 1;

  bool check = check_gameover(&info);
  ck_assert_int_eq(check, true);

  free_array(info.field, FIELD_HEIGHT);
  free_array(info.next, FIGURE_HEIGHT);
}
END_TEST

START_TEST(set_lvl_test) {
  GameInfo_t info = {0};

  set_lvl(&info);
  ck_assert_int_eq(info.level, 1);

  info.score = 900;
  set_lvl(&info);
  ck_assert_int_eq(info.level, 2);

  info.score = 9000;
  set_lvl(&info);
  ck_assert_int_eq(info.level, 10);
}
END_TEST

START_TEST(shift_field_test) {
  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  int** field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  int row = 2;
  field[row][2] = 1;
  expected_field[row][2] = 0;
  expected_field[row + 1][2] = 0;

  shift_field(field, row);

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(field[i][j], expected_field[i][j]);

  field = free_array(field, FIELD_HEIGHT);
  expected_field = free_array(expected_field, FIELD_HEIGHT);
}
END_TEST

START_TEST(shift_filled_rows_test) {
  int expected_rows = 0, rows;
  GameInfo_t info = {0};
  info.field = get_array(FIELD_HEIGHT, FIELD_WIDTH);

  rows = shift_filled_rows(&info);
  ck_assert_int_eq(rows, expected_rows);

  for (int i = FIELD_HEIGHT - 2; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) info.field[i][j] = 1;

  rows = shift_filled_rows(&info);
  expected_rows = 2;
  ck_assert_int_eq(rows, expected_rows);

  free_array(info.field, FIELD_HEIGHT);
}
END_TEST

START_TEST(calculate_score_test) {
  GameInfo_t info = {0};
  init_info(&info);

  int score[4] = {100, 300, 700, 1500};
  int expected_score = 0;
  for (int i = 4; i != 0; i--) {
    for (int row = FIELD_HEIGHT - i; row < FIELD_HEIGHT; row++)
      for (int col = 0; col < FIELD_WIDTH; col++) info.field[row][col] = 1;

    calculate_score(&info);

    expected_score += score[i - 1];
    ck_assert_int_eq(info.score, expected_score);
  }
  info.field = free_array(info.field, FIELD_HEIGHT);
  info.next = free_array(info.next, FIGURE_HEIGHT);
}
END_TEST

START_TEST(attaching_process_test_1) {
  GameInfo_t info = {0};
  init_info(&info);

  for (int i = FIELD_HEIGHT - 4; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) info.field[i][j] = 1;

  attaching_process(&info);

  ck_assert_int_eq(info.score, 1500);
  ck_assert_int_eq(info.high_score, 1500);
  ck_assert_int_eq(info.level, 3);
  ck_assert_int_eq(info.speed, 3);

  free_array(info.field, FIELD_HEIGHT);
  free_array(info.next, FIGURE_HEIGHT);
}
END_TEST;

START_TEST(attaching_process_test_2) {
  GameInfo_t info = {0};
  init_info(&info);

  info.score = 1500;

  for (int i = FIELD_HEIGHT - 4; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) info.field[i][j] = 1;

  attaching_process(&info);

  ck_assert_int_eq(info.score, 3000);
  ck_assert_int_eq(info.high_score, 3000);
  ck_assert_int_eq(info.level, 6);
  ck_assert_int_eq(info.speed, 6);

  free_array(info.field, FIELD_HEIGHT);
  free_array(info.next, FIGURE_HEIGHT);
}
END_TEST;

START_TEST(shift_figure_test_1) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4 + 1;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  bool check = shift_figure(&params);
  bool expected_flag = true;

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  ck_assert_int_eq(check, expected_flag);

  free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

START_TEST(shift_figure_test_2) {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  init_params(&params, &info, &figure);
  spawn_figure(&params);

  Ceil_t expected_fig_ceils[4];
  for (int i = 0; i < FIG_CEILS; i++) {
    expected_fig_ceils[i].x =
        tetraminoes[figure.cur_fig][i] % 4 + (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    expected_fig_ceils[i].y = tetraminoes[figure.cur_fig][i] / 4;
  }

  int** expected_field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = expected_fig_ceils[i].x;
    int y = expected_fig_ceils[i].y;

    expected_field[y][x] = 1;
  }

  for (int i = 0; i < FIELD_WIDTH; i++) info.field[2][i] = 1;

  bool check = shift_figure(&params);
  bool expected_flag = false;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      ck_assert_int_eq(info.field[i][j], expected_field[i][j]);

  ck_assert_int_eq(check, expected_flag);

  free_array(expected_field, FIELD_HEIGHT);
  free_params(&params);
}
END_TEST

Suite* game_mechanics_tests_suite() {
  Suite* game_mechanics_suite =
      suite_create("\033[33mGame_mechanics_tests\033[0m");

  TCase* figure_logic_tests_tc = tcase_create("Figure_logic_tests");
  tcase_add_test(figure_logic_tests_tc, get_tetramino_test_1);
  tcase_add_test(figure_logic_tests_tc, get_tetramino_test_2);
  tcase_add_test(figure_logic_tests_tc, get_tetramino_test_3);
  tcase_add_test(figure_logic_tests_tc, spawn_figure_test_1);
  tcase_add_test(figure_logic_tests_tc, add_or_clear_figure_test_1);
  tcase_add_test(figure_logic_tests_tc, add_or_clear_figure_test_2);
  suite_add_tcase(game_mechanics_suite, figure_logic_tests_tc);

  TCase* figure_mechanic_tests_tc = tcase_create("Figure_mechanic_tests");
  tcase_add_test(figure_mechanic_tests_tc, move_left_test_1);
  tcase_add_test(figure_mechanic_tests_tc, move_left_test_2);
  tcase_add_test(figure_mechanic_tests_tc, move_right_test_1);
  tcase_add_test(figure_mechanic_tests_tc, move_right_test_2);
  tcase_add_test(figure_mechanic_tests_tc, move_down_test_1);
  tcase_add_test(figure_mechanic_tests_tc, move_down_test_2);
  tcase_add_test(figure_mechanic_tests_tc, rotate_figure_test);
  suite_add_tcase(game_mechanics_suite, figure_mechanic_tests_tc);

  TCase* game_logic_tests_tc = tcase_create("Game_logic_tests");
  tcase_add_test(game_logic_tests_tc, pause_game_test_1);
  tcase_add_test(game_logic_tests_tc, pause_game_test_2);
  tcase_add_test(game_logic_tests_tc, check_collision_test_1);
  tcase_add_test(game_logic_tests_tc, check_collision_test_2);
  tcase_add_test(game_logic_tests_tc, check_collision_test_3);
  tcase_add_test(game_logic_tests_tc, check_collision_test_4);
  tcase_add_test(game_logic_tests_tc, check_collision_test_5);
  tcase_add_test(game_logic_tests_tc, check_collision_test_6);
  tcase_add_test(game_logic_tests_tc, check_gameover_test_1);
  tcase_add_test(game_logic_tests_tc, check_gameover_test_2);
  tcase_add_test(game_logic_tests_tc, set_lvl_test);
  tcase_add_test(game_logic_tests_tc, shift_field_test);
  tcase_add_test(game_logic_tests_tc, shift_filled_rows_test);
  tcase_add_test(game_logic_tests_tc, calculate_score_test);
  tcase_add_test(game_logic_tests_tc, attaching_process_test_1);
  tcase_add_test(game_logic_tests_tc, attaching_process_test_2);
  tcase_add_test(game_logic_tests_tc, shift_figure_test_1);
  tcase_add_test(game_logic_tests_tc, shift_figure_test_2);
  suite_add_tcase(game_mechanics_suite, game_logic_tests_tc);

  return game_mechanics_suite;
}
