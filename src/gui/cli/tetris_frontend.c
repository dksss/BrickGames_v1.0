#include "tetris_frontend.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  for (int i = left_x + 1; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);

  MVADDCH(top_y, right_x, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);

  for (int i = left_x + 1; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);

  MVADDCH(bottom_y, right_x, ACS_LRCORNER);
}

void print_overlay() {
  print_rectangle(0, BOARD_HEIGHT, 0, BOARD_WIDTH);  // Game field
  print_rectangle(0, BOARD_HEIGHT, BOARD_WIDTH + 1,
                  BOARD_WIDTH + HUD_WIDTH + 1);  // HUD
}

void print_start_screen() {
  clear();
  print_overlay();

  MVPRINTW(BOARD_HEIGHT / 2, (BOARD_WIDTH - START_MESSAGE_LEN) / 2 + 1,
           START_MESSAGE);
}

void print_game(GameInfo_t info) {
  clear();
  print_overlay();
  print_stats(&info);
  print_game_field(&info);

  if (info.pause) MVPRINTW(16, BOARD_WIDTH + 6, "PAUSE");
}

void print_stats(GameInfo_t* info) {
  print_rectangle(1, 3, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);  // score
  print_rectangle(4, 6, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);  // hi score
  print_rectangle(7, 9, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);  // lvl
  print_rectangle(10, 14, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);  // next

  MVPRINTW(1, BOARD_WIDTH + 4, " Score ");
  MVPRINTW(2, BOARD_WIDTH + 3, "%d", info->score);

  MVPRINTW(4, BOARD_WIDTH + 4, " Hi score ");
  MVPRINTW(5, BOARD_WIDTH + 3, "%d", info->high_score);

  MVPRINTW(7, BOARD_WIDTH + 4, " Lvl ");
  MVPRINTW(8, BOARD_WIDTH + 3, "%d", info->level);

  if (info->next != NULL) {
    MVPRINTW(10, BOARD_WIDTH + 4, " Next ");
    print_next_figure(info);
  }
}

void print_next_figure(GameInfo_t* info) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if (info->next[i][j]) {
        MVADDCH(12 + i, BOARD_WIDTH + 6 + j * 2, ACS_CKBOARD);
        MVADDCH(12 + i, BOARD_WIDTH + 6 + j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

void print_game_field(GameInfo_t* info) {
  for (int i = 0; i < GAME_HEIGHT; i++) {
    for (int j = 0; j < GAME_WIDTH; j++) {
      if (info->field[i][j]) {
        MVADDCH(BOARD_BEGIN + i - 1, BOARD_BEGIN + j * 2, ACS_CKBOARD);
        MVADDCH(BOARD_BEGIN + i - 1, BOARD_BEGIN + j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

void print_banner(GameInfo_t* info) {
  clear();
  print_overlay();

  MVPRINTW(BOARD_HEIGHT / 3, (BOARD_WIDTH - GAMEOVER_MSG_LEN) / 2 + 1,
           GAMEOVER_MESSAGE);

  if (info->score == info->high_score)
    MVPRINTW(BOARD_HEIGHT / 2, (BOARD_WIDTH - HISCORE_LEN) / 2, HIGHSCORE_INFO);

  MVPRINTW(BOARD_HEIGHT / 2 + 1, (BOARD_WIDTH - SCORE_INFO_LEN) / 2, SCORE_INFO,
           info->score);

  MVPRINTW(BOARD_HEIGHT * 3 / 4, (BOARD_WIDTH - START_MESSAGE_LEN) / 2 + 1,
           START_MESSAGE);
}