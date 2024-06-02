#include "tetris.h"

int main() {
  initscr();
  signal(SIGWINCH, NULL);
  setlocale(LC_ALL, "");
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();

  print_overlay();
  game_loop();

  endwin();
  return 0;
}

void game_loop() {
  srandom(time(NULL) + 1);
  // int figures[][4][2] = {
  //     {{0, 0}, {1, 0}, {1, -1}, {0, -1}}, {{0, 0}, {0, 1}, {0, -1}, {0, -2}},
  //     {{0, 0}, {0, 1}, {1, 0}, {1, -1}},  {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
  //     {{0, 0}, {0, 1}, {0, -1}, {1, 0}},  {{0, 0}, {0, 1}, {0, -1}, {1, -1}},
  //     {{0, 0}, {0, 1}, {0, -1}, {1, 1}},
  // };

  int O_shape[4][2] = {{0, 0}, {1, 0}, {1, -1}, {0, -1}};
  int I_shape[4][2] = {{0, 0}, {0, 1}, {0, -1}, {0, -2}};
  int S_shape[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, -1}};
  int Z_shape[4][2] = {{0, 0}, {0, -1}, {1, 0}, {1, 1}};
  int T_shape[4][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}};
  int L_shape[4][2] = {{0, 0}, {0, 1}, {0, -1}, {1, -1}};
  int J_shape[4][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 1}};

  int(*figures[])[4][2] = {&O_shape, &I_shape, &S_shape, &Z_shape,
                           &T_shape, &L_shape, &J_shape};

  game_info_t new_game;

  init_game(&new_game, (*figures[RANDOM_FIGURE]), BOARD_H, BOARD_W);

  // board_t map;
  // game_stats_t stats;
  // player_pos frog;

  // bool break_flag = TRUE;
  // int signal = 0;
  // frog_state state = START;

  // stats_init(&stats);

  print_stats(&new_game);

  getch();
  destroy_game(&new_game);

  // while (break_flag) {
  //   if (state == GAMEOVER || state == EXIT_STATE || state ==
  //   FILE_ERROR_STATE)
  //     break_flag = FALSE;

  //   sigact(get_signal(signal), &state, &stats, &map, &frog);

  //   if (state == MOVING || state == START) signal = GET_USER_INPUT;
  // }

  // if (state == FILE_ERROR_STATE) {
  //   print_levelerror();
  //   nodelay(stdscr, FALSE);
  //   getch();
  // }
}
