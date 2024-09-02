CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

SRC_DIR = .
TEST_DIR = tests
OUT_DIR = out
HEADERS_DIR = headers
HEADERS_FILES = $(wildcard $(HEADERS_DIR)/*.c)

SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

MAIN_BIN = $(OUT_DIR)/main

TEST_BINS = $(TEST_FILES:$(TEST_DIR)/%.c=$(OUT_DIR)/%)

all: $(MAIN_BIN) $(TEST_BINS)

$(MAIN_BIN): $(HEADERS_FILES) $(SRC_FILES) 	main.c
	$(CC) $(CFLAGS) -o $@ $^

$(OUT_DIR)/%: $(HEADERS_FILES) $(SRC_FILES) $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $(HEADERS_FILES) $(SRC_FILES) $(TEST_DIR)/$*.c

clean:
	rm -f $(OUT_DIR)/*

.PHONY: all clean
