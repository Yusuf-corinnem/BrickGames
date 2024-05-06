#ifndef _CONSOLE_VIEW_H_
#define _CONSOLE_VIEW_H_

#include <ncurses.h>
#include <unistd.h>

#include <ctime>

#include "../../../brick_game/snake/controller_qt.h"

namespace s21 {
class ConsoleView {
 public:
  static void consoleSnake() {
    bool game_over = false;
    printw("START GAME: 'S'\n");
    printw("QUIT: 'Q'\n");
    while (!game_over) {
      int key = getch();
      if (key == 's' || key == 'S')
        s21::ConsoleView::running();
      else if (key == 'q' || key == 'Q')
        game_over = true;
    }
  }

 private:
  static void running() {
    s21::Controller controller("brick_game/snake/record.txt");
    srand(time(0));
    gameLoop(controller);
    finalText(controller);
  }

  static void drawField(const std::vector<s21::Coord> &snake_body,
                        const s21::Coord &apple, s21::Controller &controller,
                        int pause) {
    clear();

    // Отрисовка границ поля
    for (int i = -1; i < HEIGHT; ++i) {
      mvaddch(i, 0, '|');
      mvaddch(i, WIDTH - 1, '|');
    }

    for (int i = 0; i < WIDTH; ++i) {
      mvaddch(0, i, '-');
      mvaddch(HEIGHT - 1, i, '-');
    }

    // Отрисовка змейки
    for (const auto &coord : snake_body) {
      if (coord == snake_body.back()) {
        mvaddch(coord.y, coord.x, '&');
      } else
        mvaddch(coord.y, coord.x, '*');
    }

    // Отрисовка яблока
    mvaddch(apple.y, apple.x, 'o');

    // Отрисовка рекорда и счета
    mvprintw(1, WIDTH + 3, "RECORD: %d", controller.getRecord());

    mvprintw(3, WIDTH + 3, "SCORE: %d", controller.getLength() - 4);

    mvprintw(5, WIDTH + 3, "LEVEL: %d", controller.getLevel());

    if (!pause)
      mvprintw(7, WIDTH + 3, "PRESS 'P' FOR PAUSE");
    else
      mvprintw(7, WIDTH + 3, "PRESS 'P' FOR UNPAUSE");

    mvprintw(9, WIDTH + 3, "PRESS 'Q' TO EXIT");

    mvaddch(HEIGHT - 1, WIDTH - 1, '-');

    refresh();
  }

  static void update(const int key, s21::Controller &controller) {
    if (key == 'q') controller.changeDirection('q', controller.getDirection());
    if (key == KEY_LEFT)
      controller.changeDirection('a', controller.getDirection());
    if (key == KEY_RIGHT)
      controller.changeDirection('d', controller.getDirection());
    if (key == KEY_UP) {
      char str[1024] = "\0";
      scanw(str);
      controller.changeDirection('w', controller.getDirection());
    }
  }

  static void gameLoop(s21::Controller &controller) {
    int pause = 0;
    while (!controller.getGameOver()) {
      int key = getch();
      if (key == 'p') {
        pause = !pause;
      }
      update(key, controller);
      if (!controller.getGameOver()) {
        if (!pause)
          controller.setMove(controller.getDirection(), controller.getApple(),
                             "brick_game/snake/record.txt");
        controller.checkCollision(WIDTH, HEIGHT);
        if (!controller.getGameOver()) {
          drawField(controller.getBodySnake(), controller.getApple(),
                    controller, pause);
          usleep(controller.getSpeed() * 1000);
          if (key == KEY_UP) controller.setSpeed(controller.getSpeed() + 400);
        }
      }
    }
  }

  static void finalText(s21::Controller &controller) {
    if (controller.getGameOver()) {
      mvprintw(11, WIDTH + 3, "START GAME: 'S'");
      if (controller.getGameWin())
        mvprintw(13, WIDTH + 3, "PLAYER WIN!");
      else
        mvprintw(13, WIDTH + 3, "GAME OVER");
      mvaddch(HEIGHT - 1, WIDTH - 1, '-');
    }
  }
};
}  // namespace s21

#endif  // _CONSOLE_VIEW_H_