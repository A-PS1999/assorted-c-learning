CC = gcc
CFLAGS = -g

queue-client: queue-client.o queue-ADT.o
	${CC} ${CFLAGS} -o queue-client queue-client.o queue-ADT.o

queue-client.o: queue-client.c
	${CC} ${CFLAGS} -c queue-client.c

queue-ADT.o: queue-ADT.c
	${CC} ${CFLAGS} -c queue-ADT.c