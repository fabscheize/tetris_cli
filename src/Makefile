CC = gcc
INSTALL = install
RM = rm -rf
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
CFLAGS = -I inc -std=c11 -Wall -Werror -Wextra
CHECKFLAGS = -lcheck
LEAKS = leaks -atExit --
else
CFLAGS = -I inc -std=gnu11 -Wall -Werror -Wextra
CHECKFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
LEAKS = valgrind --tool=memcheck --leak-check=yes
endif
TETRISFLAGS = -L. -ltetris

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib

BIN = tetris
LIB = libtetris.a
TETRIS = $(wildcard brick_game/tetris/*.c)
CLI = $(wildcard gui/cli/*.c)
TESTS = $(wildcard tests/*.c)
STYLEFILES = $(wildcard *.c $(PROJECT)/*.c tests/*.c)
TETRISOBJ := $(patsubst brick_game/tetris/%.c, build/%.o, $(TETRIS))


all: $(BIN)

install: $(BIN) $(LIB)
	@$(INSTALL) $(BIN) $(bindir)
	@$(INSTALL) $(LIB) $(libdir)
	@echo "Installed successfully."

uninstall:
	@$(RM) $(bindir)/$(BIN)
	@$(RM) $(libdir)/$(LIB)
	@echo "Uninstalled successfully."

clean:
	@$(RM) $(BIN) $(LIB) ./tests/report ./build/* *.out *.gcda *.gcno *.info *.aux *.cp* *.log *.toc *.pg* *.dvi ~/Tetris

dvi: readme.texi
	texi2dvi --pdf readme.texi -I . -o readme.dvi
	@mv *.aux *.cp* *.log *.toc *.pg *.pgs ./build

dist: clean
	tar -czf BrickGame-v1.0-1.tar.gz brick_game build gui inc tests Makefile readme.texi

test: test.out
	./test.out

leaks: test.out
	$(LEAKS) ./test.out

gcov_report: $(LIB) $(TESTS) $(TETRIS)
	$(RM) ~/Tetris
	$(CC) $(CFLAGS) $(GCOVFLAGS) $^ -o test_gcov.out $(TETRISFLAGS) $(CHECKFLAGS)
	./test_gcov.out
	lcov -t "gcov_report" -o coverage.info --no-external -c -d .
	@genhtml -q coverage.info -o ./tests/report
	@mv *.gcda *.gcno *.info ./build
	open ./tests/report/index.html

style:
	@clang-format -style=Google -n $(STYLEFILES)

rebuild: clean all

$(BIN): $(CLI) $(LIB)
	$(CC) $(CFLAGS) $(CLI) -o $(BIN) $(TETRISFLAGS) -lncurses

build/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(TETRISOBJ)
	ar cr $@ $^
	ranlib $@

test.out: $(LIB) $(TESTS)
	$(RM) ~/Tetris
	$(CC) $(CFLAGS)  $^ -o test.out $(TETRISFLAGS) $(CHECKFLAGS)

.PHONY: all install uninstall clean test leaks gcov_report style rebuild
