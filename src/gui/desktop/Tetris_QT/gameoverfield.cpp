#include "gameoverfield.h"

#include "gamefield.h"

TetrisGameOverField::TetrisGameOverField() {
  setFixedSize(302, 602);
  m_text = "";
}

void TetrisGameOverField::paintEvent(QPaintEvent *e1) {
  Q_UNUSED(e1);
  QPainter painter;
  painter.begin(this);
  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");
  painter.setFont(QFont("Calculator", 70, 700));
  painter.setPen(QColorConstants::Black);
  painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, m_text);
  painter.end();
}

void TetrisGameOverField::gameOverFieldSlot(QString text) {
  m_text = text;
  repaint();
}
