CC= gcc -std=c11 -g
CFLAGS= -Wall -Wextra -Werror
GREP= s21_grep.c s21_grep.h



s21_grep:
	rm -f s21_grep
	make clangclean
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

test:
	bash tests.sh

clean:
	rm -f s21_grep
#	rm -rf *.a *.out *.o

clang:
	clang-format -style=Google -n $(GREP)

clangclean:
	clang-format -style=Google -i $(GREP)

