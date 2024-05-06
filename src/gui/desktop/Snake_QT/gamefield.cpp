#include "gamefield.h"

#include <QDebug>
#include <QProcess>

GameField::GameField() {
  setFixedSize(306, 606);
  setFocusPolicy(Qt::StrongFocus);
  startNewGame();
}

void GameField::onButtStartClicked() {
  if (flag_game_over) {
    startNewGame();
    return;
  }
  if (!m_move_snake_timer->isActive()) {
    m_move_snake_timer->start(controller->getSpeed());
    flag_new_game = false;
  }
}

void GameField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter;
  painter.begin(this);
  QImage image_background(":/new/prefix1/background.png");
  QImage image(":/new/prefix1/pixil-frame-1.png");
  painter.drawImage(0, 0, image_background, 0, 0, 306, 606, Qt::AutoColor);
  if (flag_game_over) return;
  // draw snake
  for (int i = 0; i < controller->getBodySnake().size(); ++i) {
    painter.drawImage((controller->getBodySnake()[i].x - 1) * 30 + 2,
                      (controller->getBodySnake()[i].y - 1) * 30 + 2, image, 2,
                      2, 30, 30, Qt::AutoColor);
  }

  painter.drawImage((controller->getApple().x - 1) * 30 + 2,
                    (controller->getApple().y - 1) * 30 + 2, image, 2, 2, 30,
                    30, Qt::AutoColor);

  painter.end();
}

void GameField::keyPressEvent(QKeyEvent *e) {
  if (!flag_new_game && !flag_game_over) {
    if (e->key() == 'p' || e->key() == 'P') {
      flag_pause = !flag_pause;
      if (flag_pause)
        m_move_snake_timer->stop();
      else
        m_move_snake_timer->start(controller->getSpeed());
      if (!controller->getGameOver() || !controller->getGameWin())
        setGameStatus();
    }
    if (e->key() == 'q' || e->key() == 'Q') {
      if (!controller->getGameOver() || !controller->getGameWin()) gameOver();
      return;
    }
    if (e->key() == Qt::Key_Left && !flag_key && !flag_pause) {
      controller->changeDirection('a', controller->getDirection());
      flag_key = true;
    }
    if (e->key() == Qt::Key_Right && !flag_key && !flag_pause) {
      controller->changeDirection('d', controller->getDirection());
      flag_key = true;
    }
    if (e->key() == Qt::Key_Up && !flag_key && !flag_pause) {
      controller->changeDirection('w', controller->getDirection());
      m_move_snake_timer->stop();
      m_move_snake_timer->start(controller->getSpeed());
      flag_key = true, flag_boost = true;
    }
  } else if ((e->key() == 'a' || e->key() == 'A')) {
    startNewGame();
    return;
  }
}

void GameField::setGameStatus() {
  QString pause_text = "\n\nPAUSE - 'P'";
  QString select_text = "\nQUIT - 'Q'";
  if (flag_pause) pause_text = "\n\nUNPAUSE - 'P'";
  if (controller->getGameOver()) select_text = "\nAGAIN - 'A'";
  QString text = "RECORD: " + QString::number(controller->getRecord()) +
                 "\nSCORE: " + QString::number(controller->getLength() - 4) +
                 "\nLEVEL: " + QString::number(controller->getLevel()) +
                 pause_text + select_text;
  emit changeTextSignal(text);
}

void GameField::gameOver() {
  flag_new_game = false, flag_game_over = true;
  controller->setGameOver(true);

  if (controller->getGameWin())
    emit gameOverFieldSignal("!VICTORY!");
  else
    emit gameOverFieldSignal("GAME OVER");
  setGameStatus();
  m_move_snake_timer->stop();
  delete controller;
  delete m_move_snake_timer;
}

void GameField::startNewGame() {
  flag_pause = false, flag_new_game = true, flag_game_over = false;
  controller =
      new s21::Controller(m_current_path.toStdString() + m_path.toStdString());
  controller->setGameOver(false);
  m_move_snake_timer = new QTimer();
  connect(m_move_snake_timer, &QTimer::timeout, this,
          &GameField::move_snake_slot);
  m_move_snake_timer->stop();

  emit gameOverFieldSignal("");
  setGameStatus();
}

void GameField::move_snake_slot() {
  controller->setMove(controller->getDirection(), controller->getApple(),
                      m_current_path.toStdString() + m_path.toStdString());
  setGameStatus();
  if (controller->checkCollision(12, 22))
    gameOver();
  else {
    repaint();
    if (flag_boost) {
      controller->setSpeed(controller->getSpeed() + 400);
      flag_boost = false;
    }
    m_move_snake_timer->stop();
    m_move_snake_timer->start(controller->getSpeed());
    flag_key = false;
  }
}
