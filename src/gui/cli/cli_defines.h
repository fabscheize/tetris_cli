#ifndef BRICK_GAME_GUI_CLI_CLI_DEFINES_H_
#define BRICK_GAME_GUI_CLI_CLI_DEFINES_H_

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
// #define PRINT_FROG(x, y) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x),
// "@")
// #define BOARDS_BEGIN ((getmaxx(stdscr) + BOARD_W + INFO_BLOCK_W + 4) / 2)

#define BOARD_X ((getmaxx(stdscr) - BOARD_W - INFO_BLOCK_W - 4) / 2)
#define BOARD_Y ((getmaxy(stdscr) - BOARD_H - 2) / 2)
// #define BOARD_X 2
// #define BOARD_Y 2

#define MVPRINTW(y, x, ...) mvprintw(BOARD_Y + (y), BOARD_X + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARD_Y + (y), BOARD_X + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARD_Y + (y), BOARD_X + (x), ' ')

#define YOU_WON "tests/game_progress/you_won.txt"
#define YOU_LOSE "tests/game_progress/you_lose.txt"
#define LEVEL_DIR "tests/levels/level_"
#define INTRO_MESSAGE "Press ENTER to start!"
#define INTRO_MESSAGE_LEN 21
#define LEVEL_CNT 5
#define LEVELNAME_MAX 25

#define MAX_WIN_COUNT 10

#define ROWS_MAP 21
#define COLS_MAP 90

// #define FROGSTART_X      (BOARD_M / 2)
// #define FROGSTART_Y      (BOARD_N)
#define INITIAL_TIMEOUT 150

#define MAP_PADDING 3
// #define BOARD_N     (ROWS_MAP + MAP_PADDING * 2)

#define BANNER_N 10
#define BANNER_M 100

#define SUCCESS 0
#define ERROR 1

#define NO_INPUT -1

#define ESCAPE 27
#define ENTER_KEY 10

#endif  // BRICK_GAME_GUI_CLI_CLI_DEFINES_H_
