WWW = -Wall -Werror -Wextra -std=c11
LC = -lcheck
GCOV = -fprofile-arcs -ftest-coverage
UNIX = -lsubunit -lrt -lpthread -lm
FILES = s21_matrix.c
OUT = -o main
BRANCH = develop

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS), Darwin)
	OPEN_CMD = open
endif

# Проверка, что операционная система Windows
ifeq ($(OS), Windows_NT)
	# Для Windows
	CC = gcc
	EXECUTABLE_EXT = .exe
else
	# Для Linux и MacOS
	CC = gcc
	EXECUTABLE_EXT =
endif

EXECUTABLE = main$(EXECUTABLE_EXT)

all: s21_matrix.a

test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) $(WWW) tests/s21_tests_matrix.c s21_matrix.a -o test$(EXECUTABLE_EXT) $(LC) -lm
else
	$(CC) $(WWW) tests/s21_tests_matrix.c s21_matrix.a -o test$(EXECUTABLE_EXT) $(LC) $(UNIX)
endif
	./test$(EXECUTABLE_EXT)

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(WWW) $(GCOV) $(FILES) tests/s21_tests_matrix.c -o test$(EXECUTABLE_EXT) $(LC)
else
	$(CC) $(WWW) $(GCOV) $(FILES) tests/s21_tests_matrix.c -o test$(EXECUTABLE_EXT) $(LC) $(UNIX)
endif
	./test$(EXECUTABLE_EXT)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html
	make clean_test

s21_matrix.a: clean
	$(CC) $(WWW) -c $(FILES)
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a


style:
	clang-format -style=Google -n *.c *.h tests/*.c tests/*.h

clean_style:
	clang-format -style=Google -i *.c *.h tests/*.c tests/*.h

clean:
ifeq ($(OS), Windows_NT)
	del *.gcda
	del *.gcno
	del *.info
	del test
	del report
	del binary_files
	del *.o
	del *.a
else
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf binary_files
	rm -rf *.o
	rm -rf *.a
endif


clean_test:
	rm -rf *.gcda *.gcno test *.info

compile:
	gcc s21_matrix.c main.c

git:
	@read -p "Enter commit message: " COMMIT; \
	git add $(FILESgit) makefile; \
	git commit -m "$$COMMIT"; \
	git push -f origin $(BRANCH)