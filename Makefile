CC := gcc
CFLAGS := -ansi -pedantic-errors -Wall -Wextra -Werror -I./include

src_dir := ./src

all: producer consumer

producer: $(src_dir)/producer/main.c $(src_dir)/framework/args/env.c $(src_dir)/framework/ipc/semaphore.c $(src_dir)/framework/ipc/tokens.c $(src_dir)/framework/utils/logging.c
	$(CC) $(CFLAGS) -o $@ $^

consumer: $(src_dir)/consumer/main.c $(src_dir)/framework/args/env.c $(src_dir)/framework/ipc/semaphore.c $(src_dir)/framework/ipc/tokens.c $(src_dir)/framework/utils/logging.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf $(build_dir)

.PHONY: all clean
