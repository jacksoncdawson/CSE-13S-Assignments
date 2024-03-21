CC=clang
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
OBJS= huff.o bitwriter.o bitreader.o node.o pq.o
HEAD=bitwriter.h bitreader.h node.h pq.h

all: huff bwtest brtest nodetest pqtest dehuff

huff: $(OBJS)
	$(CC) -o huff  $(OBJS)

bwtest_OBJS=bitwriter.o bwtest.o
brtest_OBJS=bitreader.o brtest.o
nodetest_OBJS=node.o nodetest.o
pqtest_OBJS=pqtest.o pq.o node.o 
dehuff_OBJS=dehuff.o bitwriter.o bitreader.o node.o

bwtest: $(bwtest_OBJS)
	$(CC) -o bwtest $(bwtest_OBJS)

brtest: $(brtest_OBJS)
	$(CC) -o brtest $(brtest_OBJS)

nodetest: $(nodetest_OBJS)
	$(CC) -o nodetest $(nodetest_OBJS)

pqtest: $(pqtest_OBJS)
	$(CC) -o pqtest $(pqtest_OBJS)

dehuff: $(dehuff_OBJS)
	$(CC) -o dehuff $(dehuff_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f huff bwtest brtest nodetest pqtest dehuff *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: clean format all
