SRC_DIR := src
INC_DIR := includes
OBJ_DIR := obj
BIN_DIR := bin
EXEC_NAME := ics_dbms

#compiler
CC := gcc

#finds all .h and .c files in include and src folders
INCLUDES := $(shell find $(INC_DIR) -type d)
CFLAGS   := $(addprefix -I,$(INCLUDES)) -Wall -Wextra -g

SOURCES  := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS  := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTABLE := $(BIN_DIR)/${EXEC_NAME}



# compile command
compile: dirs $(EXECUTABLE)

#generate object files
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

#compile the object files with subdirectory preserved
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#make obj and bin dirs if they dont exist
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

#deletes obj and bin dirs for a cleaner compilation
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	@./bin/${EXEC_NAME}

showdat:
	@hexdump data/data.bin

