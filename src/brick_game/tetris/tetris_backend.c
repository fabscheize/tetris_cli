#include "tetris_backend.h"

int **init_matrix(int height, int width) {
  int **matrix = (int **)calloc(height, sizeof(int *));
  matrix[0] = (int *)calloc(height * width, sizeof(int));
  for (int i = 1; i < height; i++) matrix[i] = matrix[0] + i * width;

  return matrix;
}

void free_matrix(int **matrix) {
  if (matrix) {
    if (matrix[0]) {
      free(matrix[0]);
    }
    free(matrix);
  }
}

game_info_t *create_game(int ***shapes, int id, int height, int width) {
  game_info_t *game = malloc(sizeof(game_info_t));
  game->shapes_list = shapes;
  game->field = init_matrix(height, width);
  game->next = init_matrix(DOTS, COORDS);
  game->next_id = id;
  copy_shape(game->shapes_list[game->next_id], game->next);
  game->score = 0;
  game->high_score = load_high_score();
  game->level = 1;
  game->lines = 0;
  game->speed = INITIAL_SPEED_NS;
  game->state = STARTED;

  return game;
}

void destroy_game(game_info_t *game) {
  free_matrix(game->next);
  free_matrix(game->field);
  if (game) free(game);
}

void restart_game(game_info_t *game, int id) {
  memset(game->field[0], 0, BOARD_H * BOARD_W * sizeof(int));
  game->next_id = id;
  copy_shape(game->shapes_list[game->next_id], game->next);
  game->score = 0;
  game->level = 1;
  game->lines = 0;
  game->speed = INITIAL_SPEED_NS;
}

int ***init_figures(void) {
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
  figure->id = id;
  figure->shape = init_matrix(DOTS, COORDS);
  copy_shape(shapes[figure->id], figure->shape);
  figure->y = y;
  figure->x = x;

  return figure;
}

void destroy_figure(figure_t *figure) {
  free_matrix(figure->shape);
  if (figure) free(figure);
}

void drop_new_figure(game_info_t *game, figure_t *figure, int id) {
  figure->id = game->next_id;
  copy_shape(game->next, figure->shape);
  figure->y = START_Y;
  figure->x = START_X;
  game->next_id = id;
  copy_shape(game->shapes_list[game->next_id], game->next);
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
      create_figure(game->shapes_list, figure->id, figure->y, figure->x);
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
        } else if (temp->shape[i][Y] == -1 && temp->shape[i][X] == -1) {
          temp->shape[i][Y] = 1;
          temp->shape[i][X] = -1;
        } else if (temp->shape[i][Y] == 1 && temp->shape[i][X] == -1) {
          temp->shape[i][Y] = 1;
          temp->shape[i][X] = 1;
        } else if (temp->shape[i][Y] == 1 && temp->shape[i][X] == 1) {
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

void plant_figure(game_info_t *game, figure_t *figure) {
  for (int i = 0; i < DOTS; i++) {
    game->field[figure->y + figure->shape[i][Y]]
               [figure->x + figure->shape[i][X]] = figure->id + 1;
  }
}

void moveup(figure_t *figure) { figure->y -= 1; }

void movedown(figure_t *figure) { figure->y += 1; }

void moveleft(figure_t *figure) {
  int flag = 1;

  for (int i = 0; i < DOTS && flag == 1; i++)
    if (figure->shape[i][X] + figure->x == 0) flag = 0;

  if (flag) figure->x -= 1;
}

void moveright(figure_t *figure) {
  int flag = 1;

  for (int i = 0; i < DOTS && flag == 1; i++)
    if (figure->shape[i][X] + figure->x == BOARD_W - 1) flag = 0;

  if (flag) figure->x += 1;
}

void handle_collision(game_info_t *game, figure_t *figure) {
  if (check_borders_collision(figure) || check_figure_collision(game, figure)) {
    moveup(figure);
    plant_figure(game, figure);
    update_stats(game, erase_lines(game));
    drop_new_figure(game, figure, RANDOM_FIGURE);
    if (check_figure_collision(game, figure)) {
      game->state = OVER;
    }
  }
}

int is_full_line(game_info_t *game, int line) {
  int flag = 1;

  for (int j = 0; j < BOARD_W && flag != 0; j++) flag = game->field[line][j];

  return flag;
}

void drop_lines(game_info_t *game, int line) {
  for (int i = line; i > 0; i--) {
    for (int j = 0; j < BOARD_W; j++) {
      game->field[i][j] = game->field[i - 1][j];
    }
  }

  for (int j = 0; j < BOARD_W; j++) {
    game->field[0][j] = 0;
  }
}

int erase_lines(game_info_t *game) {
  int full_lines = 0;

  for (int i = 0; i < BOARD_H; i++) {
    if (is_full_line(game, i)) {
      drop_lines(game, i);
      full_lines++;
    }
  }

  return full_lines;
}

int check_figure_collision(game_info_t *game, figure_t *figure) {
  int flag = 0;
  for (int i = 0; i < DOTS && flag == 0; i++) {
    flag += game->field[figure->y + figure->shape[i][Y]]
                       [figure->x + figure->shape[i][X]];
  }

  return flag;
}

int check_borders_collision(figure_t *figure) {
  int flag = 0;
  for (int i = 0; i < DOTS && flag == 0; i++) {
    if (((figure->y + figure->shape[i][Y]) < 0) ||
        ((figure->y + figure->shape[i][Y]) >= BOARD_H))
      flag = 1;
    if (((figure->x + figure->shape[i][X]) < 0) ||
        ((figure->x + figure->shape[i][X]) >= BOARD_W))
      flag = 1;
  }

  return flag;
}

void update_stats(game_info_t *game, int full_lines) {
  game->lines += full_lines;
  if (full_lines == 1) game->score += 100;
  if (full_lines == 2) game->score += 300;
  if (full_lines == 3) game->score += 700;
  if (full_lines >= 4) game->score += 1500;

  if (game->score > game->high_score) game->high_score = game->score;

  if (game->level < 10) {
    game->level = 1 + game->score / 600;
    game->speed = INITIAL_SPEED_NS - DELTA_SPEED_NS * (game->level - 1);
  }
}

int load_high_score(void) {
  char save_path[100] = "";
  access_save_dir(save_path);

  FILE *file = fopen(save_path, "r");
  if (file == NULL) {
    file = fopen(save_path, "w");
    if (file == NULL) return -1;
    fclose(file);
    return 0;
  }

  int score = 0;
  fscanf(file, "%d", &score);
  fclose(file);
  return score;
}

int save_high_score(game_info_t *game) {
  char save_path[100] = "";
  access_save_dir(save_path);

  FILE *file = fopen(save_path, "w");
  if (file == NULL) return -1;
  fprintf(file, "%d", game->high_score);
  fclose(file);

  return 0;
}

void access_save_dir(char *save_path) {
  char *home_path = getenv("HOME");
  strcpy(save_path, home_path);
  strcat(save_path, SAVE_DIR);
  if (access(save_path, F_OK) == -1) mkdir(save_path, 0777);
  strcat(save_path, SAVE_FILE);
}
