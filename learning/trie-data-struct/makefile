CC = gcc
CFLAGS = -g -Wall

trie-playground: trie-playground.o trie.o
	${CC} ${CFLAGS} -o trie-playground trie-playground.o trie.o

trie-playground.o: trie-playground.c
	${CC} ${CFLAGS} -c trie-playground.c

trie.o: trie.c
	${CC} ${CFLAGS} -c trie.c