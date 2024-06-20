#include "filaPrioridade.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "libAuxiliar.h"

Paciente cadastraPaciente(FilaPrioridade *fila) {
    int maiorId = 1, prioridade;
    char nome[200];
    Paciente pac;

    if (filaVazia(fila)) {
        pac.id = 1;
    } else {
        for (int i = 1; i <= fila->tamanho; i++)
            if (fila->pacientes[i].id > maiorId) maiorId = fila->pacientes[i].id;
        pac.id = maiorId + 1;
    }

    printf("Qual o nome do paciente: ");
    scanf("%s", nome);
    printf("Qual a prioridade do paciente: ");
    scanf("%d", &prioridade);

    strcpy(pac.nome, nome);
    pac.prioridade = prioridade;

    printf("\n");

    return pac;
}

FilaPrioridade *criaFilaPrioridade() {
    FilaPrioridade *fila;
    fila = malloc(sizeof(FilaPrioridade));
    if (fila == NULL) {
        printf("Nao foi possivel criar um heap\n\n");
        exit(1);
    }

    fila->tamanho = 0;
    printf("\nVetor criado com sucesso!\n");
    return fila;
}

bool liberaFilaPrioridade(FilaPrioridade *fila) {
    if (fila == NULL) return false;
    free(fila);
    return true;
}

int tamanhoFila(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return -1;
    return fila->tamanho;
}

bool filaCheia(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;
    return (fila->tamanho == TAM_MAX);
}

bool filaVazia(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;
    return (fila->tamanho == 0);
}

bool insereElemento(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;

    if (filaCheia(fila)) {
        printf("Fila cheia\n\n");
        return false;
    }

    int comp = 0;

    if (!checaHeap(fila)) heapfy(fila, &comp);

    Paciente pac = cadastraPaciente(fila);

    Paciente aux;
    int novo = fila->tamanho + 1;
    fila->pacientes[novo] = pac;

    while (novo > 1 && fila->pacientes[novo / 2].prioridade < fila->pacientes[novo].prioridade) {
        aux = fila->pacientes[novo];
        fila->pacientes[novo] = fila->pacientes[novo / 2];
        fila->pacientes[novo / 2] = aux;
        novo = novo / 2;
    }

    fila->tamanho++;
    printf("Paciente inserido com sucesso!\n");
    return true;
}

bool sacodeHeap(FilaPrioridade *fila, int n, int *comp) {
    if (fila == NULL) return false;

    Paciente aux;
    int i = 2;
    while (i <= n) {
        (*comp)++;
        if (i < n && fila->pacientes[i].prioridade < fila->pacientes[i + 1].prioridade) i++;
        (*comp)++;
        if (fila->pacientes[i / 2].prioridade >= fila->pacientes[i].prioridade) break;

        aux = fila->pacientes[i / 2];
        fila->pacientes[i / 2] = fila->pacientes[i];
        fila->pacientes[i] = aux;
        i *= 2;
    }
    return true;
}

bool removeElemento(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;

    int comp = 0;
    if (fila->tamanho == 0) {
        printf("Fila esta vazia\n\n");
        return false;
    }

    fila->pacientes[1] = fila->pacientes[fila->tamanho];
    fila->tamanho--;
    sacodeHeap(fila, fila->tamanho, &comp);
    printf("Paciente removido com sucesso!\n");
    return true;
}

bool imprimeFilaPrioridade(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;

    for (int i = 1; i <= fila->tamanho; i++)
        printf("Id: %d; Nome: %s; Prioridade: %d\n", fila->pacientes[i].id, fila->pacientes[i].nome, fila->pacientes[i].prioridade);
    printf("\n");

    return true;
}

bool checaHeap(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;

    for (int i = fila->tamanho; i > 1; i--)
        if (fila->pacientes[i].prioridade > fila->pacientes[i / 2].prioridade) return false;
    return true;
}

bool heapfy(FilaPrioridade *fila, int *comp) {
    if (!filaExiste(fila)) return false;

    Paciente aux;

    (*comp)++;
    for (int k = 1; k < fila->tamanho; ++k) {
        int f = k + 1;
        (*comp)++;
        while (f > 1 && fila->pacientes[f / 2].prioridade < fila->pacientes[f].prioridade) {
            (*comp)++;
            aux = fila->pacientes[f / 2];
            fila->pacientes[f / 2] = fila->pacientes[f];
            fila->pacientes[f] = aux;
            f = f / 2;
        }
    }

    return true;
}

bool heapSort(FilaPrioridade *fila, int *compHeapSort, int *compHeapfy) {
    if (!filaExiste(fila)) return false;

    int i;
    Paciente aux;

    if (!checaHeap(fila)) heapfy(fila, compHeapfy);

    for (i = fila->tamanho; i > 1; i--) {
        // o primeiro elemento de um Heap eh sempre o maior
        aux = fila->pacientes[1];
        fila->pacientes[1] = fila->pacientes[i];
        fila->pacientes[i] = aux;
        sacodeHeap(fila, i - 1, compHeapSort);
    }

    printf("Ordenacao finalizada!\n\n");
    printf("Foram realizadas %d comparacoes pelo Heapfy\n", *compHeapfy);
    printf("Foram realizadas %d comparacoes pelo HeapSort\n", *compHeapSort);
    return true;
}

bool alteraPrioridadePaciente(FilaPrioridade *fila) {
    if (!filaExiste(fila)) return false;

    int i = 1, n, comp = 0;
    int id;
    printf("Qual o numero de identificacao do paciente? \n");
    scanf("%d", &id);

    while (i <= fila->tamanho && fila->pacientes[i].id != id) i++;

    if (fila->pacientes[i].id == id) {
        printf("Qual a nova prioridade? ");
        scanf("%d", &n);

        fila->pacientes[i].prioridade = n;
        heapfy(fila, &comp);

        printf("Prioridade do paciente com identificacao %d alterada com sucesso!\n", id);
        return true;
    } else {
        printf("Nao existe paciente com esse numero de identificacao.\n");
        return false;
    }
}

bool filaExiste(FilaPrioridade *fila) {
    if (fila != NULL) return true;
    printf("Fila nao existe.\n");
    return false;
}

FilaPrioridade *geradorVetorAleatorio(int quantidadeElementos) {
    FilaPrioridade *vetor = criaFilaPrioridade();
    Paciente pac;
    char *str;
    for (int i = 1; i <= quantidadeElementos; i++) {
        pac.id = i;
        str = geraStringAleatoria(geraNumeroAleatorio(5, 10));
        strcpy(pac.nome, str);
        pac.prioridade = geraNumeroAleatorio(0, 100);

        vetor->pacientes[i] = pac;
        vetor->tamanho++;
        free(str);
    }
    return vetor;
}