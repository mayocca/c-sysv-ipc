all : # Canonical target
BUILD := debug
build_dir := ./build/${BUILD}

framework_srcs := $(wildcard ./src/framework/*.c)
framework_objs := $(framework_srcs:./src/framework/%.c=$(build_dir)/%.o)

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -Werror -g

all: producer consumer

producer

framework: $(framework_objs)
	@$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean all