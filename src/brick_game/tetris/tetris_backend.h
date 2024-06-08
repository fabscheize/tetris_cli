#ifndef BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
#define BRICK_GAME_TETRIS_TETRIS_BACKEND_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tetris_objects.h"
#include "tetris_defines.h"

enum shapes { O = 0, I, S, Z, T, L, J };

int load_high_score();

game_info_t* create_game(int ***shapes, int id, int height, int width);
void destroy_game(game_info_t *game);

int ***init_figures();
void free_figures(int ***figures);

figure_t *create_figure(int ***shapes, int id, int y, int x);
void destroy_figure(figure_t *figure);
void copy_shape(int **shape_1, int **shape_2);

void drop_new_figure(game_info_t *game, figure_t *figure);
void plant_figure(game_info_t *game, figure_t *figure);

int check_full_lines(game_info_t *game);
int erase_lines(game_info_t *game, int full_lines);

void rotate_figure(figure_t *figure, game_info_t *game);

int check_figure_collision(game_info_t *game, figure_t *figure);
bool check_borders_collision(figure_t *figure);

void pause_game(game_info_t *game);

int **init_matrix(int height, int width);
void free_matrix(int **matrix);

#endif  // BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
