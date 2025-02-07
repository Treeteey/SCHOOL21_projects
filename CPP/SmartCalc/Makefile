FLAG = -Wall -Werror -Wextra
FILES=$(wildcard SmartCalcQt/CFunctions/*.c)
OBJ=$(patsubst %.c,%.o, ${FILES}) # changing .c for .o and appending to OBJ
GCO=--coverage
#UNAME := $(shell uname)
#UNAME := $(shell echo $(OS))

# Identify the operating system
ifeq ($(OS),Windows_NT)
    UNAME := Windows
else
    UNAME := $(shell uname -s)
endif

TEST= Tests/test_main_calc.c Tests/test_credit_calc.c Tests/main.c Tests/test_deposit_calc.c
QMAKE_PRESENT=$(shell which qmake)

ifeq ($(UNAME), Linux)
	GFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
	QTFLAGS = CONFIG+=qtquickcompiler
	RUNINSTR = ./build/SmartCalc
	OS = Linux
	QMAKE = qmake
	MAKE = /usr/bin/make
	BUILD_PATH = ../SmartCalcQt/SmartCalc.pro
	OPEN = open
	MKDIR := mkdir -p
    CP := cp -R
    RM := -rm -rf
	DEL := rm -rf
    ZIP := tar -czf
endif

ifeq ($(UNAME), Darwin)
	GFLAGS = -lcheck
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
	RUNINSTR = open build/SmartCalc.app
	QMAKE = qmake
	MAKE = /usr/bin/make
	BUILD_PATH = ../SmartCalcQt/SmartCalc.pro
	OPEN = open
	MKDIR := mkdir -p
    CP := cp -R
    RM := -rm -rf
	DEL := rm -rf
    ZIP := tar -czf
endif

ifeq ($(OS),Windows_NT)
	GFLAGS = -lcheck -lws2_32 -static-libgcc -static-libstdc++
	QTFLAGS = CONFIG+=qtquickcompiler
	RUNINSTR = .\build\SmartCalc.exe
	OS = Windows_NT
	QMAKE = qmake6
	MAKE = make
	BUILD_PATH = ..\SmartCalcQt\SmartCalc.pro
	OPEN = notepad
	MKDIR := mkdir
	CP := copy
    RM := rmdir /s /q
	DEL := del /q
    ZIP := tar -czf
endif

ifndef QMAKE_PRESENT
    $(error "No qmake in found in $(PATH), consider installing qmake and Qt on your system")
	$(error "or add path with qmake to PATH variables")
endif

all: install

install: uninstall
	mkdir build && cd build && $(QMAKE) $(BUILD_PATH) $(QTFLAGS) && $(MAKE) -j8

uninstall:
ifdef OS
ifeq ($(OS),Windows_NT)
	if exist build $(RM) build
else
	$(RM) build
endif
endif

clean:
ifdef OS
ifeq ($(OS),Windows_NT)
	-if exist main $(DEL) main
	-if exist *.dSYM $(DEL) *.dSYM
	-if exist test $(DEL) test
	-if exist *.gcda $(DEL) *.gcda
	-if exist *.gcno $(DEL) *.gcno
	-if exist *.info $(DEL) *.info
	-if exist *.tgz $(DEL) *.tgz
else
	-$(RM) build
	-$(DEL) main
	-$(DEL) *.dSYM
	-$(DEL) test
	-$(DEL) *.gcda
	-$(DEL) *.gcno
	-$(DEL) *.info
	-$(DEL) *.tgz
endif
endif

#запустить собранное приложение
run:
	$(RUNINSTR)

#открыть инструкцию
dvi:
	$(OPEN) ./SmartCalc_UserGuide.md


#заархивировать проект
dist: clean
ifdef OS
ifeq ($(OS),Windows_NT)
	if not exist SmartCalc_v1.0 $(MKDIR) SmartCalc_v1.0
	if not exist  SmartCalc_v1.0\src $(MKDIR) SmartCalc_v1.0\src
	$(CP) Makefile SmartCalc_v1.0
	xcopy SmartCalcQt SmartCalc_v1.0\src /E /I
	$(CP) SmartCalc_UserGuide.md SmartCalc_v1.0
	xcopy Tests SmartCalc_v1.0\Tests /E /I
	$(ZIP) SmartCalc_v1.0_dist.tgz SmartCalc_v1.0
	if exist build $(RM) build 
	if exist build $(RM) SmartCalc_v1.0
else
	$(MKDIR) SmartCalc_v1.0
	$(MKDIR) SmartCalc_v1.0/src
	$(CP) Makefile SmartCalcQt SmartCalc_UserGuide.md Tests SmartCalc_v1.0/src
	$(ZIP) SmartCalc_v1.0.tgz SmartCalc_v1.0/
	$(RM) build SmartCalc_v1.0
endif
endif


test:
	@gcc -g $(FLAG) -o test $(TEST) $(FILES) $(GFLAGS)
	./test


gcov_report: clean
	@gcc $(FLAG) $(GCO) $(TEST) $(FILES) -o test $(GFLAGS)
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=res
	open ./res/index.html
	-rm -rf *.dSYM test *.gcda *.gcno *.info


leaks: clean test
	@leaks -atExit -- ./test | grep LEAK:

valgrind: clean test
	@valgrind --tool=memcheck --track-origins=yes --leak-check=yes ./test

style_repair: clean
	clang-format -style=Google -i Tests/*.c Tests/*.h
	clang-format -style=Google -i SmartCalcQt/*.cpp SmartCalcQt/*.h
	clang-format -style=Google -i SmartCalcQt/CFunctions/*.c

style_check: clean
	clang-format -style=Google -n Tests/*.c Tests/*.h
	clang-format -style=Google -n SmartCalcQt/*.cpp SmartCalcQt/*.h
	clang-format -style=Google -n SmartCalcQt/CFunctions/*.c
