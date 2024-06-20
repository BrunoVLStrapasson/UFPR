#include <stdio.h>

#include "tabelaHash.h"

int main(){
    int M;
	imprimirDadosAlunos();

    scanf("%d",&M);

    struct nodoHash* tabela = gerarTabelaHash(M);
    char opcao;
    int valor;
    struct nodoHash* retorno;

    gerarTabelaHash(M);
    printf("f - Sair\ni - Inserir\nb - Buscar\nl - Imprimir tabela\nr - Remover\n");
    scanf("%c",&opcao);
    //printf("\n");
    do{
        scanf("%c",&opcao);
        switch(opcao){

            case 'f':
                //finalizar
                printf("fim da execução.\n");
                liberarTabelaHash(tabela,M);
                    break;
            case 'i':
                printf("Qual valor desseja inserir? ");
                scanf("%d", &valor);
                printf("\n");
                inserir(tabela, M ,valor);
                    break;
            case 'b':
                printf("Qual valor desseja buscar? ");
                scanf("%d", &valor);
                //printf("\n");
                retorno = buscar(tabela, M , valor);
                if(retorno != 0){
                    printf("Valor encontrado: %d\n", retorno->chave);
                }else{
                    printf("Valor nao encontrado!\n");
                }
                break;
            case 'l':
                imprimirTabelaHash(tabela,M);
                break;
            case 'r':
                printf("Qual valor desseja remover? ");
                scanf("%d", &valor);
                excluir(tabela, M,valor);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        //printf("f - Sair\ni - Inserir\nb - Buscar\nl - Imprimir tabela\nr - Remover\n");
        //printf("\n");
    }while(opcao != 'f');
    
    return 0;
}