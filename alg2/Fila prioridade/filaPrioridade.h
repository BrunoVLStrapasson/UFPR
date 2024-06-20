#include <stdbool.h>

#define TAM_MAX 1001

typedef struct {
    int id;
    char nome[50];
    int prioridade;
} Paciente;

typedef struct {
    Paciente pacientes[TAM_MAX];
    int tamanho;
} FilaPrioridade;

Paciente cadastraPaciente(FilaPrioridade *fila);
FilaPrioridade *criaFilaPrioridade();
bool liberaFilaPrioridade(FilaPrioridade *fila);
int tamanhoFila(FilaPrioridade *fila);
bool filaCheia(FilaPrioridade *fila);
bool filaVazia(FilaPrioridade *fila);
bool insereElemento(FilaPrioridade *fila);
bool removeElemento(FilaPrioridade *fila);
bool sacodeHeap(FilaPrioridade *fila, int n, int *comp);
bool imprimeFilaPrioridade(FilaPrioridade *fila);
bool checaHeap(FilaPrioridade *fila);
bool heapfy(FilaPrioridade *fila, int *comp);
bool heapSort(FilaPrioridade *fila, int *compHeapSort, int *compHeapfy);
bool alteraPrioridadePaciente(FilaPrioridade *fila);
bool filaExiste(FilaPrioridade *fila);
FilaPrioridade *geradorFilaAleatoria(int quantidadeElementos);