/*
    Autores: Diego Vieira de Christo e Bruno Villa Lobus Strapasson
    GRR: 20206154 e 20215522
*/
#ifndef FUN_H
#define FUN_H

void calcularPolinomio(int n, int k, char* resultado);

void calcularGradiente(int n, char* resultado, void** gradiente);

void calcularHessiana(int n, char* resultado, void*** hessiana); 

double *solve_linear_system(double **A, double *b,  int n);

double calcularValorFuncao(double* x, int n);

void transposta(double** matriz, double** resultado, size_t lin, size_t col);

void calculaHK(double** Hk, double* x, double** grad_f, int n, int k);



#endif