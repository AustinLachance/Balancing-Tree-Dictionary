CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

#####
# Instructions to make Words
#####

Words16: Words16.o tree.o

	${CC} ${CFLAGS} -o Words16 $^

Words16.o: Words16.c tree.h

tree.o: tree.c tree.h

#####
# Delete executables and objects
#####
clean:
	/bin/rm -f Words16 *.o