FLAGS = -std=c++14 -Wall

SRC = main.cpp blockchain.cpp bank_account.cpp bank.cpp

all:
	g++ ${FLAGS} -O2 ${SRC} -pthread -o main

debug:
	g++ ${FLAGS} -O2 ${SRC} -pthread -g -o main