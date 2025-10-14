#include "ajuste_curvas.h"
#include "sistemas_lineares.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>



double *minimos_quadrados(double *x, double *y, int grau, int n_pontos)
{
    // matriz do sistema (matriz de somatórios de pontos xi)
    int n = grau + 1;
    double **A = matriz_cria(n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i][j] = 0;

    // obtem a matriz do sistema
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // grau de x no somatório Σxi^g nesse ponto da matriz
            int g = (grau * 2) - i - j;
            for (int k = 0; k < n_pontos; k++)
            {
                A[i][j] += pow(x[k], g);
            }
        }
        
    }

    // vetor do sistema
    double *b = malloc(n * sizeof(double));
    assert(b != NULL);
    for (int i = 0; i < n; i++)
    {
        // inicializa o ínidice i do vetor
        b[i] = 0;
        // grau de x nesse ponto do vetor
        int g = grau - i;
        for (int k = 0; k < n_pontos; k++)
        {
            b[i] += y[k] * pow(x[k], g);
        }
    }

    // resolve o sistema
    double *resposta = eliminacao_gaussiana(A, b, n);

    return resposta;

}