#include "../../inc/tetris_main.h"

int main() {
  // WIN_INIT(0);
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  signal(SIGWINCH, NULL);
  set_escdelay(0);
  cbreak();
  nodelay(stdscr, TRUE);
  setlocale(LC_ALL, "");
  set_colors();

  srandom(time(NULL));
  game_loop();

  endwin();
  return 0;
}

void game_loop() {
  int signal = 0;
  int ***figures = init_figures();

  game_info_t *game = create_game(figures, RANDOM_FIGURE, BOARD_H, BOARD_W);
  figure_t *current_figure =
      create_figure(figures, RANDOM_FIGURE, START_Y, START_X);

  while (game->state != TERMINATED) {
    update_current_state(get_signal(signal), game, current_figure);
    signal = GET_USER_INPUT;
  }
  save_high_score(SAVE_FILE, game);
  destroy_game(game);
  destroy_figure(current_figure);
  free_figures(figures);
}
