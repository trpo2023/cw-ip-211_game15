CPP = g++
CFLAGS = -Wall
SFMLFALGS = -lsfml-graphics -lsfml-window -lsfml-system
RM = rm -r

APP_NAME = game15
LOGIC_NAME = game15_logic
GRAPH_NAME = game15_graph

BIN_DIR = bin
SRC_DIR = src
SFML_DIR = external/SFML
OBJ_DIR = obj

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LOGIC_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o
GRAPH_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o

CPP_EXT = cpp
HPP_EXT = hpp

APP_SOURCES = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(CPP_EXT)
APP_HPP = $(SRC_DIR)/$(APP_NAME)/$(APP_NAME).$(HPP_EXT)
APP_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/$(APP_NAME).o

LOGIC_SOURCES = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(CPP_EXT)
LOGIC_HPP = $(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).$(HPP_EXT)
LOGIC_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(LOGIC_NAME)/$(LOGIC_NAME).o

GRAPH_SOURCES = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(CPP_EXT)
GRAPH_HPP = $(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).$(HPP_EXT)
GRAPH_OBJECTS = $(OBJ_DIR)/$(SRC_DIR)/$(GRAPH_NAME)/$(GRAPH_NAME).o\

all: $(LOGIC_OBJECTS) $(GRAPH_OBJECTS)
	$(СPP) -I$(SFML_DIR)/include $(LOGIC_OBJECTS) $(GRAPH_OBJECTS)  $(APP_SOURCES) -L$(SFML_DIR)/lib $(SFML) -o $(BIN_DIR)/$(APP_NAME)

$(LOGIC_OBJECTS): $(LOGIC_SOURCES) $(LOGIC_HPP)
	$(СPP) -c -I$(SFML_DIR)/include $(LOGIC_SOURCES) -o $(LOGIC_OBJECTS)

$(GRAPH_OBJECTS): $(GRAPH_SOURCES) $(GRAPH_HPP)
	$(СPP) -c -I$(SFML_DIR)/include $(GRAPH_SOURCES) -o $(GRAPH_OBJECTS)

run:
	$(BIN_DIR)/$(APP_NAME)


clean:
	$(RM) $(OBJ_DIR)/*/*/*.o
	$(RM) $(OBJ_DIR)/*/*/*.a
	$(RM) $(OBJ_DIR)/*/*/*.d
	$(RM) $(BIN_DIR)/*.exe