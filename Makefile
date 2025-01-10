# Shell Makefile
CC = gcc
CFLAGS = -Wall -Wextra -I ./include
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
TARGET = ./shell

.PHONY: install clean docs

install: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/* $(TARGET)

docs: 
	rm ./README.pdf
	pandoc --resource-path=.:docs -V colorlinks=true README.md -o ./docs/README.pdf
