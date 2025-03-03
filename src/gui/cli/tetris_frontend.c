#include "tetris_frontend.h"

void update_screen(game_info_t *game, figure_t *figure) {
  switch (game->state) {
    case STARTED:
      print_welcome_window();
      break;
    case PLAYING:
      clear_overlay();
      print_overlay();
      print_stats(game);
      print_field(game);
      print_shadow_figure(BOARD_Y + figure->shadow_y, BOARD_X + figure->x,
                          figure->shape);
      print_figure(BOARD_Y + figure->y, BOARD_X + figure->x, figure->shape,
                   figure->id);
      break;
    case STOPPED:
      print_quit_window();
      break;
    case PAUSED:
      print_pause_window();
      break;
    case OVER:
      print_gameover_window();
      break;
    default:
      break;
  }
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    for (int j = left_x + 1; j < right_x; j++) {
      MVADDCH(i, j, ' ');
    }
  }
}

void print_game_pool(int top_y, int bottom_y, int left_x, int right_x) {
  for (int i = top_y; i <= bottom_y; i++) {
    MVADDCH(i, left_x, SOLID_BLOCK);
    MVADDCH(i, right_x, SOLID_BLOCK);
  }
  for (int i = left_x + 1; i < right_x; i++) MVADDCH(bottom_y, i, SOLID_BLOCK);
}

void print_stats(game_info_t *game) {
  MVPRINTW(2, BOARD_W + 12, "%d", game->high_score);
  MVPRINTW(5, BOARD_W + 12, "%d", game->score);
  MVPRINTW(8, BOARD_W + 12, "%d", game->level);
  MVPRINTW(11, BOARD_W + 12, "%d", game->lines);
  print_figure(15, BOARD_W + 11, game->next, game->next_id);
}

void print_figure(int y, int x, int **figure, int id) {
  attron(COLOR_PAIR(SHAPE_COLOR(id)));
  for (int i = 0; i < 4; i++) {
    MVADDCH(y + figure[i][0], x + figure[i][1], ACS_BLOCK);
  }
  attroff(COLOR_PAIR(SHAPE_COLOR(id)));
}

void print_shadow_figure(int y, int x, int **figure) {
  attron(COLOR_PAIR(SHADOW_COLOR));
  for (int i = 0; i < 4; i++) {
    MVADDCH(y + figure[i][0], x + figure[i][1], ACS_BLOCK);
  }
  attroff(COLOR_PAIR(SHADOW_COLOR));
}

void print_field(game_info_t *game) {
  for (int i = 0; i < BOARD_H; i++) {
    for (int j = 0; j < BOARD_W; j++) {
      if (game->field[i][j]) {
        attron(COLOR_PAIR(game->field[i][j]));
        MVADDCH(BOARD_Y + i, BOARD_X + j, ACS_BLOCK);
        attroff(COLOR_PAIR(game->field[i][j]));
      }
    }
  }
}

void print_overlay(void) {
  print_rectangle(0, BOARD_H + 2, 0, BOARD_W + 3);
  print_rectangle(0, BOARD_H + 2, BOARD_W + 4, BOARD_W + INFO_BLOCK_W + 3);

  print_rectangle(1, 3, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(4, 6, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(7, 9, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(10, 12, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(13, 17, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);

  print_game_pool(1, BOARD_H + 1, 1, BOARD_W + 2);

  MVPRINTW(2, BOARD_W + 6, "TOP");
  MVPRINTW(5, BOARD_W + 6, "SCORE");
  MVPRINTW(8, BOARD_W + 6, "LEVEL");
  MVPRINTW(11, BOARD_W + 6, "LINES");
  MVPRINTW(14, BOARD_W + 6, "NEXT BLOCK");
}

void print_welcome_window(void) {
  int tetris_logo[LOGO_H][LOGO_W] = {
      {4, 4, 4, 0, 6, 6, 6, 0, 1, 1, 1, 0, 3, 3, 3, 0, 0, 2, 0, 5, 5, 5},
      {0, 4, 0, 0, 6, 0, 0, 0, 0, 1, 0, 0, 3, 0, 3, 0, 0, 2, 0, 5, 0, 0},
      {0, 4, 0, 0, 6, 6, 6, 0, 0, 1, 0, 0, 3, 3, 0, 0, 0, 2, 0, 5, 5, 5},
      {0, 4, 0, 0, 6, 0, 0, 0, 0, 1, 0, 0, 3, 0, 3, 0, 0, 2, 0, 0, 0, 5},
      {0, 4, 0, 0, 6, 6, 6, 0, 0, 1, 0, 0, 3, 0, 0, 3, 0, 2, 0, 5, 5, 5}};

  print_rectangle(0, 19, 0, 27);

  for (int i = 0; i < LOGO_H; i++) {
    for (int j = 0; j < LOGO_W; j++) {
      if (tetris_logo[i][j]) {
        attron(COLOR_PAIR(tetris_logo[i][j]));
        MVADDCH(i + 2, j + 3, SOLID_BLOCK);
        attroff(COLOR_PAIR(tetris_logo[i][j]));
      }
    }
  }

  MVPRINTW(9, 3, "Press [Enter] to start");
  attron(A_BOLD);
  MVPRINTW(12, 3, "Controls:");
  attroff(A_BOLD);
  MVPRINTW(14, 3, "[Arrows]  -  movement");
  MVPRINTW(15, 3, "[Space]   -  rotation");
  MVPRINTW(16, 3, "[Escape]  -  pause");
  MVPRINTW(17, 3, "[Q]       -  quit game");
}

void print_gameover_window(void) {
  int game_over[OVER_H][OVER_W] = {
      {6, 6, 6, 6, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 6, 0, 6, 6, 6},
      {6, 0, 0, 0, 0, 6, 0, 0, 6, 0, 6, 6, 0, 6, 6, 0, 6, 0, 0},
      {6, 0, 6, 6, 0, 6, 0, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 6, 6},
      {6, 0, 0, 6, 0, 6, 6, 6, 6, 0, 6, 0, 0, 0, 6, 0, 6, 0, 0},
      {6, 6, 6, 6, 0, 6, 0, 0, 6, 0, 6, 0, 0, 0, 6, 0, 6, 6, 6},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {4, 4, 4, 4, 0, 4, 0, 0, 0, 4, 0, 4, 4, 4, 0, 4, 4, 4, 0},
      {4, 0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 4, 0},
      {4, 0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 4, 4, 4, 0, 4, 4, 0, 0},
      {4, 0, 0, 4, 0, 0, 4, 0, 4, 0, 0, 4, 0, 0, 0, 4, 0, 4, 0},
      {4, 4, 4, 4, 0, 0, 0, 4, 0, 0, 0, 4, 4, 4, 0, 4, 0, 0, 4}};

  print_rectangle(2, 18, -1, 28);

  for (int i = 0; i < OVER_H; i++) {
    for (int j = 0; j < OVER_W; j++) {
      if (game_over[i][j]) {
        attron(COLOR_PAIR(game_over[i][j]));
        MVADDCH(i + 4, j + 5, SOLID_BLOCK);
        attroff(COLOR_PAIR(game_over[i][j]));
      }
    }
  }

  MVPRINTW(16, 3, "Press [Enter] to retry");
}

void print_pause_window(void) {
  print_rectangle(4, 10, -1, 28);

  for (int i = 5; i < 10; i++) {
    for (int j = 0; j < 28; j++) {
      MVADDCH(i, j, ' ');
    }
  }

  attron(A_BOLD);
  MVPRINTW(6, 3, "PAUSE");
  attroff(A_BOLD);
  MVPRINTW(8, 3, "Press [Enter] to resume");
}

void print_quit_window(void) {
  print_rectangle(4, 11, -1, 28);

  attron(A_BOLD);
  MVPRINTW(6, 3, "Are you sure");
  MVPRINTW(7, 3, "you want to quit?");
  attroff(A_BOLD);
  MVPRINTW(9, 3, "Yes(Y)     No(N)");
}

void set_colors(void) {
  if (has_colors()) {
    start_color();
    init_color(COLOR_ORANGE, 996, 566, 47);
    init_color(COLOR_LIGHT_YELLOW, 980, 902, 312);
    init_color(COLOR_LIGHT_BLUE, 144, 347, 593);
    init_color(COLOR_GREY, 360, 360, 360);
    init_pair(O_COLOR, COLOR_LIGHT_YELLOW, COLOR_BLACK);
    init_pair(I_COLOR, COLOR_CYAN, COLOR_BLACK);
    init_pair(S_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(Z_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(T_COLOR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(L_COLOR, COLOR_ORANGE, COLOR_BLACK);
    init_pair(J_COLOR, COLOR_LIGHT_BLUE, COLOR_BLACK);
    init_pair(SHADOW_COLOR, COLOR_GREY, COLOR_BLACK);
    init_pair(NO_COLOR, COLOR_WHITE, COLOR_BLACK);
  }
}

void clear_overlay(void) {
  for (int i = 0; i < BOARD_H + 2; i++) {
    for (int j = -1; j < BOARD_W + INFO_BLOCK_W + 5; j++) {
      MVADDCH(i, j, ' ');
    }
  }
}
