/************************************************************
 * @file tetris_fsm.c
 * @brief FSM logic library source
 ************************************************************/

#include "tetris_backend.h"

/**
 * @brief Реализация конечного автомата на switch-кейсах для игры 'Tetris'
 *
 * Switch-кейсы были использованы для наглядности работы КА.
 * Функция userInput() описывает логику переключения состояний.
 * Состояния проверяются в порядке, указанном в функции userInput().
 * Внутренние функции, основанные на switch-case ищут сигнал, полученный с
 * помощью функции processing_input(). Найдя его, КА совершает какое-то действие
 * и переключает состояние на следующее.
 *
 * @param action - вводимое пользователем действие, после обработки getch()
 * @param hold - параметр, который отвечает за зажатие клавиши (по
 * спецификации). Тк в данной реализации не используется, предусмотрена заглушка
 */
void userInput(UserAction_t action, bool hold) {
  if (hold) printf(" ");  // заглушка

  Game_params_t *params = get_params(NULL);

  switch (params->state) {
    case START_GAME:
      game_start_processing(action, &params->state);
      break;

    case SPAWN_FIG:
      if (!check_gameover(params->info)) {
        spawn_figure(params);
        params->state = MOVING_FIG;
      } else
        params->state = GAMEOVER;
      break;

    case MOVING_FIG:
      if (action == Terminate) params->state = EXIT_GAME;

      if (action == Pause) pause_game(params->info);

      if (!params->info->pause) figure_move_processing(action, params);
      break;

    case SHIFT_FIG:
      if (shift_figure(params))
        params->state = MOVING_FIG;
      else
        params->state = ATTACHING;
      break;

    case ATTACHING:
      attaching_process(params->info);
      params->state = SPAWN_FIG;
      break;

    case GAMEOVER:
      gameover_processing(action, params);
      break;

    default:
      break;
  }
}

void game_start_processing(UserAction_t action, Game_state *state) {
  switch (action) {
    case Start:
      *state = SPAWN_FIG;
      break;

    case Terminate:
      *state = EXIT_GAME;
      break;

    default:
      *state = START_GAME;
      break;
  }
}

void figure_move_processing(UserAction_t action, Game_params_t *params) {
  switch (action) {
    case Left:
      move_left(params);
      break;

    case Right:
      move_right(params);
      break;

    case Down:
      move_down(params);
      params->state = ATTACHING;
      break;

    case Action:
      rotate_figure(params);
      break;

    default:
      break;
  }
}

void gameover_processing(UserAction_t action, Game_params_t *params) {
  switch (action) {
    case Start:
      reset_info(params->info);
      params->state = SPAWN_FIG;
      break;

    case Terminate:
      params->state = EXIT_GAME;
      break;

    default:
      params->state = GAMEOVER;
      break;
  }
}