#ifndef GAMEOVERFIELD_H
#define GAMEOVERFIELD_H

#include <QPainter>
#include <QWidget>

class GameOverField : public QWidget {
 public:
  GameOverField();

 protected:
  void paintEvent(QPaintEvent *e1) override;

 private:
  QString m_text;
 public slots:
  void gameOverFieldSlot(QString text);
};

#endif  // GAMEOVERFIELD_H
