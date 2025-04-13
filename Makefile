CC := gcc
CFLAGS := -ansi \
         -pedantic-errors \
         -Wall \
         -Wextra \
         -Werror \
         -Wcast-align \
         -Wconversion \
         -Wformat \
         -Wformat-security \
         -Wimplicit-fallthrough \
         -Wmissing-declarations \
         -Wmissing-prototypes \
         -Wnull-dereference \
         -Wpointer-arith \
         -Wredundant-decls \
         -Wshadow \
         -Wstrict-prototypes \
         -Wuninitialized \
         -D_SVID_SOURCE \
         -I./include \
         -O3

src_dir := ./src
framework_dir := ./src/framework
restaurant_dir := ./src/restaurant

framework_srcs := $(shell find $(framework_dir) -type f -name '*.c')
restaurant_srcs := $(shell find $(restaurant_dir) -type f -name '*.c')

all: producer consumer

producer: $(src_dir)/producer.c $(framework_srcs) $(restaurant_srcs)
	$(CC) $(CFLAGS) -o $@ $^

consumer: $(src_dir)/consumer.c $(framework_srcs) $(restaurant_srcs)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf producer consumer

.PHONY: all clean
