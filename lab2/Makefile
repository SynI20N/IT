# Флаги компиляции
FLAGS = -std=c++14 -Wall

# Директории
SRC_DIR = .
TEST_DIR = tests

# Исходные файлы (основные)
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/blockchain.cpp \
      $(SRC_DIR)/bank_account.cpp \
      $(SRC_DIR)/bank.cpp

# Тестовые файлы (в папке test/)
SRC_TEST = $(TEST_DIR)/bank_account_test.cpp \
           $(TEST_DIR)/bank_test.cpp \
           $(TEST_DIR)/blockchain_test.cpp

# Имя выходного файла
TARGET = main

.PHONY: all debug test clean

all:
	g++ $(FLAGS) -O2 $(SRC) -pthread -o $(TARGET)

debug:
	g++ $(FLAGS) -O2 $(SRC) -pthread -g -o $(TARGET)

test:
	g++ $(FLAGS) -DTEST -O0 $(SRC) $(SRC_TEST) -pthread -g -o $(TARGET) -lgtest

clean:
	rm -f $(TARGET)
