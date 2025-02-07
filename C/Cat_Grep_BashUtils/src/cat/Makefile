CC = gcc -std=c11 -g
CGLAGS = -Wall -Werror -Wextra
LOCATION = -o ../build/
SOURCES = s21_cat.c myFuncs.c myFuncs.h
SOURCES1 = s21_cat1.c myFuncs1.c myFuncs1.h

all: clangclean s21_cat 

s21_cat:
	make clangclean
	$(CC) $(SOURCES)  -o s21_cat

test:
	sh tests.sh

clang:
	clang-format -style=Google -n $(SOURCES)

clangclean:
	clang-format -style=Google -i $(SOURCES)

clean:
	rm -rf *.o *.out s21_cat

rebuild:
	make 
