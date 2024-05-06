#include "../brick_game/snake/controller_qt.h"
#include "gtest/gtest.h"

#define PATH "../brick_game/snake/record.txt"

void compareDirections(int key, s21::Controller *snake, s21::Direction dir) {
  snake->changeDirection(key, snake->getDirection());
  EXPECT_EQ(snake->getDirection(), dir);
}

TEST(ChangeDirection, Right) {
  s21::Controller *snake = new s21::Controller(PATH);

  compareDirections('d', snake, s21::RIGHT);
  compareDirections('d', snake, s21::DOWN);
  compareDirections('d', snake, s21::LEFT);
  compareDirections('d', snake, s21::UP);
  delete snake;
}

TEST(ChangeDirection, Left) {
  s21::Controller *snake = new s21::Controller(PATH);

  compareDirections('a', snake, s21::LEFT);
  compareDirections('a', snake, s21::DOWN);
  compareDirections('a', snake, s21::RIGHT);
  compareDirections('a', snake, s21::UP);
  delete snake;
}

TEST(EatApple, Eat) {
  s21::Controller *snake = new s21::Controller(PATH);
  snake->setHeadBodySnake(1, 2);
  s21::Coord *apple = new s21::Coord(snake->getApple());
  apple->x = 1, apple->y = 1;
  snake->setMove(s21::UP, *apple, PATH);
  EXPECT_EQ(snake->getLength(), 5);
  delete snake;
  delete apple;
}

TEST(Move, Move) {
  s21::Controller *snake = new s21::Controller(PATH);
  snake->setHeadBodySnake(5, 10);

  snake->setMove(snake->getDirection(), snake->getApple(), PATH);
  EXPECT_EQ(snake->getBodySnake().back().y, 9);

  for (int i = 0; i < 2; ++i) {
    snake->changeDirection('d', snake->getDirection());
    snake->setMove(snake->getDirection(), snake->getApple(), PATH);
    if (i == 0)
      EXPECT_EQ(snake->getBodySnake().back().x, 6);
    else if (i == 1)
      EXPECT_EQ(snake->getBodySnake().back().y, 10);
    else
      EXPECT_EQ(snake->getBodySnake().back().x, 5);
  }
  delete snake;
}

TEST(CheckCollision, CheckBounds) {
  s21::Controller *snake = new s21::Controller(PATH);
  snake->setHeadBodySnake(5, 1);
  snake->setMove(snake->getDirection(), snake->getApple(), PATH);
  EXPECT_EQ(snake->checkCollision(12, 22), true);
  delete snake;
}