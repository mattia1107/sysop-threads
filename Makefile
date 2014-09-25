#
#	Progetto 2 : Threads
#	Mattia Santangelo		151776
#	Luca Amadori			151103
#

CC = gcc
CFLAGS = -lpthread
DFLAGS = -c
DEPS = declaration.h
OBJ = thread.o tryCatch.o log.o


all: thread

thread: $(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -o thread

thread.o: thread.c
		$(CC) $(DFLAGS) thread.c $(CFLAGS)

tryCatch.o: tryCatch.c
		$(CC) $(DFLAGS) tryCatch.c

log.o: log.c
	$(CC) $(DFLAGS) log.c

clean:	thread.o log.o tryCatch.o
		rm $^