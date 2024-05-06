#ifndef _CONTROLLER_QT_H_
#define _CONTROLLER_QT_H_

#include <memory>

#include "snake.h"

namespace s21 {
class Controller {
 public:
  Controller(std::string path) : snake(new s21::Snake(path)) {
    apple = new s21::Coord(3, 3);
  }

  ~Controller() { delete apple; }

  const std::vector<s21::Coord> &getBodySnake() const {
    return snake->getBodySnake();
  }

  void setHeadBodySnake(int x, int y) { snake->setHeadBodySnake(x, y); }

  void changeDirection(int key, Direction &current) {
    snake->changeDirection(key, current);
  }

  bool checkCollision(int width, int height) {
    return snake->checkCollision(width, height);
  }

  // GETTERS
  Direction &getDirection() { return snake->getDirection(); }

  int getSpeed() const { return snake->getSpeed(); }

  int getRecord() const { return snake->getRecord(); }

  int getLength() const { return snake->getLength(); }

  int getLevel() const { return snake->getLevel(); }

  Coord &getApple() { return *apple; }

  int getGameOver() { return snake->getGameOver(); }

  void setGameOver(bool other) { snake->setGameOver(other); }

  int getGameWin() { return snake->getGameWin(); }

  // SETTERS
  void setMove(Direction direction, Coord &apple, std::string path) {
    return snake->setMove(direction, apple, path);
  }

  void setSpeed(int other_speed) { snake->setSpeed(other_speed); }

 private:
  std::unique_ptr<s21::Snake> snake;
  s21::Coord *apple;
};
}  // namespace s21

#endif  // _CONTROLLER_QT_H_
