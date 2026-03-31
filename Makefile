CC      = gcc
CFLAGS  = -Wall -Wextra -g
TARGET  = build/solver
SRCS    = solver.c linalg.c utils.c
OBJS    = $(SRCS:%.c=build/%.o)

all: build $(TARGET) symlink

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

symlink:
	@if [ ! -L solver ]; then \
		ln -s $(TARGET) solver; \
		echo "Symbolic link 'solver' created."; \
	fi

clean:
	rm -rf build solver

.PHONY: all symlink clean
