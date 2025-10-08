#include "zeros.h"
#include "sistemas_lineares.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


// x² - 2
double f(double x) {
    return pow(x, 2) -2;
}
// 2x
double df(double x) {
    return 2*x;
}


int main(){
    double resultado;

    // métodos para encontrar zeros de função
    printf("//========================================\n");
    printf("// Zeros de funcao\n");
    printf("//========================================\n");
    // sistema linear x² - 2
    printf(">funcao: x^2 - 2\n");

    // bisceção
    printf("- Biscecao: \t");
    resultado = biscecao(f, 0, 4);
    printf("%llf\n", resultado);
    // falsa posição
    printf("- Falsa posicao: \t");
    resultado = falsa_posicao(f, 0, 4);
    printf("%llf\n", resultado);
    // newton raphson
    printf("- Newton Raphson: \t");
    resultado = newton_raphson(f, df, 2);
    printf("%llf\n", resultado);
    // secantes
    printf("- Secantes: \t");
    resultado = secantes(f, 1, 2);
    printf("%llf\n\n\n", resultado);
    

    // métodos para resolver sistemas lineares
    printf("//========================================\n");
    printf("// Solucao de sistemas lineares\n");
    printf("//========================================\n");
    // sistema linear
    double sistema[3][4] = { {10, 1, 1, 12},
                             {1, 10, 1, 12},
                             {1, 1, 10, 12} };
    // matriz de equações
    int n_lin = 3;
    int n_col = 3;
    double **A = matriz_cria(n_lin, n_col);
    for (int i = 0; i < n_lin; i++)
        for (int j = 0; j < n_col; j++) A[i][j] = sistema[i][j];
    // vetor de soluções
    double *b = (double*) malloc(n_lin * sizeof(double));
    for (int i = 0; i < n_lin; i++) b[i] = sistema[i][3];
    // imprime o sistema linear
    printf(">sistema linear: \n");
    sistema_imprime(A, b, n_lin, n_col);
    printf("\n");

    // eliminação gaussiana
    printf("- eliminacao gaussiana: \n");
    double *solucao = eliminacao_gaussiana(A, b, n_lin);
    vetor_imprime(solucao, n_lin);
    printf("\n");
    free(solucao);
    // fatoração LU
    printf("- fatoracao LU: \n");
    double ***lu = fatoracao_lu(A, n_lin);
    matriz_imprime(lu[0], n_lin, n_lin);
    printf("\n");
    matriz_imprime(lu[1], n_lin, n_lin);
    printf("\n");
    //matriz_destroi(lu[0], n_lin);
    //matriz_destroi(lu[1], n_lin);
    free(lu);
    // gauss-jacobi
    printf("- Gauss-Jacobi: \n");
    double *chute = (double*) malloc(n_lin * sizeof(double));
    for (int i = 0; i < n_lin; i++) chute[i] = 0;
    solucao = gauss_jacobi(A, b, chute, n_lin);
    vetor_imprime(solucao, n_lin);

    return 0;
}
