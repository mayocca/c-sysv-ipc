CC := gcc
CFLAGS := -ansi \
         -pedantic-errors \
         -Wall \
         -Werror \
         -I./include \
         -D_XOPEN_SOURCE=500 \
         -O3

src_dir := ./src
framework_dir := ./src/framework
alquicor_dir := ./src/alquicor

framework_srcs := $(shell find $(framework_dir) -type f -name '*.c' ! -name '._*')
alquicor_srcs := $(shell find $(alquicor_dir) -type f -name '*.c' ! -name '._*')

all: manager client

manager: $(src_dir)/manager.c $(framework_srcs) $(alquicor_srcs)
	$(CC) $(CFLAGS) -o $@ $^

client: $(src_dir)/client.c $(framework_srcs) $(alquicor_srcs)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf manager client

.PHONY: all clean
