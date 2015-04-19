SOURCE = entree_sortie.c Netlist.c balayage.c Avl.c main.c
OBJET = $(SOURCE:.c=.o)
CC = gcc
C_FLAGS = -std=c99 -g -Wall -Werror -pedantic -Wextra
COMPIL = -ggdb -c
LINK = -ggdb -o

all: depends main

%.o: %.c
	$(CC) $(COMPIL) $?

depends: $(SOURCE)
	$(CC) -MM $? > .depends

-include .depends

main: $(OBJET)
	$(CC) $(LINK) $@ $(CFLAGS) $?

clean:
	rm -f *.o main .depends
