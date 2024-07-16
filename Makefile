# Compiler
CC = gcc
AR = ar

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = test

# Files
SRC_FILES = $(SRC_DIR)/cclib.c
TEST_FILES = $(wildcard $(TEST_DIR)/test_*.c)
OBJ_FILES = $(OBJ_DIR)/cclib.o $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES)) $(OBJ_DIR)/main.o
EXECUTABLE = $(OBJ_DIR)/main
STATIC_LIB = $(LIB_DIR)/libcclib.a

# Compile flags
CFLAGS = -I$(INCLUDE_DIR) -g

# Targets
.PHONY: all clean test docs clean_docs force install

all: $(STATIC_LIB) $(EXECUTABLE)

$(OBJ_DIR)/cclib.o: $(SRC_DIR)/cclib.c $(INCLUDE_DIR)/cclib.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cclib.c -o $(OBJ_DIR)/cclib.o

$(STATIC_LIB): $(OBJ_DIR)/cclib.o
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $(STATIC_LIB) $(OBJ_DIR)/cclib.o

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(INCLUDE_DIR)/cclib.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(TEST_DIR)/main.c
	$(CC) $(CFLAGS) -c $(TEST_DIR)/main.c -o $(OBJ_DIR)/main.o

$(EXECUTABLE): $(OBJ_FILES) $(STATIC_LIB)
	$(CC) $(OBJ_FILES) -L$(LIB_DIR) -lcclib -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) $(STATIC_LIB)

clean_docs:
	rm -rf docs/html docs/latex docs/man docs/rtf docs/xml docs/docbook

docs: force
	doxygen Doxyfile

install: $(STATIC_LIB)
	sudo mkdir -p /usr/local/include/CCLIB
	sudo cp $(INCLUDE_DIR)/cclib.h /usr/local/include/CCLIB/
	sudo cp $(STATIC_LIB) /usr/local/lib/
	sudo ldconfig

.PHONY: all clean docs force install

force:
