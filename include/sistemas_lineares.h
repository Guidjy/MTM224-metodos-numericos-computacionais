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

matriz *matriz_copia(matriz *orig);

void matriz_destroi(matriz *self);

void matriz_imprime(matriz *self, bool eh_aumentada);

// métodos numéricos

// encontra a solução de um sistema linear por meio da escalonação de uma matriz aumentada.
// - argumentos:
// > mat: matriz aumentada
// - retorno: vetor de soluções [x0, x1, ..., xn]
double *eliminacao_gaussiana(matriz *mat);


#endif  // SISTEMAS_LINEARES_H