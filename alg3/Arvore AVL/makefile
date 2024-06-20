parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab1_GRR20215522

all: $(nomePrograma)

$(nomePrograma): main.o avl.o
	gcc -o $(nomePrograma) main.o avl.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: avl.h avl.c
	gcc -c avl.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
