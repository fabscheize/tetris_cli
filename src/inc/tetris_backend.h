#ifndef TETRIS_BACKEND_H_
#define TETRIS_BACKEND_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tetris_defines.h"
#include "tetris_objects.h"

enum shapes { O = 0, I, S, Z, T, L, J };

int **init_matrix(int height, int width);
void free_matrix(int **matrix);

game_info_t *create_game(int ***shapes, int id, int height, int width);
void destroy_game(game_info_t *game);
void restart_game(game_info_t *game);

int ***init_figures(void);
void free_figures(int ***figures);

figure_t *create_figure(int ***shapes, int id, int y, int x);
void destroy_figure(figure_t *figure);
void drop_new_figure(game_info_t *game, figure_t *figure);

void copy_shape(int **shape_1, int **shape_2);
void rotate_figure(figure_t *figure, game_info_t *game);
void plant_figure(game_info_t *game, figure_t *figure);

void moveup(figure_t *figure);
void movedown(figure_t *figure);
void moveleft(figure_t *figure);
void moveright(figure_t *figure);
void handle_collision(game_info_t *game, figure_t *figure);

int is_full_line(game_info_t *game, int line);

void drop_lines(game_info_t *game, int line);
int erase_lines(game_info_t *game);

int check_figure_collision(game_info_t *game, figure_t *figure);
int check_borders_collision(figure_t *figure);

void update_stats(game_info_t *game, int full_lines);
int load_high_score(const char *filename);
int save_high_score(const char *filename, game_info_t *game);

#endif  // TETRIS_BACKEND_H_
