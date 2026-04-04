CC      = gcc
CFLAGS  = -Wall -Wextra -g
TARGET  = build/solver
LIBS    = linalg.c utils.c
SRCS    = solver.c $(LIBS)
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

test: build
	$(CC) $(CFLAGS) -o build/test test.c $(LIBS)
	./build/test

clear:
	rm -rf build solver

.PHONY: all symlink clear test
