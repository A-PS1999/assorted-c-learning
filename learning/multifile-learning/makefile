CC = gcc
CFLAGS = -g

justify: justify.o word.o line.o
		${CC} ${CFLAGS} -o justify justify.o word.o line.o

justify.o: justify.c
		${CC} -c justify.c

word.o: word.c
		${CC} -c word.c

line.o: line.c
		${CC} -c line.c