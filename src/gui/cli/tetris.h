#ifndef TETRIS_H
#define TETRIS_H

#define _XOPEN_SOURCE 600  // для видимости clock_gettime() и CLOCK_MONOTONIC

#include <time.h>

#include "../../brickGame_API.h"
#include "../../brick_game/tetris/tetris_backend.h"
#include "tetris_frontend.h"

#define GAME_INIT(time)   \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

void game_loop();
UserAction_t processing_input(int user_input, bool* hold);

#endif