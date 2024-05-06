CC = gcc
CPP = g++
FLAGS = -Wall -Werror -Wextra
CPPFLAGS = -std=c++17 -lstdc++

TETRIS_DIR = brick_game/tetris
GUI_DIR = gui/cli/tetris
TESTS_DIR = tests

SOURCE_TETRIS = $(TETRIS_DIR)/functions/*.cc $(GUI_DIR)/*.cc
HEADERS_TETRIS = $(TETRIS_DIR)/*.h $(GUI_DIR)/*.h
SOURCE_TEST = $(TETRIS_DIR)/functions/*.cc $(TESTS_DIR)/*.cc

CONSOLE_MENU_EXEC = console_menu

CLANG_FILES = **/**/*.h **/**/*.cc **/**/**/*.cpp **/**/**/*.cc **/**/**/*.h tests/*.cc

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lsubunit
else
	CHECK_FLAGS = -lgtest
endif

all: console_menu install

# CONSOLE
console_menu:
	$(CC) $(FLAGS) -lncurses $(CPPFLAGS) $(SOURCE_TETRIS) gui/cli/console_menu.cc -o $(CONSOLE_MENU_EXEC)

# DESKTOP
install:
	cmake -B gui/desktop/build "gui/desktop/Menu_QT"
	cmake --build gui/desktop/build --target Menu_QT --parallel 8
	cp -R gui/desktop/build/Menu_QT.app ~/Desktop

# RUN
run_console:
	./$(CONSOLE_MENU_EXEC)

run_desktop:
	open ~/Desktop/Menu_QT.app

# OTHER
test:
	@$(CPP) $(FLAGS) $(CPPFLAGS) $(SOURCE_TEST) -o test $(CHECK_FLAGS)
	@./test

gcov_report:
	@$(CPP) $(FLAGS) --coverage $(CPPFLAGS) $(SOURCE_TEST) -o test $(CHECK_FLAGS)
	./test
	@lcov --ignore-errors inconsistent -t "test" -o test.info -c -d .
	@lcov --remove test.info '/usr/*' -o test.info
	@genhtml -o report test.info
	@open ./report/index.html
	@rm -rf *.gcno *.gcda *.info test

dist: install
	@mkdir archiv
	@cp -r $(SOURCE_TETRIS) $(HEADERS_TETRIS) archiv
	@tar -cf tetris.tar archiv
	@rm -rf archiv

dvi:
	open ../README_RUS.md

install_brew:
	@git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	@cd ~
	@eval "$(goinfre/homebrew/bin/brew shellenv)"
	@brew update --force --quiet
	@chmod -R go-w "$(brew --prefix)/share/zsh"

install_lcov:
	@cd ~
	@brew install lcov

style_check:
	clang-format --style=Google -n $(CLANG_FILES)

clang:
	@clang-format --style=Google -i $(CLANG_FILES)
	
valgrind:
	docker build -t tetris .
	docker run --name stock tetris

clear:
	docker rm stock
	docker rmi tetris

uninstall: clean

clean:
	@rm -rf $(CONSOLE_MENU_EXEC) gui/desktop/build ~/Desktop/Menu_QT.app gui/desktop/build_snake ~/Desktop/Snake_QT.app *.o *.a tetris.tar
	@rm -rf *.gcno *.gcda *.info test report

.PHONY: console_menu install test gcov_report dist