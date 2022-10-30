CC = gcc
CFLAGS = -g -Wall

alter-wav-vol: alter-wav-vol.o wav-header.o wav-data.o
	${CC} ${CFLAGS} -o alter-wav-vol alter-wav-vol.o wav-header.o wav-data.o

alter-wav-vol.o: alter-wav-vol.c
	${CC} ${CFLAGS} -c alter-wav-vol.c

wav-header.o: wav-header.c
	${CC} ${CFLAGS} -c wav-header.c

wav-data.o: wav-data.c
	${CC} ${CFLAGS} -c wav-data.c