CC := gcc
CFLAGS := -ansi \
         -pedantic-errors \
         -Wall \
         -Wextra \
         -Werror \
         -D_SVID_SOURCE \
         -I./include \
         -O3

src_dir := ./src
framework_dir := ./src/framework
restaurant_dir := ./src/restaurant

framework_srcs := $(wildcard $(framework_dir)/**/*.c)
restaurant_srcs := $(restaurant_dir)/utils.c

all: producer consumer

producer: $(src_dir)/producer.c $(framework_srcs) $(restaurant_srcs)
	$(CC) $(CFLAGS) -o $@ $^

consumer: $(src_dir)/consumer.c $(framework_srcs) $(restaurant_srcs)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf producer consumer

.PHONY: all clean
