C_FLAGS = -std=c99 -g -Wall -Werror -pedantic -Wextra

all: main

entree_sortie.o: entree_sortie.h entree_sortie.c
	gcc -ggdb -lm -c $(CFLAGS) entree_sortie.c

Netlist.o: entree_sortie.h Netlist.h Netlist.c
	gcc -ggdb -lm -c $(CFLAGS) Netlist.c

balayage.o: Netlist.h balayage.h balayage.c
	gcc -ggdb -lm -c $(CFLAGS) balayage.c

Avl.o : Avl.h Netlist.h Avl.c
	gcc -ggdb -lm -c $(CFLAGS) Avl.c

main.o:	entree_sortie.h Netlist.h balayage.h main.c
	gcc -ggdb -lm -c $(CFLAGS) main.c

main: entree_sortie.o Netlist.o balayage.o main.o Avl.o
	gcc -ggdb -o main $(CFLAGS) Avl.o entree_sortie.o Netlist.o balayage.o main.o -lm

clean:
	rm -f *.o main
