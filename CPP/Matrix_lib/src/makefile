GCC = g++
FILES = s21_matrix_oop_constructors.cpp s21_matrix_oop_overloads.cpp s21_matrix_oop.cpp
MFILES = $(FILES) main.cpp
TFILES = $(FILES) test.cpp
TLAGS =  -lgtest
TEST = test
LIB = s21_matrix_oop.a

all: $(LIB)

# $(FILES:.cpp=.o) - create list of object files with substituted extentions
#variable $@   - represent target = $(LIB)
#variable $^   - represents all dependecies after ':'  =  $(FILES:.cpp=.o)
# so this command will expand in:
# ar rcs s21_matrix_oop.a s21_matrix_oop_constructors.o s21_matrix_oop_overloads.o s21_matrix_oop.o

# Check if the library file exists
ifeq ($(wildcard $(LIB)),)
# If it doesn't exist, build the library
$(LIB): $(FILES:.cpp=.o)
	ar rcs $@ $^
	make clean
else
# If it does exist, print a message
	@echo "Library already exists. Skipping build."
endif


#variable $<   -refers to first dependency or %.cpp
#so when dependency $(FILES:.cpp=.o) is called - its calling this RULE (means how to do things. THIS IS NOT GOAL ) 
# for each .cpp file
%.o: %.cpp
	$(GCC) -c $< -o $@


test: $(LIB)
	$(GCC) test.cpp $(LIB) $(TLAGS) -o $(TEST) 
	./$(TEST)

clean:
ifeq ($(OS),Windows_NT)
	-if exist *.o del /q *.o
	-if exist *.exe del /q *.exe
else
	rm -rf *.o
	rm -rf *.exe
endif


main:
	$(GCC) $(MFILES) -o main
	./main

install_gtest:
	sudo apt-get install build-essential
	sudo apt-get install libgtest-dev
	sudo apt-get install cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp lib/*.a /usr/lib