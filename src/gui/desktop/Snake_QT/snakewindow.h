#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QGridLayout>
#include <QMainWindow>

#include "../../../brick_game/snake/controller_qt.h"
#include "gamefield.h"
#include "gameoverfield.h"
#include "textfield.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SnakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  SnakeWindow(QWidget *parent = nullptr);
  ~SnakeWindow();
 signals:
  void buttStartClicked();
  void snakeWindowClosed();

 private:
  Ui::MainWindow *ui;
  s21::Controller *m_controller;
  GameField *m_game_field;
  TextField *m_text_field;
  GameOverField *m_over_game_field;
  QPushButton *butt_exit, *butt_start;
  QWidget *m_central_widget;
  QGridLayout *m_grid_layout;
  void closeEvent(QCloseEvent *event);
};
#endif  // SNAKEWINDOW_H
