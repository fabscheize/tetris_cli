#ifndef TETRIS_FSM_LOGIC_H_
#define TETRIS_FSM_LOGIC_H_

#include "tetris_backend.h"
#include "tetris_defines.h"
#include "tetris_frontend.h"
#include "tetris_objects.h"

void update_current_state(user_action_t action, game_info_t *game,
                          figure_t *figure);

user_action_t get_signal(int user_input);

void user_input(user_action_t action, game_info_t *game, figure_t *figure);

void game_tact(game_info_t *game, figure_t *figure);

#endif  // TETRIS_FSM_LOGIC_H_
