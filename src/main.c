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

    // resultados
    printf("- Biscecao: \t");
    resultado = biscecao(f, 0, 4);
    printf("%llf\n", resultado);
    printf("- Falsa posicao: \t");
    resultado = falsa_posicao(f, 0, 4);
    printf("%llf\n", resultado);
    printf("- Newton Raphson: \t");
    resultado = newton_raphson(f, df, 2);
    printf("%llf\n", resultado);
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

    // inicializa uma matriz
    matriz *m = matriz_cria(3, 4, valores);
    printf(">sistema linear: \n");
    matriz_imprime(m, true);
    printf("\n\n");

    eliminacao_gaussiana(m);

    matriz_destroi(m);

    return 0;
}
