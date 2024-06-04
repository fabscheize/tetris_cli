#ifndef BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
#define BRICK_GAME_TETRIS_TETRIS_BACKEND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tetris_objects.h"
#include "tetris_defines.h"

enum shapes { O = 0, I, S, Z, T, L, J };

int load_high_score();

game_info_t* create_game(figure_t *figure, int height, int width);
void destroy_game(game_info_t *game);

int ***init_figures();
void free_figures(int ***figures);

figure_t *create_figure(int ***shapes, int y, int x);
void destroy_figure(figure_t *figure);

void drop_new_figure(figure_t *figure);
void plant_figure(game_info_t *game, figure_t *figure);

#endif  // BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
