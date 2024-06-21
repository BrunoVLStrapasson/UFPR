#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "arff.h"

void exibe_atributos(atributo *infos, int quantidade){
  //Fun��o do A1 (com modifica��es para o atributo de categorias)
      if (infos == 0){
        printf("O arquivo ARFF fornecido � inv�lido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < quantidade; i++){
        printf("-> Atributo #%d\n", i+1);
        printf("Rotulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias){ 
        // mais um for dentro do categorias, infos[i].categorias[j]
            printf("{");    
            for(int j=0;j<infos[i].num_categorias;j++){
                printf("%s,", infos[i].categorias[j]);
            }
            printf("}\n");
        }
        
        if (i < quantidade-1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff){
    //Fun��o do A1
    int cont_dados = 0;
    char linha[1024];

    while(fgets(linha,sizeof(linha),arff)){
        if(strncmp(linha,"@data",5) == 0){
            //@data encontrado, fim do arquivo
            break; 
        }
        if(strncmp(linha,"@attribute",10) == 0){
            cont_dados++;
        }
    }

    //verifica novamente se o @data nao esta no fim do arquivo
    if((strncmp(linha,"@data",5) != 0)){
        fprintf(stderr,"@data nao encontrado.\n");
        exit(5);
    }

    return cont_dados;
}

void processa_categorias(atributo *elemento, char *categorias) {
    char **vet_categorias = NULL;
    int cont_dados = 0;
    char *separador = strtok(categorias, "{,");
    
    while (separador != NULL) {
        vet_categorias = realloc(vet_categorias, (cont_dados + 1) * sizeof(char *));
        vet_categorias[cont_dados] = strdup(separador);
        cont_dados++;
        separador = strtok(NULL,",");
    }
    
    elemento->categorias = vet_categorias;
    elemento->num_categorias = cont_dados;

}

atributo* processa_atributos(FILE *arff, int quantidade){
  //Fun��o do A1 (com modifica��es para o atributo de categorias)
    rewind(arff);
    //aloca o tamanho de memoria a ser utilizado
    atributo *info = malloc(quantidade * sizeof(atributo));
    char linha[1024],rotulo[1024],tipo[1024],*categorias,val[1024]; 

    for(int i = 0; i < quantidade; i++){
        if(fgets(linha,sizeof(linha),arff) == NULL){
                fprintf(stderr, "Erro ao ler atributo.\n");
                exit(4);
        }else if(strncmp(linha, "@attribute", 10) != 0){
            //se ler uma linha em branco, a "desconsidera"
            if(linha[0] == '\n'){
                i--;
                continue;
            }else{
                fprintf(stderr, "Erro ao processar atributo.\n");
                exit(4);
            }
        //val eh usado como validador, se tiver atributos a mais acusa erro
        }else if(sscanf(linha, "@attribute %s %s %s", rotulo, tipo, val) != 2){ 
            // Extrai o rotulo e o tipo 
            fprintf(stderr, "Erro ao extrair rotulo ou tipo.\n");
            exit(4);
        //se o tipo começar com '{' deve ser classicado como categoria,
        //copio a string tipo para categorias usando strdup para alocar o tam necessario e adicionar '\0'
        }else if(tipo[0] == '{'){
            categorias = strdup(tipo);
            strcpy(tipo,"categoric");
            if(categorias == NULL){
                fprintf(stderr, "Erro ao ler categorias.\n");
                exit(4);
            }
            // Remove o fechamento das chaves
            categorias[strlen(categorias)-1]='\0';

            //funcao que processa as categorias
            processa_categorias(&info[i],categorias);
            //ja atribui a string de categorias no meu struct atributos, posso liberar a mem alocada
            free(categorias);
        //nao ha categorias nesse atributo, seto ela como nulo
        }else{
          info[i].categorias = NULL;
          info[i].num_categorias = 0;
        }

        //incluo o rotulo e o tipo no struct atributos
        info[i].rotulo = strdup(rotulo);
        info[i].tipo = strdup(tipo);
    }

    return info;
}

void valida_arff(FILE *arff, atributo *atributos, int quantidade){
    //Recebe um arquivo arff com ponteiro de leitura antes do "@data"; passa por todas as linhas de dados e valida cada elementos de cada coluna em
    //rela��o ao vetor de atributos tamb�m fornecido como argumento.
    char linha[2048],/*linha[2048]*/**vet_dados = NULL;
    int cont_dados = 0 ; int flag = 0;int achou = 0;int tam = 0;int lin = 0;
    char *dados;
    
    //posiciona o ponteiro em @data
    while(fgets(linha,sizeof(linha),arff)){
        if(strncmp(linha,"@data",5) == 0){
            //@data encontrado
            flag = 1;
            break; 
        }
    }

    if(!flag){
        printf("Erro na validacao do arquivo arff.\n");
        exit(6);
    }

    //comeca a ler todas as linhas do arff apartir do @data, uma linha completa por vez
    while(fgets(linha,sizeof(linha),arff)){
        lin++;
        //desconsidera linhas em branco no corpo de dados, parte para a proxima leitura      
        if(strcmp(linha,"\n") == 0){
            continue;
        }
        int fim = strlen(linha);
        //desconsidera linhas sem terminacao(quebras de linhas)
        if(linha[fim-1] != '\n' ){
            continue;
        }
        //separa tudo que esta entre virgulas e salva em vet_dados para a verificacao que eh feita
        dados = strtok(linha,"{,");
        while(dados){
            vet_dados = realloc(vet_dados, (cont_dados + 1) * sizeof(char *));
            vet_dados[cont_dados] = strdup(dados);
            cont_dados++;
            dados = strtok(NULL,",");
        }
        tam = strlen(vet_dados[cont_dados-1]);

        vet_dados[cont_dados-1][tam-1] = '\0';

        //Verifica se a linha de arff tem a quantidade de dados igual a de atributos
        if(cont_dados == quantidade){
            cont_dados = 0;
            //continue;
        } else {
            fprintf(stderr,"Erro na quantidade de dados do arquivo. linha: %d\n",lin);
            exit(7);
        }
        //comeca verificacao de cada um dos atributos individualmente
        for(int i = 0;i<quantidade;i++){
            if (strcmp(atributos[i].tipo,"numeric") == 0)
            {
                // compararar vet_dados com algo que resulte se o que esta la eh numerico ou nao
                char *string;
                string = strdup(vet_dados[i]);
                int tamanho = strlen(string);
                for(int j=0;j<tamanho;j++){
                    //testa se o caractere eh um digito (isdigit)
                    if(!(isdigit(string[j]) || string[j] == '.' || string[j] == '-')){
                        fprintf(stderr,"Erro no tipo do atributo nao eh numerico no arquivo arff. linha : %d posicao: %d\n",lin,i+1);
                        exit(9);
                    }
                }   
                free(string);
            }else if(strcmp(atributos[i].tipo,"string") == 0){
                // comparar vet_dados com algo que verifique se eh uma string ou nao
                char *string;
                string = strdup(vet_dados[i]);
                int tamanho = strlen(string);
                for(int j=0;j<tamanho;j++){
                    //Testa se o caractere é alfabético ou númerco (isalnum)
                    if(!(isalnum(string[j]) || string[j] == '.')){
                        fprintf(stderr,"Erro na validacao do tipo atributo no arquivo arff. linha: %d posicao: %d\n",lin,i+1);
                        exit(9);
                    }
                }
                free(string);  
            }else if(strcmp(atributos[i].tipo,"categoric") == 0){
                char *string;
                string = strdup(vet_dados[i]);
                //printf("%s\n",string);
                //entrar em categorias e achar se que a que esta escrita em vet_dados pertence as categorias de atributos[i].categorias[j]
                for(int j=0;j<atributos[i].num_categorias;j++){
                    if(strcmp(string,atributos[i].categorias[j]) == 0){
                        achou = 1;
                        //free(string);
                        break;
                    }
                }
                free(string);
                if(achou){
                    //ok categoria encontrada
                    achou = 0;
                }else{
                    fprintf(stderr,"Categoria invalida. linha: %d posicao: %d\n",lin,i+1);
                    exit(8);
                }
            }else{
                // tipo do argumento errado 
                // sair do programa
                fprintf(stderr,"Erro no tipo de atributos.\n");
                exit(10);
            }
            free(vet_dados[i]);
        }
    }
    free(vet_dados);

    printf("Arquivo validado com sucesso.\n");
}

void liberar_categorias(atributo *elemento) {
    if (elemento->categorias != NULL) {
        for (int i = 0; i < elemento->num_categorias; i++) {
            free(elemento->categorias[i]);
        }
        free(elemento->categorias);
        elemento->categorias = NULL; 
        elemento->num_categorias = 0;
    }
}

atributo* libera_memoria(atributo *InfAtributo, int tamanho){
    if(InfAtributo == NULL){
        fprintf(stderr,"Erro ao liberar a memoria.\n");
        exit(5);
    }

    for(int i=0;i<tamanho;i++){
        free(InfAtributo[i].rotulo);
        free(InfAtributo[i].tipo);
        if(InfAtributo[i].categorias){
            free(InfAtributo[i].categorias);
        }
    }
    //tudo ok, memoria liberada
    return InfAtributo;
}