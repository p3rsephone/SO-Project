CC = gcc
CFLAGS = -g -Wall -Wno-unused-result -O2

all: controller const filter spawn window

controller: stringProcessing.o
	$(CC) $(CFLAGS) -o controller stringProcessing.o controller.c

const: stringProcessing.o const.c
	$(CC) $(CFLAGS) -o const stringProcessing.o const.c

filter: stringProcessing.o filter.c
	$(CC) $(CFLAGS) -o filter stringProcessing.o filter.c

spawn: stringProcessing.o spawn.c
	$(CC) $(CFLAGS) -o spawn stringProcessing.o spawn.c

window: stringProcessing.o window.c
	$(CC) $(CFLAGS) -o window stringProcessing.o window.c

stringProcessing.o: stringProcessing.c stringProcessing.h
	$(CC) $(CFLAGS) -c stringProcessing.c

clean:
	rm fifo* *.o

