CC = gcc
CFLAGS = -I inc -std=c11 -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
INSTALL = install
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
CHECKFLAGS = -lcheck
else
CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif
# USER = $(shell whoami)
INSTALL_PATH = /usr/local/bin
BIN = tetris


TETRIS = $(wildcard brick_game/tetris/*.c)
CLI = $(wildcard gui/cli/*.c)
TESTS = $(wildcard tests/*.c)
STYLEFILES = $(wildcard *.c $(PROJECT)/*.c tests/*.c)
TETRISOBJ := $(patsubst brick_game/tetris/%.c, build/%.o, $(TETRIS))


all: $(BIN)

install: $(BIN)
	@$(INSTALL) $(BIN) $(INSTALL_PATH)
	@echo "Installed in $(INSTALL_PATH)/$(BIN)"

uninstall: $(BIN)
	@if [ -f $(INSTALL_PATH)/$(BIN) ]; then \
		rm $(INSTALL_PATH)/$(BIN); \
		echo "Uninstalled successfully."; \
	else \
		echo "$(BIN) already uninstalled."; \
	fi

clean:
	@rm -rf tetris tetris_backend.a ./tests/report ./build/* *.out *.gcda *.gcno *.info ~/Tetris/tetris.save

dvi: readme.texi
	texi2dvi --pdf readme.texi -I . -o readme.dvi

dist: clean
	tar -czf BrickGame-1.0-1.tar.gz brick_game build gui inc tests Makefile

test: test.out
	./test.out

leaks: test.out
	leaks -atExit -- ./test.out

gcov_report: tetris_backend.a $(TESTS) $(TETRIS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $(GCOVFLAGS) $^ -o test_gcov.out
	./test_gcov.out
	lcov -t "gcov_report" -o coverage.info --no-external -c -d .
	@genhtml -q coverage.info -o ./tests/report
	@mv *.gcda *.gcno *.info ./build
	open ./tests/report/index.html

style:
	@clang-format -style=Google -n $(STYLEFILES)

rebuild: clean all

$(BIN):	tetris_backend.a $(CLI)
	$(CC) $(CFLAGS) $^ -o $(BIN) -lncurses

build/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tetris_backend.a: $(TETRISOBJ)
	ar rcs $@ $^
	ranlib $@

test.out: tetris_backend.a $(TESTS)
	$(CC) $(CFLAGS) $(CHECKFLAGS) $^ -o test.out

.PHONY: all install uninstall clean test leaks gcov_report style rebuild
