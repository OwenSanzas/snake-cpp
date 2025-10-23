# Makefile for Snake Game Library

CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
AR = ar
ARFLAGS = rcs

# Source files
SOURCES = snake_game.c
OBJECTS = $(SOURCES:.c=.o)

# Output library
LIBRARY = libsnake.a

# Default target
all: $(LIBRARY)

# Build static library
$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Built static library: $(LIBRARY)"

# Compile source files
%.o: %.c snake_game.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(LIBRARY)
	@echo "Cleaned build artifacts"

.PHONY: all clean
