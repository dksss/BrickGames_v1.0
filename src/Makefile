CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11

FRONTEND_DIR := gui/cli
BACKEND_DIR := brick_game/tetris
TEST_DIR := tests
BUILD_DIR := ../build
INSTALL_DIR := ../Install
TARGET_DIR_NAME := BrickGame_v1.0_by_jodyvole
DIST_DIR := ../dist
DOCS_DIR := ../docs

OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	TEST_LIB := -lcheck -lm
	OPEN := openDIST_TET_DIR := $(DIST_DIR)/BrickGame_v1.0
else ifeq ($(OS), Linux)
	TEST_LIB := -lcheck -lm -lsubunit
	OPEN := google-chrome
endif

.PHONY := all install uninstall clean dvi dist clang valgrind gcov_report rebuild

all: clang test install

install: tetris.a
	mkdir $(INSTALL_DIR)
	mkdir $(INSTALL_DIR)/$(TARGET_DIR_NAME)
	$(CC) $(CFLAGS) -o $(INSTALL_DIR)/$(TARGET_DIR_NAME)/TETRIS_GAME gui/cli/*.c -lncurses -L$(BUILD_DIR) -l:tetris.a

tetris.a:
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BACKEND_DIR)/*.c -c
	ar rcs tetris.a *.o
	ranlib tetris.a
	rm *.o
	mv tetris.a $(BUILD_DIR)

uninstall:
	rm -rf $(INSTALL_DIR) $(BUILD_DIR)

rebuild: uninstall install

dvi:
	doxygen

open_docs:
	$(OPEN) ../docs/html/index.html

dist: dvi
	mkdir $(DIST_DIR)
	tar cf $(DIST_DIR)/BrickGames_v1.0.tar ./brick_game ./gui ./brickGame_API.h ../docs

test:
	$(CC) $(CFLAGS) -o test $(BACKEND_DIR)/*.c $(TEST_DIR)/*.c $(TEST_LIB)
	./test
	rm hiscore

valgrind: test
	CK_FORK=no valgrind -s  --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=RESULT_VALGRIND.txt ./test
	rm hiscore test

gcov_report:
	$(CC) --coverage -o test $(BACKEND_DIR)/*.c $(TEST_DIR)/*.c $(TEST_LIB)
	./test
	lcov -t "Tetris_backend_test" -o coverage.info --no-external -c -d .
	genhtml -o report coverage.info
	rm *.info *.gcda *.gcno
	rm hiscore test
	$(OPEN) report/index.html

clang:
	clang-format --style=file:"../materials/linters/.clang-format" -n *.h $(FRONTEND_DIR)/*.c $(FRONTEND_DIR)/*.h $(BACKEND_DIR)/*.c $(BACKEND_DIR)/*.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h

clean:
	rm -rf report $(DIST_DIR) $(BUILD_DIR) $(DOCS_DIR)
	rm test hiscore RESULT_VALGRIND.txt