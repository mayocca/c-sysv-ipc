CC = gcc
CFLAGS = -ansi \
		 -Wall \
		 -Wextra \
		 -Werror \
		 -pedantic-errors \
		 -O3 \
		 -fsanitize=address \
		 -I./include

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

FRAMEWORK_SRC = $(wildcard $(SRC_DIR)/framework/*.c)
CONSUMER_SRC = $(wildcard $(SRC_DIR)/producer/*.c)
PRODUCER_SRC = $(wildcard $(SRC_DIR)/consumer/*.c)

FRAMEWORK_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(FRAMEWORK_SRC))
CONSUMER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CONSUMER_SRC))
PRODUCER_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(PRODUCER_SRC))

CONSUMER = $(BIN_DIR)/consumer
PRODUCER = $(BIN_DIR)/producer

.PHONY: all clean
all: $(PRODUCER) $(CONSUMER)

$(PRODUCER): $(FRAMEWORK_OBJ) $(PRODUCER_OBJ) | $(BIN_DIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(CONSUMER): $(FRAMEWORK_OBJ) $(CONSUMER_OBJ) | $(BIN_DIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
