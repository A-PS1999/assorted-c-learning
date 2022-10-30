CC = gcc
CFLAGS = -g -Wall

bst-playground: bst-playground.o bst.o
	${CC} ${CFLAGS} -o bst-playground bst-playground.o bst.o

bst-playground.o: bst-playground.c
	${CC} ${CFLAGS} -c bst-playground.c

bst.o: bst.c
	${CC} ${CFLAGS} -c bst.c