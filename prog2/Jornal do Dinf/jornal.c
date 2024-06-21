#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char titulo[33];
    char conteudo[513];
    int idade;    
}Noticia;

typedef struct auxElem {
    Noticia elem;
    struct auxElem* ant;
    struct auxElem* prox;
}No;


typedef struct {
    No* cabeca;
}Fila;

void InicializarFila(Fila* f) {
    f->cabeca = (No*) malloc(sizeof(No));
    f->cabeca->prox = f->cabeca;
    f->cabeca->ant = f->cabeca;
    f->cabeca->elem.idade = 0;
}

int tamanho(Fila* f) {
    No* end = f->cabeca->prox; 
    int tam = 0;
    while (end != f->cabeca) {
        tam++;
        end = end->prox;
    }
    return tam;
}

int InserirElemFim(Fila* f, Noticia elem) {
    No* novo = (No*) malloc(sizeof(No));
    novo->elem = elem;
    novo->prox = f->cabeca;
    novo->ant = f->cabeca->ant;
    f->cabeca->ant = novo;
    novo->ant->prox = novo;
    return 0;
}

int ExcluirElemIni(Fila* f) {
    if (f->cabeca->prox == f->cabeca) return 1;
    No* apagar = f->cabeca->prox;
    f->cabeca->prox = apagar->prox;
    apagar->prox->ant = f->cabeca;
    free(apagar);
    return 0;
}

void EsvaziarFila(Fila* f) {
    No* end = f->cabeca->prox;
    while (end != f->cabeca) {
    No* apagar = end;
    end = end->prox;
    free(apagar);
    }
    f->cabeca->prox = f->cabeca;
    f->cabeca->ant = f->cabeca;
}

int Idade(Fila*f){
    return f->cabeca->elem.idade;
}

int AtualizaIdade(Fila* f) {
    No* end = f->cabeca->prox; 
    while (end != f->cabeca) {
        end->elem.idade++;
        end = end->prox;
    }
    return end->elem.idade;
}

void requisita(char *titulo, char *texto){
    getchar();
    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

void imprimirtitulo(Fila* f){
    No* aux = f->cabeca->prox;
    printf("\n< ");
    printf("%s", aux->elem.titulo);
    printf("\n");
    printf("< %s \n", aux->elem.conteudo);
    printf("==\n");
}

int main(){

    int opcao,flag = 0, idade1=0,idade2=0;
    int avalia = 0,tam1=0,tam2=0,cont1 = 0 ,cont2 = 0;

    char titulo[33],texto[513];
    Noticia n;
    Fila f1,f2;
    InicializarFila(&f1);
    InicializarFila(&f2);

    do{

        printf("\n- (1) Cadastrar Noticia \n- (2) Fechar Edicao \n- (3) Sair \n ");
        scanf("%d", &opcao);

        switch(opcao){

            case 3: //Finalizar

                flag = 1;
                EsvaziarFila(&f1);
                EsvaziarFila(&f2);
                break;

            case 2: // Avalia as filas e fecha a edicao com impressao da noticia e atualizacoes necessarias

                //atuliza a idade de todas as noticias presentes na fila
                AtualizaIdade(&f1);
                AtualizaIdade(&f2);

                //Recebe a idade
                idade1 = Idade(&f1);
                idade2 = Idade(&f2);
                //como atualizo a idade no comeco entao comparo para idade > 3, a noticia mais antiga estara no comeco.
                // Pois sempre removemos o primeiro elemento, se for necessario atualiza e remove o proximo.
                while(idade1 > 3){
                    ExcluirElemIni(&f1);
                        idade1 = Idade(&f1);
                }
                // mesma coisa com a fila 2
                while(idade2 > 3){
                    ExcluirElemIni(&f2);
                        idade2 = Idade(&f2);
                }

                // inicio da impressao e atualizacao das filas

                tam1 = tamanho(&f1);
                tam2 = tamanho(&f2);
                // 0 Breaking News e 0 informes
                if(tam1 == 0 && tam2 == 0){
                    printf("\nEsta edição foi pulada por falta de noticias.\n");
                    break;
                }
                printf("\n=============================\n");
                cont1 = tam1;
                cont2 = tam2;
                //2 ou mais breaking News
                if(cont1 >= 2){
                    while(cont1 > tam1-2){
                        imprimirtitulo(&f1);
                        ExcluirElemIni(&f1);
                        cont1--;
                    }
                    printf("=============================\n");
                    break;
                }
                // 1 Breaking New e pelo menos 1 informe
                else if(cont1 == 1){
                    imprimirtitulo(&f1);
                    ExcluirElemIni(&f1);
                    if(tam2 >= 1){
                        imprimirtitulo(&f2);
                        ExcluirElemIni(&f2);
                    }
                    printf("=============================\n");                    
                    break;
                }
                // Nenhuma Breaking News
                else{ 
                    // 2 ou mais informes
                    if(cont2 >= 2){
                        while(cont2 > tam2-2){
                            imprimirtitulo(&f2);
                            ExcluirElemIni(&f2);
                            cont2--;
                        }
                        printf("=============================\n");
                        break;
                    }
                    // 1 informe
                    else{
                        imprimirtitulo(&f2);
                        ExcluirElemIni(&f2);
                        printf("=============================\n");
                        break;
                    }
                }
                break;

            case 1: //Insercao das Noticias

                requisita(titulo,texto);
                printf("\nEscolha se sua noticia eh (0) Breaking News ou (1) Informe.\n");
                //strcpy(n.titulo,titulo);
                //strcpy(n.conteudo,texto);
                for(int i=0;i< 33;i++){
                    n.titulo[i] = titulo[i];
                }
                for(int i=0;i< 513;i++){
                    n.conteudo[i] = texto[i];
                }
                scanf("%d", &avalia);
                if(avalia == 0){
                    InserirElemFim(&f1,n);
                }else{
                    InserirElemFim(&f2,n);
                }
                break;
        }

    }while(!flag);

    return 0;
}

