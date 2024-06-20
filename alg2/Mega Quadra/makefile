CFLAGS = -g -Wall

all: megaquadra

megaquadra: megaquadra.o ordenadores.o busca.o
	gcc megaquadra.o ordenadores.o busca.o -o megaquadra

ordenadores.o: ordenadores.c ordenadores.h
	gcc $(CFLAGS) -c ordenadores.c

busca.o: busca.c busca.h
	gcc $(CFLAGS) -c busca.c

clean:
	-rm -f *.o

purge: clean
	-rm -f megaquadra