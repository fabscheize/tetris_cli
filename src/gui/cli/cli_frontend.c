#include "cli_frontend.h"

// tetrs
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

  // MVPRINTW(0, 0, "%d - %d", getmaxx(stdscr), getmaxy(stdscr));
}

void print_levelerror(void) {
  clear();
  MVPRINTW(0, 0, "An error occured openning level file!");
  MVPRINTW(2, 0, "Please check ./tests/ directory.");
  MVPRINTW(3, 0, "There should be 5 level files named level_(1-5).txt.");
  MVPRINTW(4, 0, "Also try to open the game nearby ./tests/ directory.");
  MVPRINTW(6, 0, "Press any key to exit.");
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
  print_figure(15, BOARD_W + 11, game->next);
  // MVADDCH(BOARD_Y + 19, BOARD_X + 9, ACS_BLOCK);
}

void print_figure(int y, int x, int (*figure)[2]) {
  for (int i = 0; i < 4; i++) {
    MVADDCH(y + figure[i][0], x + figure[i][1], ACS_BLOCK);
  }
}
