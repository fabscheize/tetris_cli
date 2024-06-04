#include "tetris.h"

int main() {
  initscr();
  signal(SIGWINCH, NULL);
  setlocale(LC_ALL, "");
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  set_colors();

  print_overlay();
  game_loop();

  endwin();
  return 0;
}

void game_loop() {
  srandom(time(NULL));

  int ***figures = init_figures();

  figure_t *current_figure = create_figure(figures, START_Y, START_X);
  game_info_t *new_game = create_game(current_figure, BOARD_H, BOARD_W);
  drop_new_figure(current_figure);

  // bool break_flag = TRUE;
  // int signal = 0;
  // frog_state state = START;

  print_stats(new_game);
  plant_figure(new_game, current_figure);
  print_field(new_game);



  getch();
  destroy_game(new_game);
  destroy_figure(current_figure);
  free_figures(figures);

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
