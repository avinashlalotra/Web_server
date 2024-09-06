# Compiler and flags
CC = gcc
CFLAGS = -I./include
OUTPUT = output
FILE ?= main.c

# Default target
all: $(OUTPUT)

# Link the executable
$(OUTPUT): temp.o lib/csapp.a
	$(CC) -static -o $(OUTPUT) temp.o lib/csapp.a

# Compile the source file to object file
temp.o: $(FILE)
	$(CC) $(CFLAGS) -c $(FILE) -o temp.o

# Update the static library
lib/csapp.a: src/csapp.o
	ar rcs lib/csapp.a src/csapp.o

# Rule to compile the object file for the library
src/csapp.o: src/csapp.c
	$(CC) $(CFLAGS) -c src/csapp.c -o src/csapp.o

# Clean up build artifacts
clean:
	rm -f *.o $(OUTPUT)

# Declare phony targets
.PHONY: all clean
