SOURCE = avl.c entree_sortie.c Fonctions_Programme.c main.c netlist.c Traitement_Netlist.c
OBJET = $(SOURCE:.c=.o)
CC = gcc
C_FLAGS = -std=c99 -g -Wall -Werror -pedantic -Wextra
COMPIL = -ggdb -c
LINK = -ggdb -o

all: clean depends main

%.o: %.c
	$(CC) $(COMPIL) $?

depends: $(SOURCE)
	$(CC) -MM $? > .depends

-include .depends

main: $(OBJET)
	$(CC) $(LINK) $@ $(CFLAGS) $?

clean:
	rm -f *.o main .depends *.gch

.PHONY: all depends clean
