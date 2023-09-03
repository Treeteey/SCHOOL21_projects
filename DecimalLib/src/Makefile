WWW = -Wall -Werror -Wextra -std=c11
LC=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
UNIX = -lsubunit -lrt -lpthread -lm
OS=$(shell uname -s)
FILES = s21_arithmetic.c s21_helpers.c s21_compare.c s21_convertors.c s21_round.c

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif


all: s21_decimal.a


test: s21_decimal.a
ifeq ($(OS), Darwin)
	gcc $(WWW) s21_tests_decimal.c s21_decimal.a -o test $(LC) -lm
else
	gcc $(WWW) s21_tests_decimal.c s21_decimal.a -o test $(LC) $(UNIX)
endif
	./test

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc $(WWW) $(GCOV) $(FILES) s21_tests_decimal.c -o test $(LC)
else
	gcc $(WWW) $(GCOV) $(FILES) s21_tests_decimal.c -o test $(LC) $(UNIX)
endif
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html
	make clean_test

s21_decimal.a: clean
	gcc $(WWW) -c $(FILES)
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a

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
