# src/
# ├── 3DViewer_2/
# │   └── model/
# │       ├── my_functions.h
# │       ├── objreader.cc
# │       └── shift_scale_rotation.cc
# └── Tests/
# |   └── unit_test.cpp
# └── Makefile
# └── build/




# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -g
LDFLAGS = -lgtest -lgtest_main -lpthread

# Исходные файлы
MODEL_SRC = 3DViewer_2/model/objreader.cc 3DViewer_2/model/shift_scale_rotation.cc
UNIT_TEST_SRC = Tests/unit_test.cpp

# Выходные файлы
STATIC_LIB = s21_3d_viewer_2.a
UNIT_TEST_BIN = unit_test

# Определение операционной системы и специфичные флаги
UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    GFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
    RUNINSTR = ./build/3DViewer_2
    OPEN = cat
    MAKE = make
    RM = rm -rf
    ZIP = tar -czf
else ifeq ($(UNAME), Darwin)
    GFLAGS = -lcheck
    RUNINSTR = open build/3DViewer_2.app
    OPEN = open
    MAKE = make
    RM = rm -rf
    ZIP = tar -czf
else ifeq ($(OS), Windows_NT)
    GFLAGS = -lcheck -lws2_32 -static-libgcc -static-libstdc++
    RUNINSTR = .\build\3DViewer2.exe
    OPEN = notepad
    MAKE = make
    RM = rmdir /s /q
    ZIP = tar -czf
endif

# Основные цели
.PHONY: all test gcov_report install clean dist run dvi leaks valgrind style_repair style_check

all: install

install: uninstall
	mkdir build && cd build && qmake6 ../3DViewer_2/3DViewer_2.pro CONFIG+=qtquickcompiler && $(MAKE) -j8

# если есть ошибка qt.qpa.plugin: Could not find the Qt platform plugin "wayland" in ""
# sudo apt install qt6-wayland

# если есть ошибка: ./build/3DViewer_2: symbol lookup error: /snap/core20/current/lib/x86_64-linux-gnu/libpthread.so.0: undefined symbol: __libc_pthread_init, version GLIBC_PRIVATE
# make: *** [Makefile:90: run] Ошибка 127
# то делай make run  в терминале а не в VScode!


test: $(MODEL_SRC) $(UNIT_TEST_SRC)
	$(CXX) $(CXXFLAGS) $(MODEL_SRC) $(UNIT_TEST_SRC) $(LDFLAGS) -o unit_test
	./unit_test
# 	$(RM) unit_test

gcov_report: clean
	$(CXX) $(CXXFLAGS) --coverage $(UNIT_TEST_SRC) $(MODEL_SRC) $(LDFLAGS) -o gcov_report
	./gcov_report
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=res
	open ./res/index.html
	$(RM) *.gcda *.gcno *.info gcov_report

clean:
	$(RM) $(UNIT_TEST_BIN) $(STATIC_LIB) *.o *.gcda *.gcno *.info res unit_test settings.ini



uninstall:
	$(RM) build

run:
	$(RUNINSTR)

dvi:
	$(OPEN) ./3DViewer_UserGuide.md

dist: clean
	mkdir -p 3DViewer_v2.0/src
	cp Makefile 3DViewer_UserGuide.md 3DViewer_v2.0/src
	cp -R 3DViewer_2 3DViewer_v2.0/src
	$(ZIP) 3DViewer_v2.0.tgz 3DViewer_v2.0
	$(RM) 3DViewer_v2.0

leaks: clean test
	leaks -atExit -- ./unit_test | grep LEAK:

valgrind: clean test
	valgrind --tool=memcheck --track-origins=yes --leak-check=yes ./unit_test

# clang-format
# find all files with .h and .cc extensions and run clang-format on them
# -path - choose only files in the specified directory
# -prune - excludes subdirectories
# -i - makes changes in place
# -name - choose only files with specified name
# -o - merges results OR
# | xargs - runs command on each result
style_repair:
	find 3DViewer_2/view -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -i
	find 3DViewer_2/controller -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -i
	find 3DViewer_2/model -path '3DViewer_2/model/3rdparty' -prune -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -i

style_check:
	find 3DViewer_2/view -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -n
	find 3DViewer_2/controller -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -n
	find 3DViewer_2/model -path '3DViewer_2/model/3rdparty' -prune -name '*.h' -o -name '*.cc' | xargs clang-format -style=Google -n
