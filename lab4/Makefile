# Флаги компиляции
FLAGS = -std=c++20 -Wall

# Директории
SRC_DIR = .
TEST_DIR = tests

# Исходные файлы (основные)
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/md5.cpp \
      $(SRC_DIR)/sha256.cpp \

# Тестовые файлы (в папке test/)
SRC_TEST = $(TEST_DIR)/md5_test.cpp \
           $(TEST_DIR)/sha256_test.cpp \
           $(TEST_DIR)/hacker_test.cpp

# Имя выходного файла
TARGET = main

.PHONY: all debug test coverage clean

all:
	g++ $(FLAGS) -fopenmp -O2 $(SRC) -pthread -o $(TARGET)

debug:
	g++ $(FLAGS) -fopenmp -O0 $(SRC) -pthread -g -o $(TARGET)

test:
	g++ $(FLAGS) -fopenmp -DTEST -O0 $(SRC) $(SRC_TEST) -pthread -g -o $(TARGET) -lgtest

coverage:
	g++ $(FLAGS) -DTEST -fprofile-arcs -ftest-coverage -fopenmp -O0 -g $(SRC) $(SRC_TEST) -pthread -o $(TARGET) -lgtest

clean:
	rm -f $(TARGET)
