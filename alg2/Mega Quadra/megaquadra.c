#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "ordenadores.h"
#include "busca.h"

#define LINE_SIZE 1024

int aleat(int n, int m){
    return (rand() % (m-n+1))+n;
}

void preenchevetorNumerosAleatorios(int *vetorNumerosAleatorios, int tamanho, int maiorValor){
    int i;
    int comp;
    for(i=0; i<tamanho; i++){
        vetorNumerosAleatorios[i] = aleat(1,maiorValor);
        while(buscaSequencial(vetorNumerosAleatorios, i, vetorNumerosAleatorios[i], &comp) != -1){
            vetorNumerosAleatorios[i] = aleat(1,maiorValor);
        }
    }
}

void printavetorNumerosAleatorios(int *vetorNumerosAleatorios, int tamanho, FILE* arq){
    int i;
    for(i=0; i<tamanho-1; i++){
        printf("%d ", vetorNumerosAleatorios[i]);
        fprintf(arq, "%d ", vetorNumerosAleatorios[i]);
    }
    printf("%d\n", vetorNumerosAleatorios[i]);
    fprintf(arq, "%d\n", vetorNumerosAleatorios[i]);
}

int* copiaVetor(int *vetorNumerosAleatorios, int tamanho){
    int *vetor = malloc(sizeof(int) * tamanho);
    for(int i=0; i<tamanho; i++)
        vetor[i] = vetorNumerosAleatorios[i];
    return vetor;
}

int main(){
    srand(time(NULL));
    clock_t tempo_medido;
    double tBuscaSeq=0, tBuscaBin=0, tSelect, tBubble, tQuickRec, tQuickIte;
    FILE* arq;
    char line[LINE_SIZE];
    int* vetorNumerosAleatorios, *vetSelect, *vetBubble, *vetQuickRec, *vetQuickIte;
    int vetorNumerosUsuario[4], numeroEscolhido;
    int i, tamanho, maiorValorPossivel, cont=0, acertos=0;
    int comp_seq=0, comp_bin=0, jogarNovamente=1, flag_repetido=0;
    
    
    arq = fopen("mega-quadra.log", "a+");
    if(fgets(line, LINE_SIZE, arq) == NULL){
        fprintf(arq, "***************************************************\n");
        fprintf(arq, "ARQUIVO DE LOG DO TRABALHO PRATICO 1 - MEGA QUADRA!\n");
        fprintf(arq, "Realizado por Matheus Souza e Bruno Strapasson\n");
        fprintf(arq, "Prof. Elias P. Duarte Jr.\n");
        fprintf(arq, "***************************************************\n");
    }

    printf("\n************************************************\n");
    printf("********** BEM VINDO(A) A MEGA QUADRA **********\n");
    printf("************************************************\n\n");
    while(jogarNovamente != 0){
        fprintf(arq, "\n\n$$ Inicio de um novo jogo $$\n\n");
        long long int compQuickRec=0, compQuickIte=0, compSelect=0, compBubble=0;
        printf("Qual o tamanho do vetor: ");
        scanf("%d", &tamanho);
        while(tamanho < 4){
            fprintf(arq, "Tamanho minimo eh 4. Tentou um valor invalido: %d\n", tamanho);
            printf("Tamanho minimo eh 4. Tente outro numero: ");
            scanf("%d", &tamanho);
        }
        fprintf(arq, "Tamanho do vetor escolhido: %d\n", tamanho);

        printf("Qual o maior valor possivel: ");
        scanf("%d", &maiorValorPossivel);
        while(maiorValorPossivel < tamanho){
            fprintf(arq, "Maior valor nao pode ser menor que o tamanho. Tentou um valor invalido: %d\n", tamanho);
            printf("Maior valor nao pode ser menor que o tamanho. Tente outro numero: ");
            scanf("%d", &maiorValorPossivel);
        }
        fprintf(arq, "Maior valor escolhido: %d\n", maiorValorPossivel);

        vetorNumerosAleatorios = malloc(sizeof(int)*tamanho);

        printf("\nFaca sua aposta!\n");
        cont = 0;
        while(cont<4){
            printf("Escolha o %d numero: ", cont+1);
            scanf("%d", &numeroEscolhido);
            while(numeroEscolhido < 1 || numeroEscolhido > maiorValorPossivel){
                printf("Valor invalido. \nDigite um valor entre 1 e %d: ", maiorValorPossivel);
                fprintf(arq, "Tentou escolher um valor invalido: %d\n", numeroEscolhido);
                scanf("%d", &numeroEscolhido);
            }

            vetorNumerosUsuario[cont] = numeroEscolhido;

            while((buscaSequencial(vetorNumerosUsuario, cont, numeroEscolhido, &comp_seq) != -1)){
                printf("Numero ja escolhido. Tente outro: ");
                fprintf(arq, "Tentou escolher um numero repetido: %d\n", numeroEscolhido);
                scanf("%d", &numeroEscolhido);
                if(numeroEscolhido > maiorValorPossivel || numeroEscolhido < 1){
                    while (numeroEscolhido < 1 || numeroEscolhido > maiorValorPossivel)
                    {
                        printf("Valor invalido. \nDigite um valor entre 1 e %d: ", maiorValorPossivel);
                        fprintf(arq, "Tentou escolher um valor invalido: %d\n", numeroEscolhido);
                        scanf("%d", &numeroEscolhido);
                    }
                }
                flag_repetido = 1;
            }

            if(flag_repetido) vetorNumerosUsuario[cont] = numeroEscolhido;

            flag_repetido = 0;
            cont++;
        }

        printf("\nValores escolhidos: ");
        fprintf(arq, "Valores escolhidos na aposta: ");
        for(i=0; i<3; i++){
            printf("%d ", vetorNumerosUsuario[i]);
            fprintf(arq, "%d ", vetorNumerosUsuario[i]);
        }
        printf("%d\n", vetorNumerosUsuario[i]);
        fprintf(arq, "%d\n", vetorNumerosUsuario[i]);

        preenchevetorNumerosAleatorios(vetorNumerosAleatorios, tamanho, maiorValorPossivel);
        vetSelect = copiaVetor(vetorNumerosAleatorios, tamanho);
        vetBubble = copiaVetor(vetorNumerosAleatorios, tamanho);
        vetQuickRec = copiaVetor(vetorNumerosAleatorios, tamanho);
        vetQuickIte = copiaVetor(vetorNumerosAleatorios, tamanho);
        printf("\nVetor antes da ordenacao: ");
        fprintf(arq, "Vetor antes da ordenacao: ");
        printavetorNumerosAleatorios(vetorNumerosAleatorios, tamanho, arq);
        printf("\n");

        
        quickSortRecursivo(vetorNumerosAleatorios, 0, tamanho-1, &compQuickRec);

        tempo_medido = clock();
        selectionSort(vetSelect, tamanho, &compSelect);
        tempo_medido = clock() - tempo_medido;
        tSelect = ((double) tempo_medido/CLOCKS_PER_SEC);

        tempo_medido = clock();
        bubbleSort(vetBubble, tamanho, &compBubble);
        tempo_medido = clock() - tempo_medido;
        tBubble = ((double) tempo_medido/CLOCKS_PER_SEC);

        compQuickRec=0;
        tempo_medido = clock();
        quickSortRecursivo(vetQuickRec, 0, tamanho-1, &compQuickRec);
        tempo_medido = clock() - tempo_medido;
        tQuickRec = ((double) tempo_medido/CLOCKS_PER_SEC);

        tempo_medido = clock();
        quickSortIterativo(vetQuickIte, 0, tamanho-1, &compQuickIte);
        tempo_medido = clock() - tempo_medido;
        tQuickIte = ((double) tempo_medido/CLOCKS_PER_SEC);
        
        printf("\nVetor depois da ordenacao: ");
        fprintf(arq, "Vetor depois da ordenacao: ");
        printavetorNumerosAleatorios(vetSelect, tamanho, arq);
        printf("\n");

        acertos = 0;
        comp_bin = 0;
        comp_seq = 0;
        for(i=0; i<4; i++){
            tempo_medido = clock();
            if(buscaSequencial(vetorNumerosAleatorios, tamanho, vetorNumerosUsuario[i], &comp_seq) != -1){
                printf("Voce acertou o numero %d!\n", vetorNumerosUsuario[i]);
                fprintf(arq, "Acertou o numero %d!\n", vetorNumerosUsuario[i]);
                if(comp_seq == 1){
                    printf("Foi realizada %d comparacao com a Busca Sequencial\n", comp_seq); 
                    fprintf(arq, "Foi realizada %d comparacao com a Busca Sequencial\n", comp_seq); 
                } else {
                    printf("Foram realizadas %d comparacoes com a Busca Sequencial\n",comp_seq);
                    fprintf(arq, "Foram realizadas %d comparacoes com a Busca Sequencial\n",comp_seq);
                }
                acertos++;   
            }
            tempo_medido = clock() - tempo_medido;
            tBuscaSeq += tempo_medido;

            tempo_medido = clock();
            if(buscaBinaria(vetorNumerosAleatorios, tamanho, vetorNumerosUsuario[i], &comp_bin) != -1){
                if(comp_bin == 1){
                    printf("Foi realizada %d comparacao com a Busca Binaria\n\n", comp_bin); 
                    fprintf(arq, "Foi realizada %d comparacao com a Busca Binaria\n\n", comp_bin); 
                } else {
                    printf("Foram realizadas %d comparacoes com a Busca Binaria\n\n", comp_bin);  
                    fprintf(arq, "Foram realizadas %d comparacoes com a Busca Binaria\n\n", comp_bin);  
                }
            }
            tempo_medido = clock() - tempo_medido;
            tBuscaBin += tempo_medido;
        }

        printf("\nComparacoes e o tempo de execucao de cada algoritmo de ordenacao: \n");
        printf("Selection Sort: %lld comparacoes em %lf s.\n", compSelect, tSelect);
        printf("Bubble Sort: %lld comparacoes em %lf s.\n", compBubble, tBubble);
        printf("Quick Sort recursivo: %lld comparacoes em %lf s.\n", compQuickRec, tQuickRec);
        printf("Quick Sort iterativo: %lld comparacoes em %lf s.\n", compQuickIte, tQuickIte);

        fprintf(arq, "\nComparacoes e o tempo de execucao de cada algoritmo de ordenacao: \n");
        fprintf(arq, "Selection Sort: %lld comparacoes em %lf s.\n", compSelect, tSelect);
        fprintf(arq, "Bubble Sort: %lld comparacoes em %lf s.\n", compBubble, tBubble);
        fprintf(arq, "Quick Sort recursivo: %lld comparacoes em %lf s.\n", compQuickRec, tQuickRec);
        fprintf(arq, "Quick Sort iterativo: %lld comparacoes em %lf s.\n", compQuickIte, tQuickIte);

        if(acertos == 0){
            printf("\nVoce nao acertou nenhum numero.\n");
            fprintf(arq, "\nNao acertou nenhum numero.\n");
        }else{
            if(acertos == 1){
                printf("\nVoce acertou %d numero!\n", acertos);
                fprintf(arq, "\nAcertou %d numero!\n", acertos);
            }else{
                printf("\nVoce acertou %d numeros!\n", acertos);
                fprintf(arq, "\nAcertou %d numeros!\n", acertos);
            }
        }

        printf("\n1 - Jogar novamente\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &jogarNovamente);
        while(jogarNovamente > 1 || jogarNovamente < 0){
            printf("Digite um valor valido: ");
            scanf("%d", &jogarNovamente);
        }

        if(jogarNovamente == 1){
            free(vetorNumerosAleatorios);
            free(vetSelect);
            free(vetBubble);
            free(vetQuickRec);
        } else {
            printf("\nAte mais!\n");
        }
    }
    
    free(vetorNumerosAleatorios);
    free(vetSelect);
    free(vetBubble);
    free(vetQuickRec);
    free(vetQuickIte);
    fclose(arq);
    return 0;
}