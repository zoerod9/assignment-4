CC = gcc
CFLAGS = -Wall -g

all: part1 

clean:
	rm -f *.o part1 part1-out-test part1-output

part1: part1.c
	$(CC) $(CFLAGS) -o part1 part1.c

run-test: part1
	./part1 part1testsequence part1-out-test

run-1: part1
	./part1 part1sequence part1-output