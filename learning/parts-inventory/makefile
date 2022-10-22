CC = gcc
CFLAGS = -g -Wall

inventory: inventory.o readline.o
	${CC} ${CFLAGS} -o inventory inventory.o readline.o

inventory.o: inventory.c
	${CC} ${CFLAGS} -c inventory.c

readline.o: readline.c
	${CC} ${CFLAGS} -c readline.c