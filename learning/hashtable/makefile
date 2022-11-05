CC = gcc
CFLAGS = -g -Wall

hashtable-playground: hashtable-playground.o hashtable.o
	${CC} ${CFLAGS} -o hashtable-playground hashtable-playground.o hashtable.o

hashtable-playground.o: hashtable-playground.c
	${CC} ${CFLAGS} -c hashtable-playground.c

hashtable.o: hashtable.c
	${CC} ${CFLAGS} -c hashtable.c