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

#define N 100

// Funcao para transformar a expressao matematica dos somatorios em uma string 
// Recebe os valores de quanto vai ser o numero de polinomios produzidos e uma string para armazenar o resultado
void calcularPolinomio(int n, int k, char* resultado)
{
    char termo[50];
    strcpy(resultado, "");  // Limpar a string do resultado

    for (int i = 1; i <= n - (k/2); i++) 
    {
        sprintf(termo, "(x%d - (", i);

        // Concatenar o termo ao resultado, com limite de tamanho
        strncat(resultado, termo, 1000 - strlen(resultado) - 1);

        // Somatório interno
        for (int j = 1; j <= (k/2); j++) 
        {
            sprintf(termo, "(x%d)^%d", i + j, j);
            
            // Concatenar o termo ao resultado, com limite de tamanho
            strncat(resultado, termo, 1000 - strlen(resultado) - 1);

            if (j < k/2) {
                strcat(resultado, " + ");
            }

        }

        // xi - somatoriointerno (que eh o resultado)
        sprintf(termo, ")");
        strncat(resultado, termo, 1000 - strlen(resultado) - 1);

        sprintf(termo, ")^2 + ");
        strncat(resultado, termo, 1000 - strlen(resultado) - 1);

        if (i < n - k) {
            strcat(resultado, " + ");
        }

        // Verificar se o limite máximo de caracteres foi atingido
        if (strlen(resultado) >= 1000) {
            break;
        }
    }
}

// Funcao que calcula o vetor gradiente recebe para quantos xi vai ser calculado o vetor gradiente
// Recebe o ponteiro para equacao de string e o vetor de ponteiros para armazenar as primeiras derivadas 
void calcularGradiente(int n, char* resultado, void** gradiente)
{
    void* f;
    char** names;
    int count;

    for (int j = 0; j < n; j++) {
        char variavel[10];
        sprintf(variavel, "x%d", j + 1);

        f = evaluator_create(resultado);
        assert(f);

        evaluator_get_variables(f, &names, &count);
        void* f_dev = evaluator_derivative(f, variavel);

        gradiente[j] = f_dev;

        evaluator_destroy(f);
    }
}

// Funcao que calcula a matriz Hessiana para quantos xi vai ser calculado a Matriz Hessiana
// Recebe o ponteiro para equacao de string e a Matriz de ponteiros para armazenar as segundas derivadas
void calcularHessiana(int n, char* resultado, void*** hessiana) 
{
    void *f, *f2, *f_dev, *f_dev2, *f_dev3;
    char** names;
    int count;

    for (int j = 0; j < n; j++) 
    {

        char variavel[10];
        sprintf(variavel, "x%d", j + 1);

        f = evaluator_create(resultado);
        assert(f);

        evaluator_get_variables(f, &names, &count);
        f_dev = evaluator_derivative(f, variavel);

        for (int k = 0; k < n; k++) {
            char variavel2[10];
            sprintf(variavel2, "x%d", k + 1);

            char f_copy[1000];
            strcpy(f_copy, resultado);

            f2 = evaluator_create(f_copy);
            assert(f2);

            evaluator_get_variables(f2, &names, &count);
            f_dev2 = evaluator_derivative(f2, variavel);

            f_dev3 = evaluator_derivative(f_dev2, variavel2);

            evaluator_destroy(f2);
            evaluator_destroy(f_dev2);
            hessiana[j][k] = f_dev3;


        }
        evaluator_destroy(f);
        evaluator_destroy(f_dev);
    }
}

// vou ter que modificar essa funcao acho que aqui eh a rosenbrock em si
// Funcao para calcular a Funcao do vetor X atual que recebe o vetor X e quantos sao os xi
double calcularValorFuncao(double* x, int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += x[i];
    }
    return soma;
}

// Função para realizar a fatoração LU com pivoteamento parcial
// Recbe uma matriz o tamanho da matriz e o elemento a ser pivoteado
void lu_factorization(double** A, int n, int* pivot) {
    for (int k = 0; k < n; k++) {
        // Encontrar o pivô máximo na coluna k
        int max_index = k;
        double max_value = A[k][k];
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > abs(max_value)) {
                max_value = A[i][k];
                max_index = i;
            }
        }

        // Trocar as linhas k e max_index
        if (max_index != k) {
            double* temp = A[k];
            A[k] = A[max_index];
            A[max_index] = temp;

            int temp_pivot = pivot[k];
            pivot[k] = pivot[max_index];
            pivot[max_index] = temp_pivot;
        }

        // Realizar eliminação gaussiana na coluna k
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            A[i][k] = factor;
        }
    }
}

// Função para resolver o sistema linear usando fatoração LU com pivoteamento parcial
// Recebe uma Matriz um vetor com os termos independentes e o tamanho da Matriz
double* solve_linear_system(double **A, double *b, int n) {
    // Criar uma cópia de A para preservar a matriz original
    double** A_copy = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        A_copy[i] = (double*)malloc(sizeof(double) * n);
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }

    // Criar vetor de permutação de pivôs
    int* pivot = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        pivot[i] = i;
    }

    // Realizar fatoração LU com pivoteamento parcial
    lu_factorization(A_copy, n, pivot);

    // Resolver o sistema linear Ly = Pb usando substituição para frente
    double* y = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        y[i] = b[pivot[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A_copy[i][j] * y[j];
        }
    }

    // Resolver o sistema linear Ux = y usando substituição para trás
    double* delta = (double*)malloc(sizeof(double) * n);
    for (int i = n - 1; i >= 0; i--) {
        delta[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            delta[i] -= A_copy[i][j] * delta[j];
        }
        delta[i] /= A_copy[i][i];
    }

    // Liberar memória alocada
    for (int i = 0; i < n; i++) {
        free(A_copy[i]);
    }
    free(A_copy);
    free(pivot);
    free(y);

    return delta;
}

// Função para calcular a transposta de uma matriz
void transposta(double** matriz, double** resultado, size_t lin, size_t col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            resultado[j][i] = matriz[i][j];
        }
    }
}

// Função para calcular Hk+1, recebe matriz hk , vetor x , o gradiente , n e k
// Realiza todo o Calculo para solucao do metodo Quasi-Newton
// O valor de hk+1 eh sobrescrito na matriz hk, for fim ela eh atualizada
void calculaHK(double** Hk, double* x, double** grad_f, int n, int k) {
    double **pk = (double**)malloc(sizeof(double*) * n);
    if(!pk){
        printf("Erro ao alocar vetor pk.\n");
        return;
    }
    double **qk = (double**)malloc(sizeof(double*) * n); 
    if(!qk){
        printf("Erro ao alocar vetor qk.\n");
        return;
    }
    double **pk_t = (double**)malloc(sizeof(double*) * n);
    if(!pk_t){
        printf("Erro ao alocar vetor pk_t.\n");
        return;
    }
    double **qk_t = (double**)malloc(sizeof(double*) * n);
    if(!qk_t){
        printf("Erro ao alocar vetor pk.\n");
        return;
    }
    double **Hk_qk = (double**)malloc(sizeof(double**) * n);
    if(!Hk_qk){
        printf("Erro ao alocar matriz Hk_pk.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        Hk_qk[i] = (double*)malloc(sizeof(double*) * n);
    }
    double **Hk1 = (double**)malloc(sizeof(double**) * n);
    if(!Hk1){
        printf("Erro ao alocar matriz Hk1.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        Hk1[i] = (double*)malloc(sizeof(double*) * n);
    }
    
    double **eq1 = (double**)malloc(sizeof(double**) * n);
    if(!eq1){
        printf("Erro ao alocar matriz eq1.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        eq1[i] = (double*)malloc(sizeof(double*) * n);
        }
    
    double **eq2 = (double**)malloc(sizeof(double**) * n);
    if(!eq2){
        printf("Erro ao alocar matriz eq2.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        eq2[i] = (double*)malloc(sizeof(double*) * n);
    }
    
    // Calcula p^k = x^[k+1] - x^[k] 
    printf("x=1 - x");
            printf("\n");
    for (int i = 0; i < n; i++) {
        pk[i][1] = pow(x[i],k+1) - pow(x[i],k);
        printf("%f",pk[i][1]);
                printf("\n");
    }
    
    // Calcula pk_t = pk transposto 
    transposta(pk, pk_t, n, 1);
    
        printf("gradiete fk+1 - fk");
            printf("\n");
    //Calcula qk = grad_fk1 - grad_f 
    for (int i = 0; i < n; i++) {
        qk[i][1] = pow(grad_f[i][0],k+1) - pow(grad_f[i][0],k);
                printf("%f",qk[i][1]);
                printf("\n");
    }
    
    // Calcula qk_t = qk transposto
    transposta(qk, qk_t, n, 1);
    

    // Calcula Hk_qk = Hk * qk, ok
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <n; j++) {
            Hk_qk[i][j] = 0;
            for (int k = 0; k < n; k++) {
                Hk_qk[i][j] += Hk[i][j] * qk[k][1];
            }
        }
    }
    
    // Calcula Hk1 = Hk + (pk * pk_t) / (pk_t * qk) - (Hk_qk * qk_t * Hk) / (qk_t * Hk_qk * qk)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            eq1[i][j] = pk[i][1] * pk_t[1][j] / (pk_t[1][j] * qk[i][1]);
            eq2[i][j] = Hk_qk[i][j] * qk_t[1][j] * Hk[i][j] / (qk_t[1][j] * Hk_qk[i][j] * qk[i][1]);
            Hk1[i][j] = Hk[i][j] + eq1[i][j] - eq2[i][j];
        }
    }
    
    // Atualiza a matriz Hk com Hk1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Hk[i][j] = Hk1[i][j];
        }
    }

    free(pk);
    free(qk);
    free(pk_t);
    free(qk_t);
    free(Hk_qk);
    free(Hk1);
    free(eq1);
    free(eq2);
}