#ifndef BRICK_GAME_TETRIS_TETRIS_H_
#define BRICK_GAME_TETRIS_TETRIS_H_

#include "cli_frontend.h"
#include "../../brick_game/tetris/fsm_logic.h"
#include "../../brick_game/tetris/tetris_backend.h"
#include <locale.h>
#include <stdlib.h>
#include <signal.h>


void userInput(user_action_t action, bool hold);

game_info_t updateCurrentState();

void game_loop();

#endif  // BRICK_GAME_TETRIS_TETRIS_H_
