CFLAGS =-MP -MMD
SFMLFALGS = -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system
RM = rm -r

APP_NAME = game15
LOGIC_NAME = game15_logic
GRAPH_NAME = game15_graph

BIN_DIR = bin
SRC_DIR = src
SFML_DIR = external/SFML
OBJ_DIR = obj

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
LOGIC_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o
GRAPH_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

SRC = src/
TEST = test/
TEST_OBJ = obj/test


CPP_EXT = cpp
H_EXT = h

APP_SOURCES = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(CPP_EXT)
APP_HPP = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(H_EXT)
APP_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/$(APP_NAME).o

LOGIC_SOURCES = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(CPP_EXT)
LOGIC_HPP = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(H_EXT)
LOGIC_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o

LIB_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).a

GRAPH_SOURCES = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(CPP_EXT)
GRAPH_HPP = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(H_EXT)
GRAPH_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

.PHONY: main

$(APP_PATH): $(LOGIC_OBJECTS) $(GRAPH_OBJECTS) $(APP_OBJECTS)
	g++ -I $(SFML_DIR)/include $(CFLAGS) -o $@ $^ -L $(SFML_DIR)/lib $(SFMLFALGS) 
$(GRAPH_OBJECTS): $(GRAPH_SOURCES)
	g++ -I $(SFML_DIR)/include -c $(CFLAGS) -o $@ $^ 
$(LOGIC_OBJECTS): $(LOGIC_SOURCES)
	g++  -I $(SFML_DIR)/include -c $(CFLAGS) -o $@ $^
$(APP_OBJECTS): $(APP_SOURCES)
	g++ -I $(SFML_DIR)/include -c $(CFLAGS) -o $@ $^	


test: $(TEST_PATH)
	./$<

$(TEST_PATH): $(TEST_OBJ)/ctest.o $(TEST_OBJ)/main.o
	g++ $(CFLAGS) -o $@ $^
$(TEST_OBJ)/ctest.o: $(TEST)test.cpp
	g++ -c $(CFLAGS) -o $@ $^
$(TEST_OBJ)/main.o: $(TEST)main.cpp
	g++ -c $(CFLAGS) -o $@ $^
.PHONY: clean


.IGNORE: clean
clean:
	$(RM) $(BIN_DIR)/*.exe
	$(RM) $(OBJ_DIR)/*/*/*.o
	$(RM) $(OBJ_DIR)/*/*/*.a
	$(RM) $(OBJ_DIR)/*/*/*.d
	$(RM) $(OBJ_DIR)/*/*.o
	$(RM) $(OBJ_DIR)/*/*.a
	$(RM) $(OBJ_DIR)/*/*.d
