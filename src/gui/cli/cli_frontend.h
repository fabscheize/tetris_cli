#ifndef BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_
#define BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/tetris_objects.h"
#include "../../brick_game/tetris/tetris_defines.h"

enum colors {O_COLOR = 1, I_COLOR, S_COLOR, Z_COLOR, T_COLOR, L_COLOR, J_COLOR, NO_COLOR};

void print_overlay(void);
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(game_info_t *game);
void print_figure(int y, int x, int **figure, int id);
void print_game_pool(int top_y, int bottom_y, int left_x, int right_x);
void print_field(game_info_t *game);
void set_colors();

void print_big_figure(int y, int x, int **figure, int id);

#endif  // BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_
