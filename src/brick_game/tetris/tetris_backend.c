/************************************************************
 * @file tetris.c
 * @brief Game logic library source
 ************************************************************/

#include "tetris_backend.h"

/**
 * @brief Константный двойной массив с описанием фигур
 *
 * Для описания фигур используются 4 цифры,
 * соответствующие координатам заполненных ячеек одного тетрамино в поле 2х4.
 *
 * @example Для получения координаты x: 4 % 4 = 0
 *          Для получения координаты y: 4 / 4 = 1
 *          (x, y) => (0, 1)
 */
const int tetraminoes[FIGURES_COUNT][FIG_CEILS] = {
    {4, 6, 5, 7},  ///< I
    {0, 1, 5, 6},  ///< Z
    {2, 1, 5, 4},  ///< S
    {1, 5, 4, 6},  ///< T
    {2, 5, 4, 6},  ///< L
    {0, 5, 4, 6},  ///< J
    {1, 0, 4, 5}   ///< O
};

void init_params(Game_params_t *params, GameInfo_t *info, Figure_t *figure) {
  params->info = info;
  params->figure = figure;

  init_info(info);

  params->state = START_GAME;

  srand(time(NULL));
  params->figure->next_fig = get_tetramino(params->info->next);
}

void init_info(GameInfo_t *info) {
  info->field = get_array(FIELD_HEIGHT, FIELD_WIDTH);
  info->next = get_array(FIGURE_HEIGHT, FIGURE_WIDTH);
  info->score = 0;
  info->high_score = get_hiscore();
  info->level = 1;
  info->speed = 1;
  info->pause = 0;
}

int **get_array(int height, int width) {
  int **field = (int **)calloc(height, sizeof(int *));
  for (int i = 0; i < height; i++) field[i] = (int *)calloc(width, sizeof(int));

  return field;
}

int **free_array(int **arr, int height) {
  for (int i = 0; i < height; i++) free(arr[i]);

  free(arr);

  return NULL;
}

void free_params(Game_params_t *params) {
  params->info->field = free_array(params->info->field, FIELD_HEIGHT);
  params->info->next = free_array(params->info->next, FIGURE_HEIGHT);
}

void reset_info(GameInfo_t *info) {
  clear_field(info->field, FIELD_HEIGHT, FIELD_WIDTH);
  info->score = 0;
  info->level = 1;
  info->speed = 1;
}

Game_params_t *get_params(Game_params_t *params) {
  static Game_params_t *game_params;

  if (params != NULL) game_params = params;

  return game_params;
}

int get_hiscore() {
  int hiscore = 0;

  FILE *hiscore_file = fopen("./hiscore", "r");
  if (!hiscore_file) {
    hiscore_file = fopen("./hiscore", "w");
    fprintf(hiscore_file, "%d\n", hiscore);
  }
  fscanf(hiscore_file, "%d", &hiscore);

  fclose(hiscore_file);

  return hiscore;
}

void set_hiscore(int score) {
  FILE *hiscore_file = fopen("./hiscore", "w");
  fprintf(hiscore_file, "%d\n", score);

  fclose(hiscore_file);
}

void clear_field(int **field, int rows, int cols) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) field[i][j] = 0;
}

int get_tetramino(int **next) {
  int next_fig = rand() % FIGURES_COUNT;

  clear_field(next, FIGURE_HEIGHT, FIGURE_WIDTH);

  for (int i = 0; i < FIG_CEILS; i++) {
    int y = tetraminoes[next_fig][i] / 4;
    int x = tetraminoes[next_fig][i] % 4;

    next[y][x] = 1;
  }

  return next_fig;
}

void spawn_figure(Game_params_t *params) {
  params->figure->cur_fig = params->figure->next_fig;
  params->figure->next_fig = get_tetramino(params->info->next);

  for (int i = 0; i < FIG_CEILS; i++) {
    params->figure->ceils[i].x = tetraminoes[params->figure->cur_fig][i] % 4 +
                                 (FIELD_WIDTH - FIGURE_WIDTH) / 2;
    params->figure->ceils[i].y = tetraminoes[params->figure->cur_fig][i] / 4;
  }
  add_or_clear_figure(params, ADD);
}

bool check_gameover(GameInfo_t *info) {
  bool gameover = false;

  for (int i = 0; i < FIGURE_HEIGHT && !gameover; i++)
    for (int j = 0; j < FIELD_WIDTH && !gameover; j++) {
      if (info->field[i][j]) gameover = true;
    }

  return gameover;
}

void add_or_clear_figure(Game_params_t *params, int act) {
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = params->figure->ceils[i].x;
    int y = params->figure->ceils[i].y;

    params->info->field[y][x] = act;
  }
}

void move_left(Game_params_t *params) {
  add_or_clear_figure(params, CLEAR);
  Figure_t fig_after = *params->figure;

  for (int i = 0; i < FIG_CEILS; i++) fig_after.ceils[i].x--;

  if (!check_collision(params->info->field, &fig_after))
    *params->figure = fig_after;

  add_or_clear_figure(params, ADD);
}

void move_right(Game_params_t *params) {
  add_or_clear_figure(params, CLEAR);
  Figure_t fig_after = *params->figure;

  for (int i = 0; i < FIG_CEILS; i++) fig_after.ceils[i].x++;

  if (!check_collision(params->info->field, &fig_after))
    *params->figure = fig_after;

  add_or_clear_figure(params, ADD);
}

void move_down(Game_params_t *params) {
  add_or_clear_figure(params, CLEAR);

  while (!check_collision(params->info->field, params->figure))
    for (int i = 0; i < FIG_CEILS; i++) params->figure->ceils[i].y++;

  for (int i = 0; i < FIG_CEILS; i++) params->figure->ceils[i].y--;

  add_or_clear_figure(params, ADD);
}

void rotate_figure(Game_params_t *params) {
  add_or_clear_figure(params, CLEAR);
  Figure_t fig_after = *params->figure;

  Ceil_t center = fig_after.ceils[1];
  for (int i = 0; i < FIG_CEILS; i++) {
    int x = fig_after.ceils[i].y - center.y;
    int y = fig_after.ceils[i].x - center.x;

    fig_after.ceils[i].x = center.x - x;
    fig_after.ceils[i].y = center.y + y;
  }

  if (!check_collision(params->info->field, &fig_after))
    *params->figure = fig_after;

  add_or_clear_figure(params, ADD);
}

bool check_collision(int **field, Figure_t *figure) {
  bool check = false;

  for (int i = 0; i < FIG_CEILS && check == false; i++) {
    if (figure->ceils[i].x < 0 || figure->ceils[i].x > FIELD_WIDTH - 1)
      check = true;
    else if (figure->ceils[i].y < 0 || figure->ceils[i].y > FIELD_HEIGHT - 1)
      check = true;
    else if (field[figure->ceils[i].y][figure->ceils[i].x])
      check = true;
  }

  return check;
}

bool shift_figure(Game_params_t *params) {
  bool move_flag = true;
  add_or_clear_figure(params, CLEAR);

  for (int i = 0; i < FIG_CEILS; i++) {
    params->figure->ceils[i].y++;
  }

  if (check_collision(params->info->field, params->figure)) {
    for (int i = 0; i < FIG_CEILS; i++) {
      params->figure->ceils[i].y--;
    }
    move_flag = false;
  }
  add_or_clear_figure(params, ADD);

  return move_flag;
}

void attaching_process(GameInfo_t *info) {
  calculate_score(info);

  if (info->score > info->high_score) {
    info->high_score = info->score;
    set_hiscore(info->high_score);
  }

  set_lvl(info);

  info->speed = info->level;
}

void calculate_score(GameInfo_t *info) {
  int filled_lines = shift_filled_rows(info);

  if (filled_lines == 1)
    info->score += 100;
  else if (filled_lines == 2)
    info->score += 300;
  else if (filled_lines == 3)
    info->score += 700;
  else if (filled_lines == 4)
    info->score += 1500;
}

int shift_filled_rows(GameInfo_t *info) {
  int filled_rows = 0;

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    bool filled = true;

    while (filled) {
      int filled_ceils = 0;

      for (int j = 0; j < FIELD_WIDTH; j++) {
        if (info->field[i][j]) filled_ceils++;

        if (filled_ceils == FIELD_WIDTH) {
          filled_rows++;
          shift_field(info->field, i);
        } else
          filled = false;
      }
    }
  }

  return filled_rows;
}

void shift_field(int **field, int row) {
  for (int i = row; i > 0; i--)
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = field[i - 1][j];
    }
}

void set_lvl(GameInfo_t *info) {
  int lvl = info->score / SCORE_TO_NEXT_LVL + 1;

  if (lvl >= MAX_LVL)
    info->level = MAX_LVL;
  else
    info->level = lvl;
}

GameInfo_t updateCurrentState() {
  Game_params_t *params = get_params(NULL);

  return *params->info;
}

void pause_game(GameInfo_t *info) { info->pause = !info->pause; }