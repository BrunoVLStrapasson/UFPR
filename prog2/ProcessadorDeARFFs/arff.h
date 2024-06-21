#ifndef __ARFF__
#define __ARFF__


typedef struct {
  char *rotulo;
  char *tipo;
  char **categorias;//vetor de strings
  int num_categorias;
} atributo;

void exibe_atributos(atributo *infos, int quantidade);
int conta_atributos(FILE *arff);
void processa_categorias(atributo *elemento, char *categorias);
atributo* processa_atributos(FILE *arff, int quantidade);
void valida_arff(FILE *arff, atributo *atributos, int quantidade);

atributo* libera_memoria(atributo *InfAtributo, int tamanho);

void liberar_categorias(atributo *elemento);


#endif