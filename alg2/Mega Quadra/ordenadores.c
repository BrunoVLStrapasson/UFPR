#include <stdio.h>
#include <stdlib.h>
#include "ordenadores.h"

void selectionSort(int *vetor, int tamanho, long long int* comp){
    int i, j, indexMenor, aux;
    for(i=0; i<tamanho-1; i++){
        indexMenor = i;
        for(j=i+1; j<tamanho; j++){
            (*comp)++;
            if(vetor[j]<vetor[indexMenor]) indexMenor = j;
        }
        if(i != indexMenor){
            aux = vetor[indexMenor];
            vetor[indexMenor] = vetor[i];
            vetor[i] = aux;
        }
    }
}

void bubbleSort(int *vetor, int tamanho, long long int* comp){
    int i, j, aux;
    for(i=0; i<tamanho-1; i++){
        for(j=0; j<tamanho-(i+1); j++){
            (*comp)++;
            if(vetor[j+1]<vetor[j]){
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}

int medianaPivo(int *v, int esq, int dir){
    int valorMediana, meio = (esq+dir)/2;

    if((v[esq] >= v[dir] && v[esq] <= v[meio]) || (v[esq] <= v[dir] && v[esq] >= v[meio])){
        valorMediana = v[esq];
    }

    if((v[dir] >= v[esq] && v[dir] <= v[meio]) || (v[dir] <= v[esq] && v[dir] >= v[meio])){
        valorMediana = v[dir];
    }

    if((v[meio] >= v[esq] && v[meio] <= v[dir]) || (v[meio] <= v[esq] && v[meio] >= v[dir])){
        valorMediana = v[dir];
    }

    return valorMediana;
}

int particiona(int *vetor, int inicio, int fim, long long int* comp){
    int esq, dir, aux, valorPivo;
    valorPivo = medianaPivo(vetor, inicio, fim);
    esq = inicio;
    dir = fim;

    while(esq<dir){
        (*comp)++;
        while(esq <= fim && vetor[esq]<=valorPivo){
            (*comp)++;
            esq++;   
        }

        (*comp)++;
        while(dir >= 0 && vetor[dir]>valorPivo) {
            (*comp)++;
            dir--;
        }

        if(esq<dir){
            aux = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = aux;
        }
    }

    vetor[inicio] = vetor[dir];
    vetor[dir] = valorPivo;
    
    return dir;
}

void quickSortRecursivo(int *vetor, int inicio, int fim, long long int* comp){
    int pivo;
    if(fim > inicio){
        pivo = particiona(vetor, inicio, fim, comp);
        quickSortRecursivo(vetor, inicio, pivo-1, comp);
        quickSortRecursivo(vetor, pivo+1, fim, comp);

    }
}

void quickSortIterativo(int *vetor, int esq, int dir, long long int* comp){
    int pivo;
    int vetAux[dir - esq + 1];
    int topo = -1;

    vetAux[++topo] = esq;
    vetAux[++topo] = dir;
    while (topo >= 0) {
        dir = vetAux[topo--];
        esq = vetAux[topo--];
 
        pivo = particiona(vetor, esq, dir, comp);

        if (pivo - 1 > esq) {
            vetAux[++topo] = esq;
            vetAux[++topo] = pivo - 1;
        }

        if (pivo + 1 < dir) {
            vetAux[++topo] = pivo + 1;
            vetAux[++topo] = dir;
        }
    }
}