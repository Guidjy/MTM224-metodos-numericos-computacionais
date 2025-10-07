#ifndef SISTEMAS_LINEARES_H
#define SISTEMAS_LINEARES_H


#include <stdbool.h>


typedef struct
{
    int n_lin;      // número de linhas
    int n_col;      // número de colunas    
    double **elem;  // elementos da matriz
} matriz;


// funções de matriz

matriz *matriz_cria(int n_lin, int n_col, double valores[n_lin][n_col]);

matriz *matriz_copia(matriz *orig, int n_lin, int n_col);

void matriz_destroi(matriz *self);

matriz *matriz_multiplica(matriz *m1, matriz *m2);

void matriz_imprime(matriz *self, bool eh_aumentada);

void vetor_imprime(double *self, int n);

// métodos numéricos

// encontra a solução de um sistema linear por meio da escalonação de uma matriz aumentada.
// - argumentos:
// > mat: matriz aumentada
// - retorno: vetor de soluções [x0, x1, ..., xn]
double *eliminacao_gaussiana(matriz *mat);

// decompõe uma matriz quadrada em uma matriz triangular superior e uma inferior, tal que o produto
// das duas resulte na matriz original. A vantagem para solução de sistemas lineares, é que a
// decomposição só precisa ser feita uma vez, e o sistema Ax = b se torna (LU)x = b, que é
// muito rápido de se resolver.
// - argumentos:
// > mat: matriz quadrada
// > b: vetor de Ax = b
// - retorno: vetor de matriz [l, u]
matriz **decomposicao_lu(matriz *mat, double b[mat->n_lin]);


#endif  // SISTEMAS_LINEARES_H