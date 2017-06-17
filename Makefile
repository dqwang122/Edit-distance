CC = g++
CFLAGS = -std=c++11 -O2
TARGET = Edit-distance
SRC = Edit-distance.cpp task1.cpp task2.cpp task3.cpp task1.h task2.h task3.h


$(TARGET): $(SRC)
	g++ $^ $(CFLAGS) -o $@