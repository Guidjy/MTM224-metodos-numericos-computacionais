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
        if (valores != NULL)
        {
            memcpy(mat->elem[i], valores[i], n_col * sizeof(double));
        }
        else
        {
            for (int j = 0; j < n_col; j++) mat->elem[i][j] = 0;
        }
    }

    return mat;
}


matriz *matriz_copia(matriz *orig, int n_lin, int n_col) 
{
    matriz *copia = malloc(sizeof(matriz));
    copia->n_lin = n_lin;
    copia->n_col = n_col;

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


matriz *matriz_multiplica(matriz *m1, matriz *m2)
{
    if (m1->n_col != m2->n_lin) return NULL;

    matriz *resultado = matriz_cria(m1->n_lin, m2->n_col, NULL);
    int dim = m1->n_col;  // dimensão interna para soma (m1->n_col == m2->n_lin)

    for (int i = 0; i < resultado->n_lin; i++)
    {
        for (int j = 0; j < resultado->n_col; j++)
        {
            double soma = 0.0;
            for (int k = 0; k < dim; k++)
            {
                soma += m1->elem[i][k] * m2->elem[k][j];
            }
            resultado->elem[i][j] = soma;
        }
    }

    return resultado;
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
    printf("\n");
}


void vetor_imprime(double *self, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%6.2lf, ", self[i]);
    }
    printf("]\n");
}


double *eliminacao_gaussiana(matriz *mat)
{
    // escalona a matriz
    for (int i = 0; i < mat->n_lin; i++)
    {
        // multiplica a linha i por um escalar "c" tal que o pivô da linha se torne 1
        double pivo = mat->elem[i][i];
        for (int j = 0; j < mat->n_col; j++)
        {
            mat->elem[i][j] /= pivo;
        }
        
        for (int lin = i+1; lin < mat->n_lin; lin++)
        {
            double c = -1*mat->elem[lin][i];
            for (int j = i; j < mat->n_col; j++)
            {
                mat->elem[lin][j] += c * mat->elem[i][j];
            }
        }
    }
    
    // obtem o vetor solução
    double *solucao = (double*) malloc(mat->n_lin * sizeof(double));
    for (int i = mat->n_lin - 1; i >= 0; i--)
    {
        solucao[i] = mat->elem[i][mat->n_col - 1];
        for (int j = i + 1; j < mat->n_lin; j++)
        {
            solucao[i] -= mat->elem[i][j] * solucao[j];
        }
    }

    return solucao;
}


matriz **decomposicao_lu(matriz *mat, double b[mat->n_lin])
{
    // cria as matrizes l e u
    matriz *l = matriz_cria(mat->n_lin, mat->n_col, NULL);
    // Inicializa a diagonal de L com 1.0
    for (int i = 0; i < l->n_lin; i++) l->elem[i][i] = 1.0;
    matriz *u = matriz_copia(mat, mat->n_lin, mat->n_col);

    // fatoração
    for (int i = 0; i < u->n_lin; i++)
    {
        double pivo = u->elem[i][i];
        // zera os elementos abaixo do pivô
        for (int lin = i + 1; lin < u->n_lin; lin++)
        {
            // multiplicador "c" = elemento a ser zerado / pivo
            double c = u->elem[lin][i] / pivo;
            // armazena o multiplicador na matriz l
            l->elem[lin][i] = c;
            for (int j = i; j < u->n_col; j++)
            {
                u->elem[lin][j] -= c * u->elem[i][j];
            }
        }
    }

    matriz **lu = (matriz**) malloc(2 * sizeof(matriz*));
    lu[0] = l;
    lu[1] = u;

    return lu;
}