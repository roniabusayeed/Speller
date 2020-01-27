CC=clang
CFLAGS=-ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LDLIBS=-lm -lcrypt

speller:
	${CC} ${CFLAGS} -c -o speller.o speller.c
	${CC} ${CFLAGS} -c -o dictionary.o dictionary.c
	${CC} ${CFLAGS} -c -o hash.o hash.c
	${CC} ${CFLAGS} -o speller speller.o dictionary.o hash.o ${LDLIBS}
