#include <stdio.h>
#include <stdlib.h>
#include "busca.h"

int buscaSequencial(int *vetor, int tamanho, int chave, int *comp){
    int i=0;
    (*comp)++;
    while (i<tamanho && vetor[i]!=chave){
        i++;
        (*comp)++;
    }

    if(i > tamanho-1){
        return -1;
    }
    return i;
}

int buscaBinaria(int *vetor, int tamanho, int chave, int *comp){
    int meio, esquerda = 0, direita = tamanho-1;
    do{
        meio = (esquerda+direita)/2;  
        if(chave > vetor[meio]){
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
        (*comp)++;
    }while (chave != vetor[meio] && esquerda <= direita);
    
    if(vetor[meio] == chave)
        return meio;
    return -1;
}