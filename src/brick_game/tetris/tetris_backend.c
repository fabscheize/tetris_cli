#include "tetris_backend.h"

void init_game(game_info_t *game, int figure[4][2], int height, int width) {
  // game->field = (int **)calloc(height * width, sizeof(int));
  game->field = (int **)calloc(height, sizeof(int *));
  game->field[0] = (int *)calloc(height * width, sizeof(int));
  for (int i = 1; i < height; i++) game->field[i] = game->field[0] + i * width;
  game->next = figure;
  game->score = 0;
  game->high_score = load_high_score();
  game->level = 1;
  game->lines = 0;
  game->speed = 1;
  game->pause = 0;
}

int load_high_score() {
  const char filename[] = "save";
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    file = fopen(filename, "w");
    if (file == NULL) return -1;
    fclose(file);
    return 0;
  }

  int score = 0;
  fscanf(file, "%d", &score);
  fclose(file);
  return score;
}

void destroy_game(game_info_t *game) {
  if (game->field) {
    free(game->field[0]);
    free(game->field);
  }
}
