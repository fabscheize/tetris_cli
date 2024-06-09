#include "tetris.h"

int main() {
  WIN_INIT(10);
  set_colors();

  srandom(time(NULL));
  game_loop();

  endwin();
  return 0;
}

void game_loop() {
  int signal = 0;
  int ***figures = init_figures();

  game_info_t *new_game = create_game(figures, RANDOM_FIGURE, BOARD_H, BOARD_W);
  figure_t *current_figure =
      create_figure(figures, RANDOM_FIGURE, START_Y, START_X);


  while (new_game->state != OVER && new_game->state != QUIT) {
    sigact(get_signal(signal), new_game, current_figure);
    clear_overlay();
    print_overlay();
    print_stats(new_game);
    print_field(new_game);
    print_figure(BOARD_Y + current_figure->y, BOARD_X + current_figure->x,
                 current_figure->shape, current_figure->id);
    signal = GET_USER_INPUT;
  }
  destroy_game(new_game);
  destroy_figure(current_figure);
  free_figures(figures);

  // if (state == FILE_ERROR_STATE) {
  //   print_levelerror();
  //   nodelay(stdscr, FALSE);
  //   getch();
  // }
}
