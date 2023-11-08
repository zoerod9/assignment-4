CC = gcc
CFLAGS = -Wall -g

all: part1 

clean:
	rm -f *.o part1 

part1: part1.c
	$(CC) $(CFLAGS) -o part1 part1.c

run: part1
	./part1