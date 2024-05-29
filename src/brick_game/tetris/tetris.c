#include "tetris.h"

int main() {
  initscr();
  setlocale(LC_ALL, "");
  noecho();
  print_overlay();
  refresh();
  getch();
  endwin();
  return 0;
}
