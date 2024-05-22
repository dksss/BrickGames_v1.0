#include "tetris.h"

int main() {
  GAME_INIT(50);
  print_overlay();
  game_loop();
  endwin();

  return 0;
}

void game_loop() {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  UserAction_t action = NO_INPUT;
  bool hold = false;

  init_params(&params, &info, &figure);
  get_params(&params);  // инициализируем костыль

  bool break_flag = true;

  struct timespec ticks_prev, ticks_past;
  clock_gettime(CLOCK_MONOTONIC, &ticks_prev);

  while (break_flag) {
    if (params.state == START_GAME)
      print_start_screen();
    else if (params.state == MOVING_FIG)
      print_game(updateCurrentState());
    else if (params.state == GAMEOVER)
      print_banner(&info);

    if (params.state == EXIT_GAME) {
      break_flag = false;
      free_params(&params);
    } else if (params.state != EXIT_GAME) {
      action = processing_input(GET_USER_INPUT, &hold);
      userInput(action, hold);
    }

    clock_gettime(CLOCK_MONOTONIC, &ticks_past);
    double timer = (ticks_past.tv_sec - ticks_prev.tv_sec) +
                   (ticks_past.tv_nsec - ticks_prev.tv_nsec) / 1000000000.0;

    if (timer >= 1.0 - info.speed * 0.07) {
      if (!info.pause && params.state != EXIT_GAME &&
          params.state != START_GAME && params.state != GAMEOVER)
        params.state = SHIFT_FIG;

      ticks_prev = ticks_past;
    }
  }
}

UserAction_t processing_input(int user_input, bool* hold) {
  *hold = false;
  UserAction_t action = NO_INPUT;

  switch (user_input) {
    case ENTER:
      action = Start;
      break;

    case ESC:
      action = Terminate;
      break;

    case 'r':
      action = Action;
      break;

    case SPACE:
      action = Pause;
      break;

    case KEY_UP:
      action = Up;
      break;

    case KEY_DOWN:
      action = Down;
      break;

    case KEY_LEFT:
      action = Left;
      break;

    case KEY_RIGHT:
      action = Right;
      break;

    default:
      break;
  }
  return action;
}