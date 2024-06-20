#include "tabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matarProgramaFaltaMemoria() {
    fputs("Falha ao alocar memoria.\n", stderr);
    exit(1);
}

struct aluno* getAluno1() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if (!retorno) matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Bruno Vila Lobus Strapasson"));  // sizeof conta o \0
    if (!retorno->nome)
        matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("bvls21"));
    if (!(retorno->nomeDinf))
        matarProgramaFaltaMemoria();

    strcpy(retorno->nome, "Bruno Vila Lobus Strapasson");
    strcpy(retorno->nomeDinf, "bvls21");
    retorno->grr = 20215522;

    return retorno;
}

struct aluno* getAluno2() {
    return NULL;
}

void imprimirDadosAlunos() {
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if (!aluno) return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

// inicializa a tabela com uma lista vazia em cada posição do vetor
struct nodoHash* gerarTabelaHash(size_t tamTabela){
	struct nodoHash* tabela = (struct nodoHash*)malloc(tamTabela * sizeof(struct nodoHash));
    if (!tabela){
        printf("Erro ao alocar a tabela hash.\n");
        return NULL;
    }
    tabela->chave = 0;
    tabela->anterior = NULL;
    tabela->proximo = NULL;
	// Inicializar a tabela hash conforme necessário
	return tabela;
}

// função de espalhamento
int funcaohash(int mat,int M){
    return mat % M;
}

struct nodoHash* inserir(struct nodoHash tabelaHash[], size_t tamTabela, int chave){
    int pos = funcaohash(chave,tamTabela); // CALCULA POSIÇÃO

    struct nodoHash* lista = &tabelaHash[pos];

    if (lista != NULL) {
        if (buscar(tabelaHash,tamTabela,chave)) { // verificando se a chave já existe
            printf(" *** ATENÇÃO: O chave %d já foi cadastrado ***", chave);
            return tabelaHash;
        }
    }

    //inserelista(chave, lista);
        if (lista == NULL) {
        lista = (struct nodoHash*)malloc(sizeof(struct nodoHash));
        if (lista == NULL) {
            printf("\nErro alocação memória!");
            exit(1);
        }
        lista->chave = chave;
        lista->proximo = NULL;

        printf("-> Inserido HASH[%d]", pos);
    } else {
        printf("-> Colisão  HASH[%d]", pos);

        struct nodoHash* guarda = lista; // guardando posição inicial do ponteiro

        while (lista->proximo != NULL)
            lista = lista->proximo;

        lista->proximo = (struct nodoHash*)malloc(sizeof(struct nodoHash));
        if (lista->proximo == NULL) {
            printf("\nErro alocação memória!");
            exit(1);
        }

        lista = lista->proximo;
        lista->chave = chave;
        lista->proximo = NULL;

        tabelaHash[pos] = *guarda; // retornando ponteiro para a posição inicial
    }
    return tabelaHash;
}

void liberarTabelaHash(struct nodoHash tabelaHash[], size_t tamTabela){
    int i;
    struct nodoHash* proximo;
    for (i = 0; i < tamTabela; i++) {
        struct nodoHash* lista = &tabelaHash[i];
        while (lista != NULL) {
            proximo = lista->proximo;
            free(lista);
            lista = proximo;
        }
    }
    free(proximo);
    free(tabelaHash);
}

void imprimirTabelaHash(struct nodoHash tabelaHash[], size_t tamTabela){
    int i;
    printf(" ");
    for (i = 0; i < tamTabela; i++){
        printf("\n[%d] ->", i);
        // Percorre lista imprimindo-a
        struct nodoHash* lista = &tabelaHash[i];
        while (lista != NULL) {
            printf(" %d ->", lista->chave);
            lista = lista->proximo;
        }
        printf(" NULL");
    }
}

struct nodoHash* buscar(struct nodoHash tabelaHash[], size_t tamTabela, int chave){
    int pos = funcaohash(chave,tamTabela); // CALCULA POSIÇÃO

    struct nodoHash* lista = &tabelaHash[pos];

    while (lista != NULL) {
        if (lista->chave == chave) {
            printf("Elemento encontrado na posição HASH[%d]\n", pos);
            return lista;
        }
        lista = lista->proximo;
    }

    printf("Elemento não encontrado\n");
    return NULL;
}

void excluir(struct nodoHash tabelaHash[], size_t tamTabela, struct nodoHash* nodo){
    int pos = funcaohash(nodo->chave,tamTabela);

    if (!buscar(tabelaHash,tamTabela,nodo->chave)) {
        puts("\nItem não encontrado");
        return;
    }

    struct nodoHash* lista = &tabelaHash[pos];
    struct nodoHash* anterior = lista;
    struct nodoHash* proximo = (lista)->proximo;
    struct nodoHash* guarda = &tabelaHash[pos]; // guardando a posição do ponteiro

    while (lista != NULL) {
        if (lista == nodo) {
            if (lista == anterior) {
                if ((lista)->proximo == NULL) {
                    free(lista);
                    //tabelaHash[pos] = NULL;
                } else {
                    (lista)->proximo = proximo->proximo;
                    (lista)->chave = proximo->chave;
                    tabelaHash[pos] = *guarda;
                }
            } else {
                anterior->proximo = proximo;
                free(lista);
                tabelaHash[pos] = *guarda;
            }
            return;
        }
        anterior = lista;
        lista = (lista)->proximo;
        proximo = (lista)->proximo;
    }

    tabelaHash[pos] = *guarda; // retornando ponteiro para posição inicial
    free(anterior);
    free(proximo);
    free(guarda);
}