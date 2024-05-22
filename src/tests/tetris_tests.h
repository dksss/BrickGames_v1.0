#ifndef TETRIS_TESTS_H
#define TETRIS_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../brickGame_API.h"
#include "../brick_game/tetris/tetris_backend.h"

Suite* game_parameters_tests_suite();
Suite* game_mechanics_tests_suite();
Suite* fsm_test_suite();

#endif