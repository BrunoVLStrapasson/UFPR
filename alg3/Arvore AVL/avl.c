
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"

//substitua por seus dados
struct aluno* getAluno1(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Bruno Vila Lobus Strapasson"));//sizeof conta o \0
	if(!retorno->nome)
		exit(1);
    retorno->nomeDinf = malloc(sizeof("bvls21"));
    if(!retorno->nomeDinf)
        exit(1);
    
	strcpy(retorno->nome, "Bruno Vila Lobus Strapasson");
    strcpy(retorno->nomeDinf, "bvls21");
    retorno->grr = 20215522;

	return retorno;
}

struct aluno* getAluno2(){
    return NULL;
}

void imprimirDadosAlunos(){
    struct aluno* aluno = getAluno1();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;
    
    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

// Retorna um ponteiro para um novo no
struct nodo *criaNo(int chave){
    struct nodo *no = malloc(sizeof(struct nodo));
    if (! no){
        perror("Falha ao alocar no\n");
        return NULL;
    }

    no->chave = chave;
    no->altura = 0;
    no->nivel = 0;
    no->dir = NULL;
    no->esq = NULL;

    return no;
}

// Calcula a altura de um no da arvore
int alturaNo(struct nodo* no){
    int altEsq = 0;
    int altDir = 0;

    if (no == NULL){
        return -1;
    }

    altEsq = alturaNo(no->esq);
    altDir = alturaNo(no->dir);


    if (altEsq > altDir){
        return altEsq + 1;
    }else{
        return altDir + 1;
    }
}

// Calcula a profundidade de um no da arvore. Com travessia pre-ordem
void profundidadeNo(struct nodo *no, int nivel){
    if (no == NULL)
        return;

    no -> nivel = nivel; 
    profundidadeNo(no->esq, nivel+1);
    profundidadeNo(no->dir, nivel+1);
}

// Calcula o Fator de Balanceamento de um no da arvore
int calculaFb(struct nodo *no){
    if (no->esq == NULL && no->dir == NULL)
        return 0;

    return alturaNo(no->esq) - alturaNo(no->dir);}

// Atualiza a altura de todos nos da arvore
void atualizaAlt(struct nodo *raiz){
    if (raiz == NULL)
        return;
    
    atualizaAlt(raiz->esq);
    raiz->altura = alturaNo(raiz);
    atualizaAlt(raiz->dir);
}

// Realiza a rotação para esquerda e retorna a nova raiz
struct nodo *rotEsq(struct nodo *x){
    struct nodo *y = x->dir;
    struct nodo *T2 = y->esq;
  
    //atualiza os ponteiros
    y->esq = x;
    x->dir = T2;
  
    //atualiza altura da arvore
    atualizaAlt(x);
    atualizaAlt(y);
  
    return y;
}

// Realiza a rotação para direita e retorna a nova raiz
struct nodo *rotDir(struct nodo *y){
    struct nodo *x = y->esq;
    struct nodo *T2 = x->dir;
  
    //atualiza os ponteiros
    x->dir = y;
    y->esq = T2;
  
    //atualiza altura da arvore
    atualizaAlt(y);
    atualizaAlt(x);

    return x;
}

//Faz o re-balanceamento da arvore
struct nodo *balanceiaAvl(struct nodo* raiz, int chave){
    struct nodo* noBal;
    if(calculaFb(raiz) > 1){
        if(calculaFb(raiz->esq) < 0)
            raiz->esq = rotEsq(raiz->esq);
        noBal = rotDir(raiz);
    }
    else if(calculaFb(raiz) < -1){
        if(calculaFb(raiz->dir) > 0)
            raiz->dir = rotDir(raiz->dir);
        noBal = rotEsq(raiz);
    }

    atualizaAlt(raiz);

    return noBal;
}

//insere um novo no na arvore
struct nodo* inserir(struct nodo** raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = criaNo(chave);
        return *raiz;
    }
    
    if (chave > (*raiz)->chave) {
        (*raiz)->dir = inserir(&((*raiz)->dir), chave);
    }
    else if (chave < (*raiz)->chave) {
        (*raiz)->esq = inserir(&((*raiz)->esq), chave);
    }
    else {
        printf("Falha ao inserir.\n");
        return NULL;
    }

    atualizaAlt(*raiz);

    *raiz = balanceiaAvl(*raiz, chave);
    
    return *raiz;
}

//remove um no da arvore
int excluir(struct nodo** raiz, int chave) {
    if (*raiz == NULL)
        return 0;
    
    if ((*raiz)->chave == chave) {
        struct nodo* aux = *raiz;
        
        // Caso 1: nó folha (sem filhos)
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            free(aux);
            *raiz = NULL;
            return 1;
        }
        // Caso 2: nó com dois filhos
        else if ((*raiz)->esq != NULL && (*raiz)->dir != NULL) {
            aux = (*raiz)->esq;
            while (aux->dir != NULL)
                aux = aux->dir;
            (*raiz)->chave = aux->chave;
            return excluir(&((*raiz)->esq), aux->chave);
        }
        // Caso 3: nó com um filho
        else {
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(aux);
            return 1;
        }
    }
    else if (chave < (*raiz)->chave)
        return excluir(&((*raiz)->esq), chave);
    else
        return excluir(&((*raiz)->dir), chave);
}

//busca um no na arvore, se achar retorna o no
struct nodo* buscar(struct nodo* raiz, int chave){   
    if (raiz == NULL)
        return NULL;

    if (raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

//imprime a arvore em ordem, junto imprime o nivel de cada no
void imprimirEmOrdem(struct nodo* raiz,int nivel){
    if (raiz == NULL)
        return;
    
    imprimirEmOrdem(raiz->esq, nivel+1);
    printf("%d, %d \n", raiz->chave, nivel);
    imprimirEmOrdem(raiz->dir, nivel+1);
}

//imprime a arvore em largura
void imprimirEmLargura(struct nodo* raiz){
    if (raiz == NULL)
        return;

    int nivelAtual = 1;
    int proximoNivel = 0;
    int indicedalinha = 0;

    // Inicializa um array para armazenar os nós de um nível
    struct nodo** fila = malloc(sizeof(struct nodo*) * 100); // Tamanho máximo da largura da árvore
    int indiceInicioFila = 0;
    int indiceFimFila = 0;

    fila[indiceFimFila++] = raiz;

    printf("[%d]", indicedalinha);

    while (indiceInicioFila < indiceFimFila) {
        struct nodo* nodoAtual = fila[indiceInicioFila++];
        nivelAtual--;

        printf("%d (%d) ", nodoAtual->chave, nodoAtual->nivel);

        if (nodoAtual->esq != NULL) {
            fila[indiceFimFila++] = nodoAtual->esq;
            proximoNivel++;
        }
        if (nodoAtual->dir != NULL) {
            fila[indiceFimFila++] = nodoAtual->dir;
            proximoNivel++;
        }

        if (nivelAtual == 0) {
            nivelAtual = proximoNivel;
            proximoNivel = 0;
            indicedalinha++;
            printf("\n");
            printf("[%d] ", indicedalinha);
        }
    }

    free(fila);
}

// Libera a memoria da arvore
void destroiArvore(struct nodo *raiz)
{
    if (raiz == NULL)
        return;
    destroiArvore(raiz->esq);
    destroiArvore(raiz->dir);
    free(raiz);
}