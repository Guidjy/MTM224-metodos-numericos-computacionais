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
    double valores[3][4] = { {3, 2, 4, 1},
                             {1, 1, 2, 2},
                             {4, 3, -2, 3} };
    double b[] = {1, 2, 3};
    matriz *a = matriz_cria(3, 4, valores);
    printf("sistema linear: \n");
    matriz_imprime(a, true);

    // eliminação gaussiana
    printf("- eliminacao gaussiana: \n");
    matriz *m1 = matriz_copia(a, 3, 4);
    double *solucao = eliminacao_gaussiana(m1);
    vetor_imprime(solucao, m1->n_lin);
    free(solucao);
    // fatoração LU
    printf("- decomposicao LU: \n");
    matriz *m2 = matriz_copia(a, 3, 3);
    matriz **lu = decomposicao_lu(m2, b);
    matriz_imprime(lu[0], false);
    matriz_imprime(lu[1], false);

    return 0;
}
