CC=gcc
CFLAGS=-I.
LIBFLAGS=-l pthread
all: ex_pthread_create.c ex_pthread_join.c ex_pthread_stack_size.c
	$(CC) -o ex_pthread_create ex_pthread_create.c $(LIBFLAGS)
	$(CC) -o ex_pthread_join ex_pthread_join.c $(LIBFLAGS)
	$(CC) -o ex_pthread_stack_size ex_pthread_stack_size.c $(LIBFLAGS)
clean:
	rm ex_pthread_create ex_pthread_join ex_pthread_stack_size
