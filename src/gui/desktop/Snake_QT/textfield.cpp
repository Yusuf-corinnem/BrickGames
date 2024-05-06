#include "textfield.h"

#include "gamefield.h"

TextField::TextField(int record) {
  setFixedSize(165, 600);
  m_text = "RECORD: " + QString::number(record) +
           "\nSCORE: 0\nLEVEL: 0\n\nPAUSE - 'P'\nQUIT - 'Q'";
}

void TextField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter;
  painter.begin(this);
  QImage image_background(":/new/prefix1/color.png");
  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");
  painter.drawImage(0, 0, image_background, 0, 0, 165, 600, Qt::AutoColor);
  painter.setPen(QColorConstants::Black);
  painter.setFont(QFont("Calculator", 35, 700));
  painter.drawText(QRect(0, 0, width(), height()), Qt::AlignHCenter, m_text);
  painter.end();
}

void TextField::changeTextSlot(QString text) {
  m_text = text;
  repaint();
}
