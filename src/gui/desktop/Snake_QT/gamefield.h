#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QFontDatabase>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/controller_qt.h"

#define STRING(x) #x
#define XSTRING(x) STRING(x)

class GameField : public QWidget {
  friend class SnakeWindow;
  Q_OBJECT
 public:
  GameField();

 protected:
  s21::Controller *controller;
  QString m_current_path = XSTRING(THREE_LEVELS_UP);
  QString m_path = "/brick_game/snake/record.txt";
  bool flag_key = false, flag_boost = false, flag_new_game = false,
       flag_pause = false, flag_game_over = false;

 private:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void setGameStatus();
  QTimer *m_move_snake_timer;
  s21::Coord *m_apple;
  void gameOver();
  void startNewGame();
 public slots:
  void onButtStartClicked();
 private slots:
  void move_snake_slot();
 signals:
  void changeTextSignal(QString text);
  void gameOverFieldSignal(QString text);
};

#endif  // GAMEFIELD_H
