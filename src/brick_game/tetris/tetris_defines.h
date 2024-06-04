#ifndef BRICK_GAME_TETRIS_TETRIS_DEFINES_H_
#define BRICK_GAME_TETRIS_TETRIS_DEFINES_H_

#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define GET_USER_INPUT getch()

#define BOARD_W 10
#define BOARD_H 20
#define INFO_BLOCK_W 14

#define SCREEN_X ((getmaxx(stdscr) - BOARD_W - INFO_BLOCK_W - 4) / 2)
#define SCREEN_Y ((getmaxy(stdscr) - BOARD_H - 2) / 2)
#define BOARD_X 2
#define BOARD_Y 1

#define MVPRINTW(y, x, ...) \
  mvprintw(SCREEN_Y + (y), SCREEN_X + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(SCREEN_Y + (y), SCREEN_X + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(SCREEN_Y + (y), SCREEN_X + (x), ' ')

#define START_X 5
#define START_Y 0
#define INITIAL_TIMEOUT 150

#define SUCCESS 0
#define ERROR 1

#define NO_INPUT -1

#define ESCAPE 27
#define ENTER_KEY 10
#define SPACE 32

#define X 1
#define Y 0

#define COLOR_ORANGE 8
#define SHAPE_COLOR(id) (id + 1)

#define SOLID_BLOCK (' ' | A_REVERSE)

#define RANDOM_FIGURE (random() % 7)

#endif  // BRICK_GAME_TETRIS_TETRIS_DEFINES_H_
