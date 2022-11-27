CC=gcc
CFLAGS=-I.
LIBFLAGS=-l pthread
all: ex_pthread_globals.c
	$(CC) -o ex_pthread_globals ex_pthread_globals.c $(LIBFLAGS)
	$(CC) -o ex_pthread_mutex_protect_globals ex_pthread_mutex_protect_globals.c $(LIBFLAGS)
	$(CC) -o ex_pthread_mutex_deadlock ex_pthread_mutex_deadlock.c $(LIBFLAGS)
clean:
	rm ex_pthread_globals ex_pthread_mutex_protect_globals ex_pthread_mutex_deadlock
