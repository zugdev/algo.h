# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRC = $(wildcard *.c tests/*.c)
HEADERS_SRC = $(wildcard headers/*.c)

# Output directory
OUT_DIR = out

# Executables (derived from SRC files)
EXECS = $(patsubst %.c,$(OUT_DIR)/%,$(notdir $(SRC)))

# Default rule
all: $(EXECS)

# Rule to create output directory if it doesn't exist
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# General rule to compile each source file with headers
$(OUT_DIR)/%: %.c $(HEADERS_SRC) | $(OUT_DIR)
	$(CC) $^ -o $@ $(CFLAGS)

$(OUT_DIR)/%: tests/%.c $(HEADERS_SRC) | $(OUT_DIR)
	$(CC) $^ -o $@ $(CFLAGS)

# Clean rule
clean:
	rm -rf $(OUT_DIR)/*.o $(EXECS)

# Phony targets
.PHONY: all clean
