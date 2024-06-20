#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main(){
    struct nodo *raiz = NULL;
    struct nodo *nodo = NULL;

    char comando;
    int valor;

    imprimirDadosAlunos();

    scanf(" %c", &comando);
    
    while (comando != 'f'){
        switch(comando){
            //insere elemento na arvore
            case 'i':
                scanf("%d",&valor);
                raiz = inserir(&raiz, valor);
                break;
            //busca elemento na arvore
            case 'b':
                scanf("%d",&valor);
                nodo = buscar(raiz, valor);
                if (nodo == NULL) {
                    printf("Não encontrado %d.\n", valor);
                } else {
                    printf("Valor encontrado %d.\n", valor);
                }
                break;
            //busca e se achar remove o no
            case 'r':
                scanf("%d",&valor);
                nodo = buscar(raiz, valor);
                if(!nodo){
                    printf("Falha ao remover %d.\n", valor);
                    break;
                }
                excluir(&raiz, valor);
                break;
            //imprimir em ordem, junto com o nivel de cada no
            case 'e':
                imprimirEmOrdem(raiz,0);
                break;
            //imprimir em largura
            case 'l':
                imprimirEmLargura(raiz);
                break;
            //encerra o programa
            case 'f':
                destroiArvore(raiz);
                break;

            default:
                printf("Valor invalido.\n");
                break;
        }       
        scanf(" %c", &comando);
    }
    
    return 0;
}