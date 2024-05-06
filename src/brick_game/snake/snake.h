#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define HEIGHT 22
#define WIDTH 12

namespace s21 {
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Coord {
  int x;
  int y;

  Coord(int X, int Y) : x(X), y(Y) {}

  bool operator==(const Coord &other) const {
    return x == other.x && y == other.y;
  }
};

class Snake {
  friend class Game;

 public:
  Snake(std::string path)
      : length(4), speed(660), level(0), game_over(false), game_win(false) {
    record(path);
    body_snake.push_back({WIDTH / 2, HEIGHT / 2});
    for (int i = 0; i < 3; ++i) {
      body_snake.push_back({WIDTH / 2, HEIGHT / 2 - (i + 1)});
    }
  }

  // GETTERS
  const std::vector<Coord> &getBodySnake() const { return body_snake; }

  int getLength() const { return length; }

  int getRecord() const { return record_length; }

  int getLevel() const { return level; }

  int getSpeed() const { return speed; }

  Direction &getDirection() { return direction; }

  int getGameOver() { return game_over; }

  void setGameOver(bool other) { game_over = other; }

  int getGameWin() { return game_win; }

  // SETTERS
  void setHeadBodySnake(int x, int y) {
    body_snake.back().x = x, body_snake.back().y = y;
  }

  void setSpeed(int other_speed) { speed = other_speed; }

  void setMove(Direction direction, Coord &apple, std::string path) {
    move(direction, apple, path);
  }

  bool checkCollision(int width, int height) {
    Coord head = body_snake.back();
    // проверка столкновения со стенами
    if ((head.x <= 0 || head.x >= width - 1) ||
        (head.y <= 0 || head.y >= height - 1)) {
      game_over = true;
      return true;
    }
    // проверка столкновения с собой
    for (auto itr = body_snake.begin(); itr != body_snake.end() - 1; ++itr) {
      if (*itr == head) {
        game_over = true;
        return true;
      }
    }

    if (length == (HEIGHT - 2) * (WIDTH - 2)) {
      game_win = true, game_over = true;
      return true;
    }

    return false;
  }

  void changeDirection(int key, Direction &current) {
    if (key == 'q' || key == 'Q') game_over = true;
    if (key == 'w') {
      if (speed >= 400) speed -= 400;
    }
    if (key == 'a') {
      if (current == DOWN) {
        current = RIGHT;
      } else if (current == RIGHT) {
        current = UP;
      } else if (current == LEFT) {
        current = DOWN;
      } else if (current == UP) {
        current = LEFT;
      }
    }
    if (key == 'd') {
      if (current == DOWN) {
        current = LEFT;
      } else if (current == RIGHT) {
        current = DOWN;
      } else if (current == LEFT) {
        current = UP;
      } else if (current == UP) {
        current = RIGHT;
      }
    };
  }

 protected:
  void record(std::string str) {
    std::ifstream inf(str);
    inf >> record_length;
    if (length - 4 >= record_length) {
      std::ofstream outf(str);
      outf << length - 4;
      record_length = length - 4;
    }
  }

  void checkGameOver() {
    if (length == (HEIGHT - 2) * (WIDTH - 2)) game_win = true, game_over = true;
  }

  // MOVE LOGIC
  void move(Direction direction, Coord &apple, std::string path) {
    Coord head = body_snake.back();
    switch (direction) {
      case UP:
        head.y--;
        break;
      case DOWN:
        head.y++;
        break;
      case LEFT:
        head.x--;
        break;
      case RIGHT:
        head.x++;
        break;
    }

    body_snake.push_back(head);
    body_snake.erase(body_snake.begin());

    if (head.x == apple.x && head.y == apple.y) {
      growth();
      record(path);
      checkSpeed();
      changeAppleCoor(apple);
    }
  }

  void changeSpeed() { speed -= 25, level++; }

  void checkSpeed() {
    if (length >= 9 && length <= 54 && length % 5 == 4) {
      changeSpeed();
    }
  }

  // APPLE GENERATION LOGIC
  bool compareCoordSnakeApple(Coord apple) {
    for (auto itr = body_snake.begin(); itr != body_snake.end(); ++itr) {
      if (*itr == apple) return true;
    }
    return false;
  }

  void changeAppleCoor(Coord &apple) {
    do {
      apple.x = rand() % (WIDTH - 2) + 1;
      apple.y = rand() % (HEIGHT - 2) + 1;
    } while (compareCoordSnakeApple(apple));
  }

  void growth() {
    body_snake.insert(body_snake.begin(), body_snake.front());
    ++length;
  }

 protected:
  std::vector<Coord> body_snake;
  int length = 0;
  int record_length = 0;
  int speed = 660;
  int level = 0;
  bool game_over = false;
  bool game_win = false;
  Direction direction = UP;
};
}  // namespace s21

#endif  // _SNAKE_H_
