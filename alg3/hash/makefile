parametrosCompilacao=-Wall #-Wshadow
trab2=trab

all: $(trab2)

$(trab2): main.o tabelaHash.o
	gcc -o $(trab2) main.o tabelaHash.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

tabelaHash.o: tabelaHash.h tabelaHash.c
	gcc -c tabelaHash.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(trab2)