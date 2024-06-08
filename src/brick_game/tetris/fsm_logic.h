#ifndef BRICK_GAME_TETRIS_FSM_LOGIC_H_
#define BRICK_GAME_TETRIS_FSM_LOGIC_H_

#include <ncurses.h>

#include "tetris_backend.h"
#include "tetris_defines.h"
#include "tetris_objects.h"

user_action_t get_signal(int user_input);

void moveup(figure_t *figure);

void movedown(figure_t *figure);

void moveleft(figure_t *figure);
void moveright(figure_t *figure);
void game_tact(game_info_t *game, figure_t *figure);

void sigact(user_action_t sig, game_info_t *game, figure_t *figure);

void handle_collision(game_info_t *game, figure_t *figure);

#endif  // BRICK_GAME_TETRIS_FSM_LOGIC_H_
