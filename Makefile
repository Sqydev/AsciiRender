# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2

# Paths
SRC_DIR = src
OBJ_DIR = compiled/object_files
TARGET_DIR = compiled
TARGET = $(TARGET_DIR)/AsciiRender

# Find all .c files(in SRC_DIR)
SRC = $(wildcard $(SRC_DIR)/*.c)

# Find all obj files(in OBJ_DIR)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Main target
$(TARGET): $(OBJ)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(OBJ) -o $(TARGET)

# Compiling things .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	# If no compiled/object_files then create
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

