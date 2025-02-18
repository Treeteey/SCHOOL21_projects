CC = g++ -std=c++17 -Wall -Werror -Wextra -lstdc++
CC_R = g++ -std=c++20 -Wall -Werror -Wextra -lstdc++
LIBS = -lgtest -pthread
GCOV = --coverage

ADELINAN_TEST = test_adelinan
TAMRAMAR_TEST = test_tamramar
CRAYDLEC_TEST = test_craydlec

all: clean test_adelinan test_tamramar test_craydlec

test_adelinan:
	$(CC) $(GCOV) tests/list_tests.cc -o $(ADELINAN_TEST) $(LIBS)
	./$(ADELINAN_TEST)

test_tamramar:
	$(CC) $(GCOV) tests/tests.cc -o $(TAMRAMAR_TEST) $(LIBS)
	./$(TAMRAMAR_TEST)

test_craydlec:
	$(CC_R) $(GCOV) tests/combined_test.cc -o $(CRAYDLEC_TEST) $(LIBS)
	./$(CRAYDLEC_TEST)

gcov_report: clean
	make test_adelinan
	make test_tamramar
	make test_craydlec
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory report
	xdg-open ./report/index.html 
	make clean_test

clean_test:
ifeq ($(OS),Windows_NT)
	-if exist *.gcda $(DEL) *.gcda
	-if exist *.gcno $(DEL) *.gcno
	-if exist *.info $(DEL) *.info
	-if exist $(ADELINAN_TEST) $(DEL) $(ADELINAN_TEST)
	-if exist $(TAMRAMAR_TEST) $(DEL) $(TAMRAMAR_TEST)
	-if exist $(CRAYDLEC_TEST) $(DEL) $(CRAYDLEC_TEST)
else
	rm -rf *.gcda *.gcno *.info $(ADELINAN_TEST) $(TAMRAMAR_TEST) $(CRAYDLEC_TEST)
endif

clean: clean_test
ifeq ($(OS),Windows_NT)
	-if exist *.o $(DEL) *.o
	-if exist *.a $(DEL) *.a
else
	rm -rf ./*.o ./*.a report
endif

style:
	clang-format -style=Google -n containers/list/*.tpp containers/s21_map/*.tpp containers/s21_set/*.tpp containers/tree/*.tpp containers/vector/*.tpp
