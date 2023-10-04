CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -O1 -Werror
LDLIBS = -lm

crosswords: cwddriver.o crosswords.o
	${CC} ${CFLAGS} -o crosswords cwddriver.o crosswords.o ${LDLIBS}

cwddriver.o: cwddriver.c
	${CC} ${CFLAGS} -c cwddriver.c ${LDLIBS}

crosswords.o: crosswords.c
	${CC} ${CFLAGS} -c crosswords.c ${LDLIBS}