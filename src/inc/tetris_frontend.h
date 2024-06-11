#ifndef TETRIS_FRONTEND_H_
#define TETRIS_FRONTEND_H_

#include <ncurses.h>

#include "tetris_defines.h"
#include "tetris_objects.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_game_pool(int top_y, int bottom_y, int left_x, int right_x);

void print_stats(game_info_t *game);
void print_figure(int y, int x, int **figure, int id);
void print_field(game_info_t *game);

void print_overlay(void);
void print_welcome_window(void);
void print_gameover_window(void);
void print_pause_window(void);
void print_quit_window(void);

void set_colors(void);
void clear_overlay(void);

#endif  // TETRIS_FRONTEND_H_
