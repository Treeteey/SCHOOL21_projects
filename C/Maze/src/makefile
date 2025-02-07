FILES= ui/*.c logic/*.c generate_maze/*.c solve_maze/*.c
GXX = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
EXE = ui.out
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
   		OPEN_CMD = open
		TEST_LIBS += -lcheck
endif
ifeq ($(UNAME_S), Linux)
		TEST_LIBS += -lcheck -lsubunit -lm
		OPEN_CMD = xdg-open
endif		

#-lncurses
all: install
	./$(EXE)

install:
	$(GXX) $(FLAGS) $(FILES) -o $(EXE)  -lncursesw -DNCURSES_STATIC -DNCURSES_WIDECHAR=1

uninstall: 
	-rm -rf ui.out

# need fix tests
test:  
	$(GXX) $(FLAGS) tests/tests.*c generate_maze/generate_maze.c solve_maze/*.c -o test $(TEST_LIBS)
	./test
	rm -f test_maze.txt

clean:
	rm -f $(EXE) test
	rm -f ui/*.out
	rm -f my_maze.txt
	-rm -rf *.o *.a
	-rm -rf maze test greport
	-rm -rf *.gcda *.gcno *.info
	-rm -rf *.dSYM report *.install


clang_check:
	find . -type f -name '*.h' -o -name '*.c' | xargs clang-format -n -style=Google

clang_repair:
	find . -type f -name '*.h' -o -name '*.c' | xargs clang-format -i -style=Google

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test


gcov_report: 
	gcc --coverage generate_maze/generate_maze.c tests/tests.*c solve_maze/*.c -o greport $(TEST_LIBS)
	./greport
	rm -f test_maze.txt
	lcov -t "test" -o maze.info -c -d .
	genhtml -o report maze.info
	$(OPEN_CMD) ./report/index.html
