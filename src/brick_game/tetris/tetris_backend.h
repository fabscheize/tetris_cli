#ifndef BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
#define BRICK_GAME_TETRIS_TETRIS_BACKEND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tetris_objects.h"

#define RANDOM_FIGURE (random() % 7)

enum shapes { O = 0, I, S, Z, T, L, J };

void init_game(game_info_t *game, int figure[4][2], int height, int width);
int load_high_score();
void destroy_game(game_info_t *game);

#endif  // BRICK_GAME_TETRIS_TETRIS_BACKEND_H_
