CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3
HEADER = -I./
BUILD_DIR = build

all: main

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

main:
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -f $(BUILD_DIR)/*
