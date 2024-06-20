#include "libAuxiliar.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define TAM_INPUT 200

char *geraStringAleatoria(int tamanho) {
    int key;
    char *str = malloc(sizeof(char) * tamanho);
    const char *minusculas = "abcdefghijklmnopqrstuvwxyz";
    const char *maiusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (tamanho) {
        --tamanho;
        for (size_t n = 0; n < tamanho; n++) {
            if (n == 0) {
                key = rand() % (int)(sizeof(maiusculas - 1));
                str[n] = maiusculas[key];
            } else {
                key = rand() % (int)(sizeof(minusculas - 1));
                str[n] = minusculas[key];
            }
        }
        str[tamanho] = '\0';
    }
    return str;
}

int geraNumeroAleatorio(int inferior, int superior) { return (rand() % (superior - inferior + 1)) + inferior; }

bool verificaInput(char *input) {
    char str[TAM_INPUT];
    strcpy(str, input);
    int length, i;
    length = strlen(str);
    for (i = 0; i < length; i++)
        if (!isdigit(str[i])) return false;

    return true;
}