#ifndef TETRIS_DEFINES_H_
#define TETRIS_DEFINES_H_

#define WIN_INIT()          \
  {                         \
    initscr();              \
    noecho();               \
    curs_set(0);            \
    cbreak();               \
    keypad(stdscr, TRUE);   \
    signal(SIGWINCH, NULL); \
    set_escdelay(0);        \
  }

#define GET_USER_INPUT getch()
#define MVPRINTW(y, x, ...) \
  mvprintw(SCREEN_Y + (y), SCREEN_X + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(SCREEN_Y + (y), SCREEN_X + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(SCREEN_Y + (y), SCREEN_X + (x), ' ')

#define BOARD_W 10
#define BOARD_H 20
#define INFO_BLOCK_W 14
#define LOGO_H 5
#define LOGO_W 22
#define OVER_H 11
#define OVER_W 19

#define SCREEN_X ((getmaxx(stdscr) - BOARD_W - INFO_BLOCK_W - 4) / 2)
#define SCREEN_Y ((getmaxy(stdscr) - BOARD_H - 2) / 2)
#define BOARD_X 2
#define BOARD_Y 1
#define START_X 5
#define START_Y 0

#define INITIAL_SPEED_NS 500000000L
#define DELTA_SPEED_NS 55000000L

#define ESCAPE 27
#define ENTER_KEY 10
#define SPACE 32
#define DOWN_KEY 0402
#define UP_KEY 0403
#define LEFT_KEY 0404
#define RIGHT_KEY 0405

#define X 1
#define Y 0
#define SHAPES 7
#define DOTS 4
#define COORDS 2

#define COLOR_ORANGE 8
#define COLOR_LIGHT_YELLOW 9
#define COLOR_LIGHT_BLUE 10
#define SHAPE_COLOR(id) (id + 1)

#define SOLID_BLOCK (' ' | A_REVERSE)

#define RANDOM_FIGURE (random() % 7)

#define SAVE_DIR "/Tetris"
#define SAVE_FILE "/tetris.save"

#endif  // TETRIS_DEFINES_H_
