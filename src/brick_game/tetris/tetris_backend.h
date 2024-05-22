#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

/************************************************************
 * @file tetris.h
 * @brief Game logic library header
 ************************************************************/

#include <ncurses.h>  // Для стрелок
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../brickGame_API.h"

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10

#define FIGURES_COUNT 7
#define FIG_CEILS 4
#define FIGURE_HEIGHT 2
#define FIGURE_WIDTH 4

#define SCORE_TO_NEXT_LVL 600
#define MAX_LVL 10

#define GET_USER_INPUT getch()
#define ENTER 10
#define ESC 27
#define SPACE ' '
#define NO_INPUT -1

#define ADD 1
#define CLEAR 0

/**
 * Перечисление состояний КА
 */
typedef enum {
  START_GAME,
  SPAWN_FIG,
  MOVING_FIG,
  SHIFT_FIG,
  ATTACHING,
  GAMEOVER,
  EXIT_GAME
} Game_state;

/**
 * @brief Ceil_t - структура ячейки тетрамино
 *
 * Включает поля x и y. Отображет ячейку по заданным координатам x и y.
 */
typedef struct {
  int x, y;
} Ceil_t;

/**
 * @brief Figure_t - структура фигуры
 *
 * cur_fig - текущая фигура
 * next_fig - фигура, которая появится после текущей
 * ceils - четыре ячейки тетрамино
 */
typedef struct {
  int cur_fig;
  int next_fig;
  Ceil_t ceils[4];
} Figure_t;

/**
 * @brief Game_params_t - структура игровых параметров
 *
 * info - структура с информацией о поле, набранных очках и тд.
 * figure - структура с информацией о фигуре
 * state - состояние КА
 */
typedef struct {
  GameInfo_t* info;
  Figure_t* figure;
  Game_state state;
} Game_params_t;

/**
 * @brief game_start_processing() - процедура для обработки ввода пользователя
 * при старте игры
 */
void game_start_processing(UserAction_t action, Game_state* state);

/**
 * @brief figure_move_processing() - процедура для обработки ввода пользователя
 * при движении фигуры
 */
void figure_move_processing(UserAction_t action, Game_params_t* params);

/**
 * @brief gameover_processing() - процедура для обработки ввода пользователя при
 * gameover'e
 */
void gameover_processing(UserAction_t action, Game_params_t* params);

/**
 * @brief Функция init_params() инициализирует структуру Game_params_t
 *
 * Функция init_params() инициализирует структуру Game_params_t,
 * принимая в качестве параметров указатель на переменную params,
 * которую нужно инициализировать и дополнительные указатели-параметры,
 * являющимися ее составными частями.
 */
void init_params(Game_params_t* params, GameInfo_t* info, Figure_t* figure);

/**
 * @brief Функция init_info() инициализирует структуру GameInfo_t
 */
void init_info(GameInfo_t* info);

/**
 * @brief Процедура освобождения выделенной памяти для структуры Game_params_t
 */
void free_params(Game_params_t* params);

/**
 * @brief Функция обнуления для новой игры
 *
 * Функция reset_info() "обнуляет" нужные параметры,
 * для начала новой игры, без необходимости
 * перезапускать исполняемый файл
 */
void reset_info(GameInfo_t* info);

/**
 * @brief Процедура очистки поля (все поле заполняется "0")
 */
void clear_field(int** field, int rows, int cols);

/**
 * @brief Функция получения динамического массива заданных размеров
 */
int** get_array(int height, int width);

/**
 * @brief Функция для освобождения выделенной для двойного массива памяти
 */
int** free_array(int** arr, int height);

/**
 * @brief Функция get_params() - костыль, нужный для выполнения проекта согласно
 * спецификации
 */
Game_params_t* get_params(Game_params_t* params);

/**
 * @brief Функция для получения рекорда в игре. В случае если файла с рекордом
 * нет, создает его
 */
int get_hiscore();

/**
 * @brief Процедура записи рекорда в игре в файл
 */
void set_hiscore(int score);

/**
 * @brief get_tetramino() - функция получения фигуры
 *
 * @param next - поле отобржения следующей фигуры
 * @return Функция возвращает индекс фигуры, которая заспавнется после текущей
 * фигуры
 */
int get_tetramino(int** next);

/**
 * @brief Процедура спавна новой фигуры на игровое поле
 */
void spawn_figure(Game_params_t* params);

/**
 * @brief Процедура для добавления или удаления текущей
 * фигуры на заданном поле
 *
 * @param act - действие, которое необходимо совершить с фигурой
 * @example CLEAR зануляет координаты фигуры на поле
 * @example ADD ставит "1" на игровом поле, в координатах текущей фигуры для ее
 * отображения
 */
void add_or_clear_figure(Game_params_t* params, int act);

/**
 * @brief Процедура движения фигуры влево на игровом поле
 */
void move_left(Game_params_t* params);

/**
 * @brief Процедура движения фигуры вправо на игровом поле
 */
void move_right(Game_params_t* params);

/**
 * @brief Процедура движения фигуры вниз на игровом поле
 */
void move_down(Game_params_t* params);

/**
 * @brief Процедура для вращения фигур на поле
 *
 * Новое состояние фигуры вычисляется через уравнение:
 * X = x_0 + (x - x_0) * cos(90) - (y - y_0) * sin(90)
 * Y = y_0 + (y − y_0) * cos⁡(90) + (x − x_0 ) * sin⁡(90);
 *
 * x,y - исходные координаты каждой ячейки
 * X,Y - координаты после вращения
 * x_0, y_0 - координаты центра вращения
 * В качестве центров вращения выбраны координаты вторых ячеек всех фигур
 * (ДА, КВАДРАТ ТОЖЕ ВРАЩАЕТСЯ)
 */
void rotate_figure(Game_params_t* params);

/**
 * @brief Процедура паузы игры (Движение останавливается)
 */
void pause_game(GameInfo_t* info);

/**
 * @brief Функция проверки коллизии фигур.
 *
 * Если фигура не выходит за пределы поля по Х и У или ячейка на поле пуста,
 * то возвращается false.
 */
bool check_collision(int** field, Figure_t* figure);

/**
 * @brief check_gameover() - функция, проверяющая gameover
 *
 * Данная функция проверяет две верхние строки по всей ширине и
 * если они пусты, то спавнится новая фигура,
 * в противном случае игра оканчивается
 */
bool check_gameover(GameInfo_t* info);

/**
 * @brief Процедура, которая вызывается при коллизии фигуры и удаляет
 * заполненнные линии на поле, считает набранные очки и тд.
 */
void attaching_process(GameInfo_t* info);

/**
 * @brief Функция, которая смещает фигурку вниз по тику таймера
 *
 * Возвращает флаг, который говорит о том, может ли фигура двигаться вниз
 * или произошла коллизия.
 */
bool shift_figure(Game_params_t* params);

/**
 * @brief Процедура смещения игрового поля на 1 вниз по Y
 */
void shift_field(int** field, int row);

/**
 * @brief Функция удаления заполненных линий поля
 *
 * @return Возвращает количество удаленных линий для дальнейшего подсчета очков
 * в игре
 */
int shift_filled_rows(GameInfo_t* info);

/**
 * @brief Процедура подсчета очков в игре
 */
void calculate_score(GameInfo_t* info);

/**
 * @brief Процедура установки уровня сложности в игре
 */
void set_lvl(GameInfo_t* info);

#endif