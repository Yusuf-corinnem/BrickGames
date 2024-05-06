#include "gameoverfield.h"

#include "gamefield.h"

GameOverField::GameOverField() {
  setFixedSize(302, 602);
  m_text = "";
  this->setWindowFlags(Qt::FramelessWindowHint);
  this->setAttribute(Qt::WA_TranslucentBackground, true);
  this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
}

void GameOverField::paintEvent(QPaintEvent *e1) {
  Q_UNUSED(e1);
  QPainter painter;
  painter.begin(this);
  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");
  painter.setFont(QFont("Calculator", 70, 700));
  painter.setPen(QColorConstants::Black);
  painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, m_text);
  painter.end();
}

void GameOverField::gameOverFieldSlot(QString text) {
  m_text = text;
  repaint();
}
