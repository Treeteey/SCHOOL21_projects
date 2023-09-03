WWW = -Wall -Werror -Wextra -std=c11
LC=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
UNIX = -lsubunit -lrt -lpthread -lm
OS=$(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif


all: s21_math.a


test: s21_math.a
ifeq ($(OS), Darwin)
	gcc $(WWW) tests/s21_math_test.c s21_math.a -o test $(LC) -lm
else
	gcc $(WWW) tests/s21_math_test.c s21_math.a -o test $(LC) $(UNIX)
endif
	./test

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc $(WWW) $(GCOV) s21_*.c tests/*.c -o test $(LC)
else
	gcc $(WWW) $(GCOV) s21_*.c tests/*.c -o test $(LC) $(UNIX)
endif
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html
	make clean_test

s21_math.a: clean
	gcc $(WWW) -c s21_*.c
	ar rc s21_math.a s21_*.o
	ranlib s21_math.a

style:
	clang-format -style=Google -n *.c *.h

clean:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf binary_files
	rm -rf *.o
	rm -rf *.a

clean_test:
	rm -rf *.gcda *.gcno test *.info
