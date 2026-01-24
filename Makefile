SRC_DIR := src
INC_DIR := includes
OBJ_DIR := obj
BIN_DIR := bin


CC := gcc
CFLAGS := -I$(INC_DIR) -Wall -Wextra

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BIN_DIR)/ics_dbms

.PHONY: compile clean dirs


compile: dirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)



