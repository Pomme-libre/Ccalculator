CC = gcc
CFLAGS = -o main -Wall -Wextra -pedantic -std=c23 -lm
FILES = main.c

main: main.c
	$(CC) $(FILES) $(CFLAGS)