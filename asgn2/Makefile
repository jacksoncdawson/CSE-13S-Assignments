CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g
LFLAGS = 
EXEC = hangman
HEADERS = hangman_helpers.h

all: $(EXEC)

$(EXEC): $(EXEC).o hangman_helpers.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

tests: test_helpers test_functionality

test_functionality:
	./test_functionality.sh

test_helpers: test_helpers.o
	$(CC) $(CFLAGS) test_helpers.o -o test_helpers
	./test_helpers

test_helpers.o: test_helpers.c
	$(CC) $(CFLAGS) -c test_helpers.c -o test_helpers.o

