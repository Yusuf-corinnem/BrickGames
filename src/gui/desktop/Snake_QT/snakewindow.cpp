#include "snakewindow.h"

#include "./ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setFixedSize(530, 660);
  setWindowTitle("Snake");
  QFontDatabase::addApplicationFont(":/new/prefix1/Calculator.ttf");
  m_game_field = new GameField();
  m_controller =
      new s21::Controller(m_game_field->m_current_path.toStdString() +
                          m_game_field->m_path.toStdString());
  m_text_field = new TextField(m_game_field->controller->getRecord());
  m_over_game_field = new GameOverField();

  connect(m_game_field, &GameField::changeTextSignal, m_text_field,
          &TextField::changeTextSlot);
  connect(m_game_field, &GameField::gameOverFieldSignal, m_over_game_field,
          &GameOverField::gameOverFieldSlot);

  m_central_widget = new QWidget();
  m_grid_layout = new QGridLayout();

  m_grid_layout->addWidget(m_game_field, 0, 0);
  m_grid_layout->addWidget(m_text_field, 0, 1);
  m_grid_layout->addWidget(m_over_game_field, 0, 0);

  m_central_widget->setLayout(m_grid_layout);
  setCentralWidget(m_central_widget);

  butt_start = new QPushButton{"START", m_central_widget};
  butt_start->setFont(QFont("Calculator", 30, 700));
  butt_start->setStyleSheet(
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
  butt_start->setGeometry(347, 320, 165, 37);
  connect(butt_start, &QPushButton::clicked, m_game_field,
          &GameField::onButtStartClicked);

  butt_exit = new QPushButton{"CLOSE", m_central_widget};
  butt_exit->setFont(QFont("Calculator", 30, 700));
  butt_exit->setStyleSheet(
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
  butt_exit->setGeometry(347, 370, 165, 37);

  connect(butt_exit, &QPushButton::clicked, this, &SnakeWindow::close);
}

void SnakeWindow::closeEvent(QCloseEvent *event) {
  if (!m_game_field->flag_game_over) m_game_field->gameOver();
  delete m_game_field;
  delete m_controller;
  delete m_text_field;
  delete m_over_game_field;
  emit snakeWindowClosed();
  event->accept();
}

SnakeWindow::~SnakeWindow() { delete ui; }
