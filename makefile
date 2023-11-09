CC = gcc
CFLAGS = -Wall -g

all: part1 part2

clean:
	rm -f *.o part1 part1-out-test part1-output part2 part2-output

part1: part1.c
	$(CC) $(CFLAGS) -o part1 part1.c

part2: part2.c
	$(CC) $(CFLAGS) -o part2 part2.c

run-test: part1
	./part1 part1testsequence part1-out-test

run-1: part1
	./part1 part1sequence part1-output

run-2: part2
	./part2 part2sequence part2-output