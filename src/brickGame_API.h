#ifndef BRICKGAME_API_H
#define BRICKGAME_API_H

#include <stdbool.h>

/**
 * @brief Перечисление действий игрока
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief GameInfo_t - структура, с информацией о игре
 *
 * @param field Игровое поле
 * @param next Поле с показом следующей фигуры
 * @param score Набранные очки
 * @param high_score Рекорд в игре
 * @param level Уровень, max 10
 * @param speed Скорость, max 10
 * @param pause Пауза в игре
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Реализация конечного автомата на switch-кейсах для игры 'Tetris'.
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
void userInput(UserAction_t action, bool hold);

/**
 * @brief Функция updateCurrentState предназначена для получения данных для
 * отрисовки в интерфейсе.
 *
 * Она возвращает структуру, содержащую информацию о текущем состоянии игры.
 */
GameInfo_t updateCurrentState();

#endif