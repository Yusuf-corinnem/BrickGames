#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QApplication>
#include <QDesktopServices>
#include <QMainWindow>
#include <QPushButton>
#include <QUrl>

#include "../Snake_QT/snakewindow.h"
#include "../Tetris_QT/tetriswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuWindow;
}
QT_END_NAMESPACE

class MenuWindow : public QMainWindow {
  Q_OBJECT

 public:
  MenuWindow(QWidget *parent = nullptr);
  ~MenuWindow();

 private:
  Ui::MenuWindow *ui;
  SnakeWindow *snake_window;
  TetrisWindow *tetris_window;
  QPushButton *m_snake_button, *m_tetris_button, *m_exit_button, *m_developer;
  bool open_snake = false, open_tetris = false;
  void createSnakeButton();
  void createTetrisButton();
  void createExitButton();
  void createDeveloperButton();
  void openSnakeWindow();
  void openTetrisWindow();
  void showMenuWindow();
};
#endif  // MENUWINDOW_H
