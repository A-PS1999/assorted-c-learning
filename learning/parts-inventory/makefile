CC = gcc
CFLAGS = -g

inventory: inventory.o readline.o quicksort.o
	${CC} ${CFLAGS} -o inventory inventory.o readline.o quicksort.o

inventory.o: inventory.c
	${CC} ${CFLAGS} -c inventory.c

readline.o: readline.c
	${CC} ${CFLAGS} -c readline.c

quicksort.o: quicksort.c
	${CC} ${CFLAGS} -c quicksort.c