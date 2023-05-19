CPP = g++
CFLAGS =-MP -MMD
SFMLFALGS = -lsfml-graphics -lsfml-window -lsfml-system
RM = rm -r

APP_NAME = game15
LOGIC_NAME = game15_logic
GRAPH_NAME = game15_graph
TEST_NAME = test
CTEST_NAME = ctest

BIN_DIR = bin
SRC_DIR = src
SFML_DIR = external/SFML
OBJ_DIR = obj
TEST_DIR = test
THIRD_DIR = thirdparty

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

GRAPH_SOURCES = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(CPP_EXT)
GRAPH_HPP = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(H_EXT)
GRAPH_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

TEST_SOURCES = $(TEST_DIR)/$(TEST_NAME).$(CPP_EXT)
TEST_LOGIC_SOURCES = $(SRC_DIR)/game15_logic_forTEST/$(LOGIC_NAME).$(CPP_EXT)
TEST_OBJECTS = $(OBJ_DIR)/$(TEST_NAME)/$(TEST_NAME)/$(TEST_NAME).o
TEST_LOGIC = $(OBJ_DIR)/$(TEST_NAME)/logic_test/$(LOGIC_NAME).o

CTEST_SOURCES = $(TEST_DIR)/$(CTEST_NAME).h
CTEST_OBJECTS = $(TEST_DIR)/include/$(CTEST_NAME).o


all: $(LOGIC_OBJECTS) $(GRAPH_OBJECTS)
	g++ -I$(SFML_DIR)/include $(LOGIC_OBJECTS) $(GRAPH_OBJECTS) $(APP_SOURCES) -L$(SFML_DIR)/lib $(SFMLFALGS) -o $(BIN_DIR)/$(APP_NAME)

$(LOGIC_OBJECTS): $(LOGIC_SOURCES) $(LOGIC_HPP)
	g++ -I$(SFML_DIR)/include $(CFLAGS) -c $(LOGIC_SOURCES) -o $(LOGIC_OBJECTS)

$(GRAPH_OBJECTS): $(GRAPH_SOURCES) $(GRAPH_HPP)
	g++ -I$(SFML_DIR)/include $(CFLAGS) -c $(GRAPH_SOURCES) -o $(GRAPH_OBJECTS)

run:
	./$(BIN_DIR)/$(APP_NAME)

test: $(TEST_PATH)

test/game15_logic: test/game15_logic.cpp
	g++ -I$(SFML_DIR)/include $(CFLAGS) -c test/game15_logic.cpp -o test/game15_logic.o

test/test: test/test.cpp
	g++ -c test/test.cpp -o test/test.o

$(TEST_PATH): test/test.o test/game15_logic.o
	g++ $^ -o $@
	./bin/test

.IGNORE: clean
clean:
	$(RM) $(BIN_DIR)/*.exe
	$(RM) $(OBJ_DIR)/*/*/*.o
	$(RM) $(OBJ_DIR)/*/*/*.d
	$(RM) $(OBJ_DIR)/$(TEST_NAME)/*.o
	$(RM) $(OBJ_DIR)/$(TEST_NAME)/*.d