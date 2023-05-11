CC = g++
CFLAGS = -Wall -Werror
CPPFLAGS = -I src -MP -MMD
SFMLFALGS = -lsfml-graphics -lsfml-window -lsfml-system
I = -I 
L = -L 
INC = include
LIB = lib
O = -o 
C = -c
RM = rm -r

APP_NAME = game15
LOGIC_NAME = game15_logic
GRAPH_NAME = game15_graph
TEST_NAME = test

BIN_DIR = bin
SRC_DIR = src
SFML_DIR = external/SFML
OBJ_DIR = obj
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LOGIC_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).a
GRAPH_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).a
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

SRC_EXT = cpp

APP_SOURCES = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(SRC_EXT)
APP_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/$(APP_NAME).o

LOGIC_SOURCES = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(SRC_EXT)
LOGIC_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o

GRAPH_SOURCES = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(SRC_EXT)
GRAPH_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

DEPS = $(APP_OBJECTS:.o=.h) $(LIB_OBJECTS:.o=.h) $(GRAPH_OBJECTS:.o=.h)


all: $(BIN_DIR)
	$(CC) $(I)$(SFML_DIR)/$(INC) $(C) $(APP_SOURCES) $(O) $(APP_OBJECTS)
	$(CC) $(APP_OBJECTS) $(O) $(APP_PATH) $(L)$(SFML_DIR)/$(LIB) $(SFMLFALGS)
.PHONY: clean run test

run:
	./$(BIN_DIR)/$(APP_NAME)

clean:
	$(RM) $(OBJ_DIR)/*/*/*.o
	$(RM) $(OBJ_DIR)/*/*/*.a
	$(RM) $(OBJ_DIR)/*/*/*.d
	$(RM) $(BIN_DIR)/*.exe