/*
    Autores: Diego Vieira de Christo e Bruno Villa Lobus Strapasson
    GRR: 20206154 e 20215522
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <matheval.h>
#include <stdlib.h>
#include <assert.h>
#include "funcoes.h"
#define N 100
#define MAX_SIZE 1000

int main(int argc,char* argv[]) 
{
    int print = 0;
    FILE *arq = NULL;
    if (argc == 1){
        //ok
    } else if(argc == 3 && strcmp(argv[1], "-o") == 0){
        print = 1;
        arq = fopen(argv[2],"w");
        if(!arq){
            perror("erro ao abrir o arquivo.");
            return -1;
        }
    } else {
        printf("erro na entrada da linha de comando.");
        return 1;
    }

    int n = 0, k, hess_steps, max_iter;
    char resultado[100000];// referencia[1000];  // String para armazenar o resultado
    //char *str;variavel[3];
    void *f;// *f2,*f_dev, *f_dev2, *f_dev3;
    int tam;
    //int count;
    double x = 0.0, epsilon;
    //int count = 0;

    // Le os valores da entrada 
    scanf("%d %d %lf %lf %d %d", &n, &k, &x, &epsilon, &max_iter, &hess_steps);

    // Exibição dos parâmetros na saída
    printf("%d %d %.6f %.6f %d %d\n", n, k, x, epsilon, max_iter, hess_steps);
    printf("#\n");
    
    // Funcao para transfomar a funcao de Rosenbrock em uma string
    calcularPolinomio(n, k, resultado);

    //Calcular o tamanho da string resultado
    tam = strlen(resultado);
    resultado[tam-2] = '\0';

    // Cria o ponteiro da equação
    f = evaluator_create (resultado);
    if(!f)
    {
        fprintf(stderr, "Erro ao criar a equacao.\n");
        return 1;
    }
    assert(f);

    char resultado2[tam];

    strcpy(resultado2,resultado);

    // A partir daqui declaração de todos os elementos necessãrios para o caculo dos dois metodos 
    // Newton Modificado e Quasi-Newton
    // Declaracao feita basicamente 2 vezes para cada elemento, visto que os dois metodos sao calculados simultaneamente



    // Criar o vetor de ponteiros para o gradiente
    void** gradiente = (void**)malloc(sizeof(void*) * n);

    //void** gradiente2 = (void**)malloc(sizeof(void*) * n);

    // Vetor gradiente auxiliar
    double **grad_x = (double**)malloc(sizeof(double*) * n);

    // Criar a matriz de ponteiros para a Hessiana
    void*** hessiana = (void***)malloc(sizeof(void**) * n);
    for (int i = 0; i < n; i++) {
        hessiana[i] = (void**)malloc(sizeof(void*) * n);
        for (int j = 0; j < n; j++) {
            hessiana[i][j] = NULL;  // Inicializar com NULL
        }
    } 

    /*void*** hessiana2 = (void***)malloc(sizeof(void**) * n);
    for (int i = 0; i < n; i++) {
        hessiana2[i] = (void**)malloc(sizeof(void*) * n);
        for (int j = 0; j < n; j++) {
            hessiana2[i][j] = NULL;  // Inicializar com NULL
        }
    }*/

    // Cria o vetor X de acordo com o valor da entrada
    double* vet_x = (double*)malloc(sizeof(double) * n);
    for (int j = 0; j < n; j++)
    {
        // aqui era iniciado com x
        vet_x[j] = 1;
    }

   /*double* vet_x2 = (double*)malloc(sizeof(double) * n);
    for (int j = 0; j < n; j++)
    {
        vet_x2[j] = x;
    }*/

    // Declara o vetor X atual e o proximo
    double* x_atual = (double*)malloc(sizeof(double) * n);
    for(int i=0;i<n;i++){
        //aqui era iniciado com 0
        x_atual[i] = x;
    }
    double* x_proximo = (double*)malloc(sizeof(double) * n);

    /*double* x_atual2 = (double*)malloc(sizeof(double) * n);
    double* x_proximo2 = (double*)malloc(sizeof(double) * n);
    */

    // Cálculo do valor de f(X) atual
    double f_x_atual = 0.0;
    f_x_atual = calcularValorFuncao(vet_x, n);
    double f_x_proximo = 0.0;

    printf(" %f valor inicial f_x_atual \n", f_x_atual);

    /*double f_x_atual2 = calcularValorFuncao(vet_x, n);
    double f_x_proximo2;
    */

    // Ponteiro para guardar o vetor X inicial e os proximos vetores X    
    void** xPointers = (void**)malloc(sizeof(void*) * n);
    for (int j = 0; j < n; j++) {
        char variable[10];
        snprintf(variable, sizeof(variable), "x%d", j + 1);
        xPointers[j] = evaluator_create(variable);
    }  

    /*
    void** xPointers2 = (void**)malloc(sizeof(void*) * n);
    for (int j = 0; j < n; j++) {
        char variable[10];
        snprintf(variable, sizeof(variable), "x%d", j + 1);
        xPointers2[j] = evaluator_create(variable);
    }*/

    // Vetor de nomes das variáveis
    char **Nomes = (char**)malloc(sizeof(char*) * n);
    for (int j = 0; j < n; j++) {
        char variable[10];
        snprintf(variable, sizeof(variable), "x%d", j + 1);
        Nomes[j] = strdup(variable); // Copia o nome da variável para o vetor names
    }

    /*
    char **Nomes2 = (char**)malloc(sizeof(char*) * n);
    for (int j = 0; j < n; j++) {
        char variable[10];
        snprintf(variable, sizeof(variable), "x%d", j + 1);
        Nomes2[j] = strdup(variable); // Copia o nome da variável para o vetor names
    }*/

    // Vetor de termos independentes do sistema linear
    double* b = (double*)malloc(sizeof(double) * n);
    //double* b2 = (double*)malloc(sizeof(double) * n);

    // Declarar a matriz de constantes do sistema linear
    double** A = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(sizeof(double) * n);
    }

    for(int i =0;i<n;i++){
        for(int j =0;j<n;j++)
            A[i][j] = 0;
    }
    
    /*double** A2 = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        A2[i] = (double*)malloc(sizeof(double) * n);
    }*/


    // Declarar o deltaa

    double* deltaa = (double*)malloc(sizeof(double) * n);

    //double* delta2 = (double*)malloc(sizeof(double) * n);


    int iter_count = 0;
    int hess_count = 0;

    while (iter_count < max_iter) 
    {
        // Verificar o critério de parada e interromper o loop, se necessário
        if (fabs(f_x_atual) < epsilon) {
            break;
        }

        // Calcular o valor de f(X) atual
        f_x_atual = calcularValorFuncao(x_atual, n);

        //f_x_atual2 = calcularValorFuncao(x_atual2, n);

        // Calcular o gradiente
        calcularGradiente(n, resultado, gradiente);

        //calcularGradiente(n,resultado2, gradiente2);

        // Verificar se a Hessiana precisa ser atualizada
        if (hess_count == 0) {
            // Calcular a Hessiana
            calcularHessiana(n, resultado, hessiana);
        }

        //calcularHessiana(n, resultado2, hessiana2);

        for (int i = 0; i < n; i++) 
        {
            // Parte Principal do Calculo do Metodo de Newton Modificado.

            // Calcular o valor do termo independente (b[i]) usando o gradiente correspondente à variável xi
            b[i] = evaluator_evaluate(gradiente[i], n, Nomes, vet_x);

            // Preenche a matriz A com os valores da matriz Hessiana.
            for (int j = 0; j < n; j++) {
                double hessiana_value = evaluator_evaluate(hessiana[i][j], n, Nomes, vet_x);
                A[i][j] = hessiana_value;
            }

            // Resolver o sistema linear para obter o vetor de incremento deltaa
            deltaa = solve_linear_system( A, b, n);

            // Atualizar o vetor x_proximo
            for (int i = 0; i < n; i++) {
                x_proximo[i] = x_atual[i] - deltaa[i];
            }

            // Calcular o valor de f(X) para x_proximo
            f_x_proximo = calcularValorFuncao(x_proximo, n);


            // --------x---------x---------x---------x----------x----------x //
            // Parte Principal do Calculo do Metodo de Quasi-Newton
            

            // Calcular o valor do termo independente (b[i]) usando o gradiente correspondente à variável xi
            /*b2[i] = evaluator_evaluate(gradiente2[i], n , Nomes2 ,vet_x2);

            //atualiza o gradiente, formatado para entrada em calculaHK
            for(int i = 0; i< n; i++){
                grad_x[i] = gradiente2[i];
            }

            // Preenche a matriz A com os valores da matriz Hessiana.
            for (int j = 0; j < n; j++) {
                double hessiana_value2 = evaluator_evaluate(hessiana2[i][j], n, Nomes2, vet_x2);
                A2[i][j] = hessiana_value2;
            }

             //Calcula Hk+1, baseada na hessiana calculada posteriormente, a matriz hk eh atualizada durante o processo, dessa forma hk=hk+1
            
            //calculaHK(A2 ,vet_x2 , grad_x , n, k);


            // Resolver o sistema linear para obter o vetor de incremento deltaa
            //delta2 = solve_linear_system(A2 , b2 , n);

            // Atualizar o vetor x_proximo
            for (int i = 0; i < n; i++) {
                x_proximo2[i] = x_atual2[i] - delta2[i];
            }

            // Calcular o valor de f(X) para x_proximo
            f_x_proximo2 = calcularValorFuncao(x_proximo2, n);
            */
        }

        // Verificar se é necessário atualizar a Hessiana somente no metodo de Newton Modificado
        if (hess_count == hess_steps) {
            hess_count = 0;
            // Calcular a Hessiana atualizada
            calcularHessiana(n, resultado, hessiana);
        } else {
            hess_count++;
        }

        // Atualizar o valor de x_atual e f_x_atual
        for (int i = 0; i < n; i++) {
            x_atual[i] = x_proximo[i];
        }
        f_x_atual = f_x_proximo;

        /*for (int i = 0; i < n; i++) {
            x_atual2[i] = x_proximo2[i];
        }
        f_x_atual2 = f_x_proximo2;
        */

        // Exibir o valor de f(X) na tabela de saída
        printf("Iteração  |  Newton Modificado  |  Quasi-Newton DFP\n");
        printf("%-10d|  %-18lf | %-18lf\n", iter_count+1, f_x_atual, f_x_atual);

        // Incrementar o número de iterações
        iter_count++;
    }
    printf("----------------------------------------------\n");

    // Verificar se o critério de parada foi atingido
    if (fabs(f_x_atual) >= epsilon) {
        printf("\nCritério de parada não foi atingido.\n");
    }

    // Liberar a memória alocada
    for (int i = 0; i < n; i++) {
        free(hessiana[i]);
        free(Nomes[i]);
    }

    /*for (int i = 0; i < n; i++) {
        free(hessiana2[i]);
        free(Nomes2[i]);
    }*/

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }

        for (int i = 0; i < n; i++) {
        free(xPointers[i]);
    }
    
    //fclose(arq);
    free(deltaa);
    free(xPointers);
    free(hessiana);
    free(Nomes);
    free(gradiente);
    free(x_atual);
    free(x_proximo);
    free(vet_x);
    free(b);
    free(A);
    free(grad_x);
    //free(hessiana2);
    //free(Nomes2);
    //free(gradiente2);
    //free(x_atual2);
    //free(x_proximo2);
    //free(delta2);

    return 0;
}

/*
String para função rosenbrock ? ja nao eh o que a rosenbrock faz?
Vetor de x para calcular segunda derivada de cada xi gerando matriz de derivada 2x2 ? isso nao tinha entendido e acho q nao fizemos
Vetor de ponteiros para apontar para cada x ? acho que ja tem algo assim
Matriz Hessiana ?ja nao tem?
Vetor para cada X1 até xn ?? vetor pra que x?
Matriz de coeficiente avaliando cada função da matriz no ponto (x1,..., xn) da iteração atual
Matriz de dados ? o que seria a matriz de dados?
Cada xi começa valendo 1 / aqui da pra fazer iniciar com 1 
*/