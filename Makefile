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
         -Wmissing-declarations \
         -Wmissing-prototypes \
         -Wpointer-arith \
         -Wredundant-decls \
         -Wshadow \
         -Wstrict-prototypes \
         -Wuninitialized \
         -I./include \
         -D_XOPEN_SOURCE=500 \
         -O3

src_dir := ./src
framework_dir := ./src/framework
alquicor_dir := ./src/alquicor

framework_srcs := $(shell find $(framework_dir) -type f -name '*.c')
alquicor_srcs := $(shell find $(alquicor_dir) -type f -name '*.c')

all: manager consumer

manager: $(src_dir)/manager.c $(framework_srcs) $(alquicor_srcs)
	$(CC) $(CFLAGS) -o $@ $^

consumer: $(src_dir)/consumer.c $(framework_srcs) $(alquicor_srcs)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf manager consumer

.PHONY: all clean
