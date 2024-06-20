CFLAGS = -g -Wall

all: tp2

tp2: tp2.o filaPrioridade.o libAuxiliar.o
	gcc tp2.o filaPrioridade.o libAuxiliar.o -o tp2

filaPrioridade.o: filaPrioridade.c filaPrioridade.h
	gcc $(CFLAGS) -c filaPrioridade.c

libAuxiliar.o: libAuxiliar.c libAuxiliar.h
	gcc $(CFLAGS) -c libAuxiliar.c

clean:
	-rm -f *.o

purge: clean
	-rm -f tp2