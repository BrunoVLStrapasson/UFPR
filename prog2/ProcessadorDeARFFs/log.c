#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "log.h"
#include "lista.h"
#include "arff.h"

int Ajusta_Ponteiro(FILE *arff){
    char linha[1024];
        while(fgets(linha,sizeof(linha),arff)){
        if(strncmp(linha,"@data",5) == 0){
            //@data encontrado
            break; 
        }
    }

    return 1;
}

Lista* avalia_nomes(Lista* l,char* vet_dados){
    int achou = 0;
    char* string;
    char* ip = "vazio\0";

    No* aux = l->cabeca->prox;
    while(aux != l->cabeca){
        if(strcmp(aux->elem->nome,vet_dados) == 0){
            achou = 1;
            aux->elem->qnt_IP++;    
            break;
        }
        aux = aux->prox;
    }

    if(!achou){
        Avalia_Elem *Elemento;
        Elemento = (Avalia_Elem*)malloc(sizeof(Avalia_Elem));
        if(!Elemento){
            printf("Erro ao alocar memoria.\n");
            exit(10);
        }
        Elemento->IP = malloc(16 * sizeof(char));
        Elemento->nome = malloc(16 * sizeof(char));
        for(int j = 0; j< 16; j++){
            Elemento->IP[j] = ' ';
            Elemento->IP[j] = ' ';
        }
        Elemento->qnt_IP = 0;
        Elemento->tam_pkt = 0; 
        //atribui os valores ao novo nodo que sera inserido na lista
        Elemento->qnt_IP = 1;
        strcpy(Elemento->IP,ip);
        string = strdup(vet_dados);
        strcpy(Elemento->nome,string); 

        InserirElemFim(l,Elemento);
        free(string);
    }

    return l;
}

int avalia_ataques(FILE *arff, atributo *atributos,FILE* saida){
    char linhas[2048],**vet_dados = NULL;
    int cont = 0 ;
    char *dados;
    Lista l;
    InicializarLista(&l);

    //acho a posicao de PKT_CLASS no meu vetor de atributos 
    int j=0;
    while(strcmp(atributos[j].rotulo,"PKT_CLASS") != 0){j++;}
    
    //ajusto o ponteiro do arquivo parando em @data
    Ajusta_Ponteiro(arff);

    //comeca a ler todas as linhas do arff apartir do @data, uma linha completa por vez
    while(fgets(linhas,sizeof(linhas),arff)){      
        //separa tudo que esta entre virgulas e salva em vet_dados para a verificacao que eh feita
        //em seguida no corpo dessa mesma funcao
        dados = strtok(linhas,"{,");
        cont = 0;
        while(dados){
            vet_dados = realloc(vet_dados, (cont + 1) * sizeof(char *));
            vet_dados[cont] = strdup(dados);
            cont++;
            dados = strtok(NULL,",");
        }
        int tam = strlen(vet_dados[cont-1]);
        //ajusta o fim da string com o /0
        vet_dados[cont-1][tam-1] = '\0';

        //comparo o nome do ataque que esta em vet_dados com todas a posicoes posiveis do atributo PKT_CLASS
        for(int i=0;i<atributos[j].num_categorias;i++){
            if(strncmp(vet_dados[j],"Normal",5) == 0){
                //apenas sai do laço "Normal" nao eh um ataque
                break;
            }else if(strcmp(vet_dados[j],atributos[j].categorias[i]) == 0){
                avalia_nomes(&l,vet_dados[j]);
            }
        }
        //Libera o vetor alocado 
        for(int i =0;i<cont;i++){
            free(vet_dados[i]);
        }
    }

    //registra os ataques no arquivo de saida
    No* end = l.cabeca->prox; 
    while (end != l.cabeca){
        fprintf(saida,"%s;%d\n",end->elem->nome,end->elem->qnt_IP);
        end = end->prox;
    }
    //libera vetor de dados
    free(vet_dados);
    //libera memoria da lista
    EsvaziarLista(&l);

    printf("Ataques processados com sucesso.\n");

    return 1;
}

Lista* avalia_ips_entidades(Lista* l,char* nome_array,char* ip_array){
    int achou = 0;
    char* string_N;
    char* string_P;

    No* aux = l->cabeca->prox;
    while(aux != l->cabeca){
        if(strcmp(aux->elem->IP,ip_array) == 0){
            achou = 1;
            if(strcmp(aux->elem->nome,nome_array) == 0){
                aux->elem->qnt_IP++;
            }
            break;
        }
        aux = aux->prox;
    }

    if (!achou) {
        Avalia_Elem *Elemento;
        Elemento = (Avalia_Elem*)malloc(sizeof(Avalia_Elem));
        if(!Elemento){
            printf("Erro ao alocar memoria.\n");
            exit(10);
        }
        Elemento->IP = malloc(16 * sizeof(char));
        Elemento->nome = malloc(16 * sizeof(char));
        for(int j = 0; j< 16; j++){
            Elemento->IP[j] = ' ';
            Elemento->IP[j] = ' ';
        }
        Elemento->qnt_IP = 0;
        Elemento->tam_pkt = 0; 
        // Não é um IP duplicado, adicione à lista
        string_P = strdup(ip_array);
        strcpy(Elemento->IP, string_P);
        string_N = strdup(nome_array);
        strcpy(Elemento->nome, string_N);
        Elemento->qnt_IP = 1;
        InserirElemFim(l,Elemento);
        //libera a memoria alocada nos strings
        free(string_P);
        free(string_N);
        //free(Elemento);
    }

    return l;
}

int avalia_entidades(FILE *arff, atributo *atributos,FILE* saida){
    char linhas[2048],**vet_dados = NULL;
    int cont = 0;
    char *dados;
    Lista l;
    InicializarLista(&l);
    
    //acho que posicao de PKT_CLASS no meu vetor de atributos 
    int j=0;
    while(strcmp(atributos[j].rotulo,"PKT_CLASS") != 0){j++;}
    
    //acho que posiccao SRC_ADD no meu vetor de atributos
    int k = 0;
    while(strcmp(atributos[k].rotulo,"SRC_ADD") != 0){k++;}   
    
    //Posiciono o ponteiro em @data
    Ajusta_Ponteiro(arff);

    //comeco a ler linha a linha a parte de dados do arquivo
    while(fgets(linhas,sizeof(linhas),arff)){      
        //separa tudo que esta entre virgulas (dados do arquivo) e salva em vet_dados, 
        //em seguida chamo a funcao para avaliar e classificar a entidade dessa linha
        dados = strtok(linhas,"{,");
        cont = 0;
        while(dados){
            vet_dados = realloc(vet_dados, (cont + 1) * sizeof(char *));
            vet_dados[cont] = strdup(dados);
            cont++;
            dados = strtok(NULL,",");
        }
        int tam = strlen(vet_dados[cont-1]);
        //ajusta o fim da string com o /0
        vet_dados[cont-1][tam-1] = '\0';

        avalia_ips_entidades(&l,vet_dados[j],vet_dados[k]);

        //Libera o vetor alocado 
        for(int i =0;i<cont;i++){
            free(vet_dados[i]);
        }
    }   

    //registra as entidades no arquivo de saida
    No* end = l.cabeca->prox; 
    while (end != l.cabeca) {
        if(strcmp(end->elem->nome,"Normal") == 0){
            fprintf(saida,"%s;benigna\n",end->elem->IP);
        }else if(end->elem->qnt_IP >= 1 && end->elem->qnt_IP <= 5){
            fprintf(saida,"%s;potencialmente maliciosa\n",end->elem->IP);
        }else{ //(end->elem->IP > 5){ 
            fprintf(saida,"%s;maliciosa\n",end->elem->IP);
        }
        end = end->prox;
    }
    //libera vetor de dados
    free(vet_dados);
    //libera memoria da lista
    EsvaziarLista(&l);

    printf("Entidades processadas com sucesso.\n");

    return 1;
}

Lista* avalia_ips_tam(Lista* l,char* nome_array,char* tam_array){
    int achou = 0;
    int valor = 0 ;
    char *string;

    No* aux = l->cabeca->prox;
    while(aux != l->cabeca){
        if(strcmp(aux->elem->nome,nome_array) == 0){
            valor = atoi(tam_array);
            aux->elem->tam_pkt+=valor;
            aux->elem->qnt_IP++;
            achou = 1;
        }
        aux = aux->prox;
    }

    if (!achou){
        Avalia_Elem *Elemento;
        Elemento = (Avalia_Elem*)malloc(sizeof(Avalia_Elem));
        if(!Elemento){
            printf("Erro ao alocar memoria.\n");
            exit(10);
        }
        Elemento->qnt_IP = 1;
        Elemento->tam_pkt = 0;
        Elemento->IP = malloc(16 * sizeof(char));
        Elemento->nome = malloc(16 * sizeof(char));
        for(int j = 0; j< 16; j++){
            Elemento->IP[j] = ' ';
            Elemento->IP[j] = ' ';
        }
        if(strcmp(nome_array,"Normal") != 0){
            valor = atoi(tam_array);
            Elemento->tam_pkt += valor;
            string = strdup(nome_array);
            strcpy(Elemento->nome,string);
            Elemento->qnt_IP = 1;
            InserirElemFim(l,Elemento);
            free(string);
        }
    }

    return l;
}

int avalia_tamanho(FILE *arff, atributo *atributos,FILE* saida){
    char linhas[2048],**vet_dados = NULL;
    int cont = 0;
    char *dados;
    Lista l;
    InicializarLista(&l);

    //acho que posicao de PKT_CLASS no meu vetor de atributos 
    int j=0;
    while(strcmp(atributos[j].rotulo,"PKT_CLASS") != 0){j++;}
    
    //acho que posiccao PKT_AVG_SIZE. no meu vetor de atributos(tamanho do pacote)
    int k = 0;
    while(strcmp(atributos[k].rotulo,"PKT_AVG_SIZE") != 0){k++;}
    
    //ajusto o ponteiro para o @data
    Ajusta_Ponteiro(arff);

    //comeco a ler os dados do arquivo, linha a linha
    while(fgets(linhas,sizeof(linhas),arff)){      
        //separa tudo que esta entre virgulas e salva em vet_dados para a verificacao que eh feita
        //em seguida no corpo dessa mesma funcao
        dados = strtok(linhas,"{,");
        cont = 0;
        while(dados){
            vet_dados = realloc(vet_dados, (cont + 1) * sizeof(char *));
            vet_dados[cont] = strdup(dados);
            cont++;
            dados = strtok(NULL,",");
        }
        int tam = strlen(vet_dados[cont-1]);
        //ajusta o fim da string com o /0
        vet_dados[cont-1][tam-1] = '\0';

        for(int i=0;i<atributos[j].num_categorias;i++){
            if(strncmp(vet_dados[j],"Normal",5) == 0){
                //apenas sai do laço "Normal" nao eh um ataque
                break;
            }else if(strcmp(vet_dados[j],atributos[j].categorias[i]) == 0){
                avalia_ips_tam(&l,vet_dados[j],vet_dados[k]);
            }
        }
        //Libera o vetor alocado 
        for(int i =0;i<cont;i++){
            free(vet_dados[i]);
        }
    }

    //registra a media do tamanho dos ataques no arquivo de saida
    No* end = l.cabeca->prox; 
    while (end != l.cabeca) {
        fprintf(saida,"%s;%d\n",end->elem->nome,end->elem->tam_pkt/end->elem->qnt_IP);
        end = end->prox;
    }
    //libera vetor de dados
    free(vet_dados);
    //libera memoria da lista
    EsvaziarLista(&l);

    printf("Tamanhos processados com sucesso.\n");

    return 1;
}

Lista* avalia_ips_blist(Lista* l,char* nome_array,char* ip_array){
    int achou = 0;
    char* string_N;
    char* string_P;

    No* aux = l->cabeca->prox;
    while(aux != l->cabeca){
        if(strcmp(aux->elem->IP,ip_array) == 0){
            achou = 1;
            if(strcmp(aux->elem->nome,nome_array) == 0){
                aux->elem->qnt_IP++;
            }
            break;
        }
        aux = aux->prox;
    }

    if (!achou){
        Avalia_Elem *Elemento;
        Elemento = (Avalia_Elem*)malloc(sizeof(Avalia_Elem));
        if(!Elemento){
            printf("Erro ao alocar memoria.\n");
            exit(10);
        }
        Elemento->qnt_IP = 1;
        Elemento->tam_pkt = 0;
        Elemento->IP = malloc(16 * sizeof(char));
        Elemento->nome = malloc(16 * sizeof(char));
        for(int j = 0; j< 16; j++){
            Elemento->IP[j] = ' ';
            Elemento->IP[j] = ' ';
        }
        // Não é um IP duplicado, adicione à lista
        string_P = strdup(ip_array);
        string_N = strdup(nome_array);
        strcpy(Elemento->IP, string_P);
        strcpy(Elemento->nome, string_N);
        Elemento->qnt_IP = 1;
        InserirElemFim(l,Elemento);
        //libera a memoria dos strings
        free(string_N);
        free(string_P);
    }

    return l;
}

int black_list(FILE *arff, atributo *atributos,FILE* saida){
    char linhas[2048],**vet_dados = NULL;
    int cont = 0;
    char *dados;
    Lista l;

    InicializarLista(&l);

    //acho que posicao de PKT_CLASS no meu vetor de atributos 
    int j=0;
    while(strcmp(atributos[j].rotulo,"PKT_CLASS") != 0){j++;}
    
    //acho que posiccao SRC_ADD no meu vetor de atributos
    int k = 0;
    while(strcmp(atributos[k].rotulo,"SRC_ADD") != 0){k++;}
    
    //ajusta o ponteiro para @data
    Ajusta_Ponteiro(arff);

    //comeco a ler os dados do arquivo, linha a linha
    while(fgets(linhas,sizeof(linhas),arff)){      
        //separa tudo que esta entre virgulas e salva em vet_dados para a verificacao que eh feita
        //em seguida no corpo dessa mesma funcao
        dados = strtok(linhas,"{,");
        cont = 0;
        while(dados){
            vet_dados = realloc(vet_dados, (cont + 1) * sizeof(char *));
            vet_dados[cont] = strdup(dados);
            cont++;
            dados = strtok(NULL,",");
        }
        int tam = strlen(vet_dados[cont-1]);
        //ajusta o fim da string com o /0
        vet_dados[cont-1][tam-1] = '\0';

        avalia_ips_blist(&l,vet_dados[j],vet_dados[k]);

        //Libera o vetor alocado 
        for(int i =0;i<cont;i++){
            free(vet_dados[i]);
        }
    }   

    //registra a Blist no arquivo de saida
    No* end = l.cabeca->prox; 
    while (end != l.cabeca) {
        if(end->elem->qnt_IP > 5 && strcmp(end->elem->nome,"Normal") !=0){
            fprintf(saida,"%s\n",end->elem->IP);
        }
        end = end->prox;
    }
    //libera vetor de dados
    free(vet_dados);
    //libera memoria da lista
    EsvaziarLista(&l);

    printf("Black list criada com sucesso.\n");

    return 1;
}
