#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QPainter>
#include <QWidget>

class TextField : public QWidget {
 public:
  TextField(int record);

 protected:
  void paintEvent(QPaintEvent *e) override;

 private:
  QString m_text;
 public slots:
  void changeTextSlot(QString text);
};

#endif  // TEXTFIELD_H
