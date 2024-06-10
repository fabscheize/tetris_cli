#ifndef TETRIS_FSM_LOGIC_H_
#define TETRIS_FSM_LOGIC_H_

#include <ncurses.h>

#include "tetris_backend.h"
#include "tetris_defines.h"
#include "tetris_frontend.h"
#include "tetris_objects.h"

user_action_t get_signal(int user_input);

void moveup(figure_t *figure);

void movedown(figure_t *figure);

void moveleft(figure_t *figure);
void moveright(figure_t *figure);

void update_current_state(user_action_t action, game_info_t *game,
                          figure_t *figure);
void user_input(user_action_t action, game_info_t *game, figure_t *figure);

void handle_collision(game_info_t *game, figure_t *figure);

#endif  // TETRIS_FSM_LOGIC_H_
