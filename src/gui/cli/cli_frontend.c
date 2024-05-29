#include "cli_frontend.h"

// tetrs
void print_overlay(void) {

  print_rectangle(0, BOARD_H + 1, 0, BOARD_W + 3);
  print_rectangle(0, BOARD_H + 1, BOARD_W + 4, BOARD_W + INFO_BLOCK_W + 3);

  print_rectangle(1, 3, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(4, 6, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(7, 9, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);
  print_rectangle(10, 14, BOARD_W + 5, BOARD_W + INFO_BLOCK_W + 2);

  MVPRINTW(2, BOARD_W + 6, "LEVEL");
  MVPRINTW(5, BOARD_W + 6, "SCORE");
  MVPRINTW(8, BOARD_W + 6, "SPEED");
  MVPRINTW(11, BOARD_W + 6, "NEXT BLOCK");

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

// void print_stats(game_stats_t *stats)
// {
//     MVPRINTW(2, BOARD_W + 12, "%d", stats->level);
//     MVPRINTW(5, BOARD_W + 12, "%d", stats->score);
//     MVPRINTW(8, BOARD_W + 12, "%d", stats->speed);
//     MVPRINTW(11, BOARD_W + 12, "%d", stats->lives);
// }

// void print_board(board_t *game, player_pos *frog)
// {
//     print_cars(game);
//     PRINT_FROG(frog->x, frog->y);
// }

// void print_cars(board_t *game)
// {
//     for(int i = MAP_PADDING + 1; i < BOARD_H - MAP_PADDING + 1; i++)
//     {
//         if (i % 2 == (MAP_PADDING + 1) % 2)
//         {
//             for (int j = 1; j < BOARD_W + 1; j++)
//                 MVADDCH(i, j, ACS_BLOCK);
//         }
//         else
//         {
//             for (int j = 1; j < BOARD_W + 1; j++)
//             {
//                 if (game->ways[i - MAP_PADDING - 1][j - 1] == '0')
//                     MVADDCH(i, j, ' ');
//                 else
//                     MVADDCH(i, j, ']');
//             }
//         }
//     }
// }

// void print_finished(board_t *game)
// {
//     for (int i = 0; i < BOARD_W; i++)
//     {
//         if (game->finish[i] == '0')
//             MVADDCH(1, i + 1, ACS_BLOCK);
//         else
//             MVADDCH(1, i + 1, ' ');
//     }
// }
// void print_banner(game_stats_t *stats)
// {
//     banner_t banner;

//     memset(banner.matrix, 0, (BANNER_N + 1) * (BANNER_M + 1));

//     clear();

//     if (!(read_banner(stats, &banner)))
//     {
//         for (int i = 0; i < BANNER_N; i++)
//             for (int j = 0; j < BANNER_M; j++)
//                 if (banner.matrix[i][j] == '#')
//                     MVADDCH(i, j, ACS_BLOCK);
//                 else
//                     MVADDCH(i, j, ' ');
//         refresh();
//         napms(2000);
//     }
// }

// int read_banner(game_stats_t *stats, banner_t *banner)
// {
//     int rc = SUCCESS;
//     FILE *file = NULL;

//     if (stats->lives)
//         file = fopen(YOU_WON, "r");
//     else
//         file = fopen(YOU_LOSE, "r");

//     if (file)
//     {
//         for (int i = 0; i < BANNER_N - 1 && !rc; i++)
//         {
//             if (fgets(banner->matrix[i], BANNER_M + 2, file) == NULL)
//                 rc = ERROR;
//             else
//                 banner->matrix[i][strcspn(banner->matrix[i], "\n")] = '\0';
//         }

//         fclose(file);
//     }
//     else
//         rc = ERROR;

//     return rc;
// }
