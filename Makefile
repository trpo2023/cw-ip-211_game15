SFMLFALGS = -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system
RM = rm -r
CC = g++

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
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
LOGIC_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o
GRAPH_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

CPP_EXT = cpp
H_EXT = h

APP_SOURCES = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(CPP_EXT)
APP_HPP = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(H_EXT)
APP_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/$(APP_NAME).o

LOGIC_SOURCES = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(CPP_EXT)
LOGIC_HPP = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(H_EXT)
LOGIC_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o
LOGIC_OBJECTS_TEST = $(OBJ_DIR)/$(TEST_DIR)/$(LOGIC_NAME).o
LOGIC_HPP_OBJECTS = $(OBJ_DIR)/$(TEST_DIR)/logic_h.o

LIB_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/lib_game15.a
LOGIC_STATIC_TEST = $(OBJ_DIR)/$(TEST_DIR)/lib_logic.a
GRAPH_STATIC = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/lib_graph.a

GRAPH_SOURCES = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(CPP_EXT)
GRAPH_HPP = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(H_EXT)
GRAPH_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

TEST_SOURCE = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
TEST_OBJECTS = $(TEST_SOURCE:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

.PHONY: main

.PHONY: main

$(APP_PATH): $(APP_OBJECTS) $(LIB_OBJECTS)
	g++ -I $(SFML_DIR)/include -o $@ $^ -L $(SFML_DIR)/lib $(SFMLFALGS) 

$(LIB_OBJECTS): $(LOGIC_OBJECTS) $(GRAPH_OBJECTS)
	ar rcs $@ $^

$(GRAPH_OBJECTS): $(GRAPH_SOURCES)
	g++ -I $(SFML_DIR)/include -c -o $@ $^

$(LOGIC_OBJECTS): $(LOGIC_SOURCES)
	g++ -I $(SFML_DIR)/include -c -o $@ $^

$(APP_OBJECTS): $(APP_SOURCES)
	g++ -I $(SFML_DIR)/include -c -o $@ $^





test: $(TEST_PATH)
	./$<

$(TEST_PATH): $(TEST_OBJECTS) obj/test/main.o $(LOGIC_STATIC_TEST)
	$(CC) $^ -o $@ -L $(SFML_DIR)/lib $(SFMLFALGS)
	./bin/test

obj/test/main.o: test/main.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

$(LOGIC_OBJECTS_TEST): $(LOGIC_SOURCES)
	g++ -I $(SFML_DIR)/include -c -o $@ $^

$(LOGIC_STATIC_TEST): $(LOGIC_OBJECTS_TEST)
	ar rcs $@ $^

.PHONY: clean


.IGNORE: clean
clean:
	$(RM) $(BIN_DIR)/*.exe
	$(RM) $(OBJ_DIR)/*/*/*.o
	$(RM) $(OBJ_DIR)/*/*/*.a
	$(RM) $(OBJ_DIR)/*/*.o
	$(RM) $(OBJ_DIR)/*/*.a
	$(RM) $(OBJ_DIR)/$(TEST_DIR)/*.a
	$(RM) $(OBJ_DIR)/$(TEST_DIR)/*.o

