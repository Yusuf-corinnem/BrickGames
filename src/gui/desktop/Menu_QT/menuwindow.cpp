#include "menuwindow.h"

#include "./ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuWindow) {
  ui->setupUi(this);
  setFixedSize(300, 300);

  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");

  createSnakeButton();
  connect(m_snake_button, &QPushButton::clicked, this,
          &MenuWindow::openSnakeWindow);

  createTetrisButton();
  connect(m_tetris_button, &QPushButton::clicked, this,
          &MenuWindow::openTetrisWindow);

  createExitButton();
  connect(m_exit_button, &QPushButton::clicked, this, &MenuWindow::close);

  createDeveloperButton();
  connect(m_developer, &QPushButton::clicked, this, [&]() {
    QDesktopServices::openUrl(QUrl("https://github.com/Yusuf-corinnem"));
  });
}

void MenuWindow::createSnakeButton() {
  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");
  m_snake_button = new QPushButton("SNAKE", this);
  m_snake_button->setFont(QFont("Calculator", 30, 700));
  m_snake_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 137, 109);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(169, 184, 130);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 137, 109);"
      "}");
  m_snake_button->setGeometry(70, 35, 160, 37);
}

void MenuWindow::createTetrisButton() {
  m_tetris_button = new QPushButton("TETRIS", this);
  m_tetris_button->setFont(QFont("Calculator", 30, 700));
  m_tetris_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 137, 109);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(169, 184, 130);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 137, 109);"
      "}");
  m_tetris_button->setGeometry(70, 85, 160, 37);
}

void MenuWindow::createExitButton() {
  m_exit_button = new QPushButton{"CLOSE", this};
  m_exit_button->setFont(QFont("Calculator", 30, 700));
  m_exit_button->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: rgb(124, 137, 109);"
      "border: 1px solid black;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(169, 184, 130);"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(124, 137, 109);"
      "}");
  m_exit_button->setGeometry(70, 135, 160, 37);
}

void MenuWindow::createDeveloperButton() {
  m_developer = new QPushButton{"DESIGNED BY\nCORINNEM", this};
  m_developer->setFont(QFont("Calculator", 18, 700));
  m_developer->setStyleSheet(
      "QPushButton {"
      "color: black;"
      "background-color: transparent;"
      "}"
      "QPushButton:hover {"
      "background-color: transparent;"
      "color: rgb(124, 137, 109);"
      "}"
      "QPushButton:pressed {"
      "background-color: transparent;"
      "}"
      "QPushButton {"
      "text-decoration: underline;"
      "}");
  m_developer->setGeometry(100, 200, 100, 37);
}

void MenuWindow::openSnakeWindow() {
  snake_window = new SnakeWindow(this);
  connect(snake_window, &SnakeWindow::snakeWindowClosed, this,
          &MenuWindow::showMenuWindow);
  open_snake = true;
  snake_window->show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(160, 172, 134));
  snake_window->setAutoFillBackground(true);
  snake_window->setPalette(pal);
  this->hide();
}

void MenuWindow::openTetrisWindow() {
  tetris_window = new TetrisWindow(this);
  connect(tetris_window, &TetrisWindow::tetrisWindowClosed, this,
          &MenuWindow::showMenuWindow);
  open_tetris = true;
  tetris_window->show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(160, 172, 134));
  tetris_window->setAutoFillBackground(true);
  tetris_window->setPalette(pal);
  this->hide();
}

void MenuWindow::showMenuWindow() {
  if (open_snake) {
    delete snake_window;
    open_snake = false;
  }
  if (open_tetris) {
    delete tetris_window;
    open_tetris = false;
  }
  this->show();
}

MenuWindow::~MenuWindow() { delete ui; }
