#include "tetris.h"

int main() {
  initscr();
  noecho();
  print_overlay();

  getch();
  endwin();
  return 0;
}
