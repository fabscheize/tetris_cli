#include "tetris_main.h"

int main(void) {
  WIN_INIT();
  nodelay(stdscr, TRUE);
  setlocale(LC_ALL, "");
  set_colors();
  srandom(time(NULL));

  game_loop();

  endwin();
  return 0;
}

void game_loop(void) {
  int signal = 0;
  int ***figures = init_figures();

  game_info_t *game = create_game(figures, RANDOM_FIGURE, BOARD_H, BOARD_W);
  figure_t *figure = create_figure(figures, RANDOM_FIGURE, START_Y, START_X);

  while (game->state != TERMINATED) {
    update_screen(game, figure);
    update_current_state(get_signal(signal), game, figure);
    signal = GET_USER_INPUT;
  }

  save_high_score(game);
  destroy_game(game);
  destroy_figure(figure);
  free_figures(figures);
}
