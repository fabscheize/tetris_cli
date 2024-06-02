#ifndef BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_
#define BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/tetris_objects.h"
#include "cli_defines.h"
// #include "objects.h"

void print_overlay(void);
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(game_info_t *game);
void print_figure(int y, int x, int (*figure)[2]);
void print_game_pool(int top_y, int bottom_y, int left_x, int right_x);

#endif  // BRICK_GAME_GUI_CLI_CLI_FRONTEND_H_
