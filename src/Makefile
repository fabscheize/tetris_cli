PROJECT = brick_game

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
CHECKFLAGS = -lcheck
else
CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

TETRIS = $(wildcard brick_game/tetris/*.c)
CLI = $(wildcard gui/cli/*.c)
TESTS = $(wildcard tests/*.c)
STYLEFILES = $(wildcard *.c $(PROJECT)/*.c tests/*.c)
TETRISOBJ := $(patsubst brick_game/tetris/%.c, build/%.o, $(TETRIS))
CLIOBJ := $(patsubst gui/cli/%.c, build/%.o, $(CLI))


all: clean tetris_cli

tetris_cli:	build/tetris_backend.a $(CLI)
	$(CC) $(CFLAGS) $^ -o tetris_cli -lncurses
	./tetris_cli

build/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/tetris_backend.a: $(TETRISOBJ)
	ar rcs $@ $^
	ranlib $@

test: $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $^ -o test.out
	./test.out

gcov_report: $(PROJECT).a $(SOURCES) $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $(GCOVFLAGS) $^ -o test_gcov.out
	./test_gcov.out
	lcov -t "gcov_report" -o coverage.info --no-external -c -d .
	@genhtml -q coverage.info -o ./tests/report
	@mv *.gcda *.gcno *.info ./build
	open ./tests/report/index.html

style:
	@clang-format -style=Google -n $(STYLEFILES)

leaks: $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $^ -o test.out
	leaks -atExit -- ./test.out

clean:
	@rm -rf cli_frontend.a tetris_cli save ./tests/report ./build/* *.out *.gcda *.gcno *.info

rebuild: clean all

.PHONY: all tetris_cli cli_frontend.a test gcov_report style clean rebuild
