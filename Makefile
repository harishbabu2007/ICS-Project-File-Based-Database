# Compiler
CXX := g++

INC_DIR := includes
# Flags
CXXFLAGS := -std=c++17 -Wall -Wextra -I$(INC_DIR)

# Directories
SRC_DIR := src
BIN_DIR := bin
TARGET := $(BIN_DIR)/ics_dbms

# Dynamically collect all .cpp files
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')


# Compile target
compile: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Run target... but compile too
run: compile
	./$(TARGET)

# Clean target
clean:
	rm -rf $(BIN_DIR)

# Rebuild target
rebuild: clean compile
