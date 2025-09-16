CC = gcc
CFLAGS = -o main -Wall -Wextra -pedantic -std=c23
FILES = main.c

main: main.c
	$(CC) $(FILES) $(CFLAGS)