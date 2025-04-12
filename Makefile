CC := gcc
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -Werror -I./include -O3

src_dir := ./src

all: producer consumer

producer: $(src_dir)/producer.c $(src_dir)/framework/os/env.c $(src_dir)/framework/ipc/semaphore.c $(src_dir)/framework/ipc/tokens.c $(src_dir)/framework/utils/logging.c
	$(CC) $(CFLAGS) -o $@ $^

consumer: $(src_dir)/consumer.c $(src_dir)/framework/os/env.c $(src_dir)/framework/ipc/semaphore.c $(src_dir)/framework/ipc/tokens.c $(src_dir)/framework/utils/logging.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf producer consumer

.PHONY: all clean
