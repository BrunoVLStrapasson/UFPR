CC = gcc
CFLAGS = -O3 -mavx -march=native -DLIKWID_PERFMON -Wall -Wextra 
LDFLAGS = -llikwid

OBJ = pontosCriticos.o funcoes.o

all: pontosCriticos

pontosCriticos: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o pontosCriticos $(LDFLAGS) -lm -lmatheval

pontosCriticos.o: pontosCriticos.c funcoes.h
	$(CC) $(CFLAGS) -c pontosCriticos.c

funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -c funcoes.c

clean:
	rm -f $(OBJ) pontosCriticos
