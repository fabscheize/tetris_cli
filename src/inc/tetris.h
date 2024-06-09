#ifndef BRICK_GAME_TETRIS_TETRIS_H_
#define BRICK_GAME_TETRIS_TETRIS_H_

#include <signal.h>

#include "fsm_logic.h"

void userInput(user_action_t action, bool hold);

game_info_t updateCurrentState();

void game_loop();

#endif  // BRICK_GAME_TETRIS_TETRIS_H_
