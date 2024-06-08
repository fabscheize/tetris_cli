#include "tetris_backend.h"

game_info_t *create_game(figure_t *figure, int height, int width) {
  game_info_t *game = malloc(sizeof(game_info_t));
  game->field = (int **)calloc(height, sizeof(int *));
  game->field[0] = (int *)calloc(height * width, sizeof(int));
  for (int i = 1; i < height; i++) game->field[i] = game->field[0] + i * width;
  game->next = figure->shape;
  game->next_id = figure->id;
  game->score = 0;
  game->high_score = load_high_score();
  game->level = 1;
  game->lines = 0;
  game->speed = 1;
  game->state = PLAYING;
  game->ticks_left = TIMEOUT;

  return game;
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
    if (game->field[0]) {
      free(game->field[0]);
    }
    free(game->field);
  }
  if (game) free(game);
}

int ***init_figures() {
  int shapes[][DOTS][COORDS] = {
      {{0, 0}, {1, 0}, {1, -1}, {0, -1}}, {{0, 0}, {0, 1}, {0, -1}, {0, -2}},
      {{0, 0}, {0, 1}, {1, 0}, {1, -1}},  {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
      {{0, 0}, {0, 1}, {0, -1}, {1, 0}},  {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
      {{0, 0}, {0, 1}, {0, -1}, {1, 1}},
  };

  int ***figures = (int ***)calloc(SHAPES, sizeof(int **));

  for (int i = 0; i < SHAPES; i++) {
    figures[i] = (int **)calloc(DOTS, sizeof(int *));
    for (int j = 0; j < DOTS; j++) {
      figures[i][j] = (int *)calloc(COORDS, sizeof(int));
    }
  }

  for (int i = 0; i < SHAPES; i++) {
    for (int j = 0; j < DOTS; j++) {
      for (int k = 0; k < COORDS; k++) {
        figures[i][j][k] = shapes[i][j][k];
      }
    }
  }

  return figures;
}

void free_figures(int ***figures) {
  for (int i = 0; i < SHAPES; ++i) {
    if (figures[i]) {
      for (int j = 0; j < DOTS; ++j) free(figures[i][j]);
      free(figures[i]);
    }
  }
  free(figures);
}

figure_t *create_figure(int ***shapes, int id, int y, int x) {
  figure_t *figure = malloc(sizeof(figure_t));
  figure->shapes_list = shapes;
  figure->id = id;
  figure->shape = figure->shapes_list[figure->id];
  figure->y = y;
  figure->x = x;

  return figure;
}

void destroy_figure(figure_t *figure) {
  if (figure) free(figure);
}

void drop_new_figure(game_info_t *game, figure_t *figure) {
  figure->id = game->next_id;
  figure->shape = game->next;
  figure->y = START_Y;
  figure->x = START_X;
  game->next_id = RANDOM_FIGURE;
  game->next = figure->shapes_list[game->next_id];

}

void plant_figure(game_info_t *game, figure_t *figure) {
  for (int i = 0; i < DOTS; i++) {
    game->field[figure->y + figure->shape[i][Y]]
               [figure->x + figure->shape[i][X]] = figure->id + 1;
  }
}

int check_full_lines(game_info_t *game) {
  int line = 1;
  int full_lines = 0;

  do {
    for (int i = 0; i < BOARD_W && line != 0; i++)
      line = game->field[BOARD_H - 1 - full_lines][i];
    if (line) full_lines++;
  } while (line != 0);

  return full_lines;
}

int erase_lines(game_info_t *game, int full_lines) {
  for (int i = BOARD_H - full_lines - 1; i >= 0; i--) {
    for (int j = 0; j < BOARD_W; j++) {
      game->field[i + full_lines][j] = game->field[i][j];
    }
  }
  for (int i = 0; i < full_lines; i++) {
    for (int j = 0; j < BOARD_W; j++) {
      game->field[i][j] = 0;
    }
  }

  int ret = 0;
  if (full_lines == 1) ret = 100;
  if (full_lines == 2) ret = 300;
  if (full_lines == 3) ret = 700;
  if (full_lines >= 4) ret = 1500;

  return ret;
}

void copy_shape(int **shape_1, int **shape_2) {
  for (int i = 0; i < DOTS; i++) {
    for (int j = 0; j < COORDS; j++) {
      shape_2[i][j] = shape_1[i][j];
    }
  }
}

void rotate_figure(figure_t *figure, game_info_t *game) {
  figure_t *temp =
      create_figure(figure->shapes_list, figure->id, figure->y, figure->x);
  copy_shape(figure->shape, temp->shape);

  for (int i = 0; i < DOTS; i++) {
    int flag = abs(temp->shape[i][Y]) & abs(temp->shape[i][X]);
    switch (flag) {
      case 0:
        if (temp->shape[i][Y] == 0) {
          temp->shape[i][Y] = -temp->shape[i][X];
          temp->shape[i][X] = 0;
        } else {
          temp->shape[i][X] = temp->shape[i][Y];
          temp->shape[i][Y] = 0;
        }
        break;
      case 1:
        if (temp->shape[i][Y] == -1 && temp->shape[i][X] == 1) {
          temp->shape[i][Y] = -1;
          temp->shape[i][X] = -1;
        }
        if (temp->shape[i][Y] == -1 && temp->shape[i][X] == -1) {
          temp->shape[i][Y] = 1;
          temp->shape[i][X] = -1;
        }
        if (temp->shape[i][Y] == 1 && temp->shape[i][X] == -1) {
          temp->shape[i][Y] = 1;
          temp->shape[i][X] = 1;
        }
        if (temp->shape[i][Y] == 1 && temp->shape[i][X] == 1) {
          temp->shape[i][Y] = -1;
          temp->shape[i][X] = 1;
        }
        break;
    }
  }
  if (!check_borders_collision(temp))
    if (!check_figure_collision(game, temp))
      copy_shape(temp->shape, figure->shape);

  destroy_figure(temp);
}

int check_figure_collision(game_info_t *game, figure_t *figure) {
  int flag = 0;
  for (int i = 0; i < DOTS && flag == 0; i++) {
    flag += game->field[figure->y + figure->shape[i][Y]]
                       [figure->x + figure->shape[i][X]];
  }

  return flag;
}

bool check_borders_collision(figure_t *figure) {
  bool flag = FALSE;
  for (int i = 0; i < DOTS && flag == FALSE; i++) {
    if (((figure->y + figure->shape[i][Y]) < 0) ||
        ((figure->y + figure->shape[i][Y]) >= BOARD_H))
      flag = TRUE;
    if (((figure->x + figure->shape[i][X]) < 0) ||
        ((figure->x + figure->shape[i][X]) >= BOARD_W))
      flag = TRUE;
  }

  return flag;
}



// void pause_game(game_info_t *game) {}
