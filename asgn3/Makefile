# Makefile for CSE 13S, Winter 2024, Assignment 3

CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic

.PHONY: all clean format
all: xd bad_xd

xd: xd.o
	$(CC) $(CFLAGS) $< -o xd
xd.o: xd.c
	$(CC) $(CFLAGS) -c xd.c
bad_xd: bad_xd.o
	$(CC) $(CFLAGS) $< -o bad_xd
bad_xd.o: bad_xd.c
	$(CC) $(CFLAGS) -c bad_xd.c
format: 
	clang-format -i -style=file *.[ch]
clean:
	rm -f xd *.o
	rm -f bad_xd *.o
