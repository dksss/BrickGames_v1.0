#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <ncurses.h>

#include "../../brickGame_API.h"

#define BOARD_BEGIN 2

#define BOARD_HEIGHT 21  // 0--21 = 22
#define BOARD_WIDTH (10 * 2 + 2)

#define GAME_HEIGHT 20
#define GAME_WIDTH 10

#define HUD_WIDTH 15

#define START_MESSAGE "ENTER - Start!"
#define START_MESSAGE_LEN 14
#define GAMEOVER_MESSAGE "GAME OVER"
#define GAMEOVER_MSG_LEN 9
#define SCORE_INFO "YOUR SCORE: %d"
#define SCORE_INFO_LEN 13
#define HIGHSCORE_INFO "NEW HISCORE!!!"
#define HISCORE_LEN 14

#define MVADDCH(y, x, c) mvaddch(BOARD_BEGIN + (y), BOARD_BEGIN + (x), c)
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARD_BEGIN + (y), BOARD_BEGIN + (x), __VA_ARGS__)

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_overlay();

void print_start_screen();

void print_game(GameInfo_t info);
void print_stats(GameInfo_t* info);
void print_next_figure(GameInfo_t* info);
void print_game_field(GameInfo_t* info);

void print_banner(GameInfo_t* info);

#endif