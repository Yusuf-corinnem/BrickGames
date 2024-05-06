#include "snake/console_view.h"
#include "tetris/frontend_tetris.h"

int main() {
  initscr();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  bool exit = false;
  while (!exit) {
    clear();
    printw(
        "MENU:\nPress '1' to play Tetris\nPress '2' to play Snake\nPress '3' "
        "to Exit\n");
    int choice = getch();
    if (choice == '1') {
      clear();
      consoleTetris();
    } else if (choice == '2') {
      clear();
      s21::ConsoleView::consoleSnake();
    } else if (choice == '3')
      exit = true;
  }
  endwin();
  return 0;
}