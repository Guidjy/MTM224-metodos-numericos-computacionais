#include "sistemas_lineares.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


matriz *matriz_cria(int n_lin, int n_col, double valores[n_lin][n_col])
{
    // aloca memória para a estrutura de uma matriz
    matriz *mat = (matriz*) malloc(sizeof(matriz));
    assert(mat != NULL);

    // inicializa os valores da estrutura
    mat->n_lin = n_lin;
    mat->n_col = n_col;

    // aloca memória para as linhas da matriz
    mat->elem = (double**) malloc(mat->n_lin * sizeof(double*));
    assert(mat->elem != NULL);
    for (int i = 0; i < mat->n_lin; i++)
    {
        // aloca memória para as colunas da linha i
        mat->elem[i] = (double*) malloc(mat->n_col * sizeof(double));
        assert(mat->elem[i] != NULL);
        // inicializa as colunas da linha i
        memcpy(mat->elem[i], valores[i], n_col * sizeof(double));
    }

    return mat;
}


matriz *matriz_copia(matriz *orig) 
{
    matriz *copia = malloc(sizeof(matriz));
    copia->n_lin = orig->n_lin;
    copia->n_col = orig->n_col;

    copia->elem = malloc(copia->n_lin * sizeof(double*));
    for (int i = 0; i < copia->n_lin; i++) 
    {
        copia->elem[i] = malloc(copia->n_col * sizeof(double));
        memcpy(copia->elem[i], orig->elem[i], copia->n_col * sizeof(double));
    }

    return copia;
}


void matriz_destroi(matriz *self)
{
    if (self == NULL) return;

    // libera a matriz
    for (int i = 0; i < self->n_lin; i++)
    {
        free(self->elem[i]);
    }
    free(self->elem);

    // libera a estrutura da matriz
    free(self);
}


void matriz_imprime(matriz *self, bool eh_aumentada)
{
    if (self == NULL) return;

    for (int i = 0; i < self->n_lin; i++)
    {
        printf("|");
        for (int j = 0; j < self->n_col; j++)
        {
            if (eh_aumentada && j == self->n_col - 1) printf("|");
            printf("%4.1lf ", self->elem[i][j]);
        }
        printf("|\n");
    }
}


double *eliminacao_gaussiana(matriz *mat)
{
    // copia a matriz original para não altera-la
    matriz *m = matriz_copia(mat);

    for (int i = 0; i < m->n_lin; i++)
    {
        // Get a 1 in the first column, first row
        // Use the 1 to get 0’s in the remainder of the first column

        // multiplica a linha i por um escalar "c" tal que o pivô da linha se torne 1
        double pivo = m->elem[i][0+i];
        double c = 1 / pivo;
        for (int j = 0; j < m->n_col; j++)
        {
            m->elem[i][j] *= c;
        }

        // soma um múltiplo da linha i as linhas de baixo de forma a zerar os elementos abaixo do pivô
        for (int lin = i+1; lin < m->n_lin; lin++)
        {
            c = m->elem[lin][0+i] / pivo;
        }
    }
    
    matriz_imprime(m, true);
    matriz_destroi(m);
}