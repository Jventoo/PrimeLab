CFLAGS =-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

sequence	:	sequence.o bv.o sieve.o
	$(CC) -o sequence sequence.o bv.o sieve.o -lm
sequence.o	:	sequence.c bv.h sieve.h
	$(CC) -c sequence.c
bv.o	:	bv.c bv.h
	$(CC) -c bv.c
sieve.o	:	sieve.c sieve.h bv.h
	$(CC) -c sieve.c
all	:	sequence
clean	:
	rm -f sequence *.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
