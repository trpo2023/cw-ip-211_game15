CC = g++
CFLAGS = -Wall -Werror
CPPFLAGS = -I src -MP -MMD

APP_NAME = geometry
TEST_NAME = test

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test


APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

SRC_EXT = cpp

TEST_SOURCE = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
TEST_OBJECTS = $(TEST_SOURCE:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

all:bin
	g++ -Isrc/SFML/include -c src/game15/main.cpp -o obj/src/game15/main.o
	g++ obj/src/game15/main.o -o bin/main -Lsrc/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
.PHONY: clean run test

run: 
	./main

test:bin
	 g++ -Isrc/SFML/include -c test/test.cpp -o obj/test/main.o
	 g++ obj/test/main.o -o bin/test -Lsrc/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
	 ./bin/test


clean:
	rm -r main.o
	rm -r main.exe