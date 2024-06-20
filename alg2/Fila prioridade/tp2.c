#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "filaPrioridade.h"
#include "libAuxiliar.h"

#define TAM_INPUT 200

int main() {
    srand(time(NULL));

    char escolha[TAM_INPUT] = "1";
    char qntElementos[TAM_INPUT] = "1";
    int qntPessoas = 0;
    FilaPrioridade* heap = NULL;
    int compHeapSort = 0, compHeapfy = 0;

    printf("\n*** SISTEMA DE CADASTRO DE PACIENTES ***\n\n");

    printf("1 - Criar uma nova fila de prioridades\n");
    printf("2 - Inserir um paciente na fila\n");
    printf("3 - Remover paciente da fila\n");
    printf("4 - Alterar prioridade de um paciente\n");
    printf("5 - Analisar quantas pessoas estao na fila\n");
    printf("6 - Verificar se a fila atual eh um Heap\n");
    printf("7 - Ordenar de acordo com a prioridade\n");
    printf("8 - Printar fila atual\n");
    printf("9 - Gerar vetor aleatorio\n");
    printf("10 - Transformar fila aleatoria em heap\n");
    printf("\n0 - Sair\n");
    while (atoi(escolha) != 0) {
        printf("\nO que deseja fazer? ");
        scanf("%s", escolha);
        while (!verificaInput(escolha)) {
            printf("Valor invalido\n");
            printf("O que deseja fazer? ");
            scanf("%s", escolha);
        }

        switch (atoi(escolha)) {
            case 1:
                printf("\n");
                if (heap != NULL) liberaFilaPrioridade(heap);
                heap = criaFilaPrioridade();
                break;

            case 2:
                printf("\n");
                if (filaExiste(heap)) insereElemento(heap);
                break;

            case 3:
                printf("\n");
                if (filaExiste(heap)) removeElemento(heap);
                break;

            case 4:
                printf("\n");
                if (filaExiste(heap)) alteraPrioridadePaciente(heap);
                break;

            case 5:
                printf("\n");
                if (filaExiste(heap)) {
                    qntPessoas = tamanhoFila(heap);
                    if (qntPessoas > 0)
                        printf("A fila de prioridades possui %d pacientes.\n", qntPessoas);
                    else
                        printf("A fila de prioridades esta vazia.\n");
                }
                break;

            case 6:
                printf("\n");
                if (filaExiste(heap)) {
                    if (checaHeap(heap))
                        printf("Eh um heap\n");
                    else
                        printf("Nao eh um heap\n");
                };
                break;

            case 7:
                printf("\n");
                if (filaExiste(heap)) heapSort(heap, &compHeapSort, &compHeapfy);
                break;

            case 8:
                printf("\n");
                if (filaExiste(heap))
                   // if (tamanhoFila(heap)== 0)
                        printf("fila vazia.\n");
                imprimeFilaPrioridade(heap);          
                break;

            case 9:
                printf("\n");
                compHeapfy = 0, compHeapSort = 0;
                if (heap != NULL) liberaFilaPrioridade(heap);
                printf("Quantas pessoas serao inseridas? ");
                scanf("%s", qntElementos);
                while (!verificaInput(qntElementos)) {
                    printf("Valor invalido\n");
                    printf("Quantas pessoas serao inseridas? ");
                    scanf("%s", qntElementos);
                }
                heap = geradorVetorAleatorio(atoi(qntElementos));
                break;

            case 10:
                printf("\n");
                if (heap != NULL) {
                    if (!checaHeap(heap)) {
                        compHeapfy = 0;
                        if (heapfy(heap, &compHeapfy)) {
                            printf("Heapfy realizado com sucesso!\n");
                            printf("Foram realizadas %d comparacoes. \n", compHeapfy);
                        }
                    } else {
                        printf("Esse vetor ja eh um Heap.\n");
                    }
                }
                break;

            case 0:
                liberaFilaPrioridade(heap);
                printf("Ate mais\n");
                break;

            default:
                printf("Valor invalido\n");
                break;
        }
    }

    return 0;
}
