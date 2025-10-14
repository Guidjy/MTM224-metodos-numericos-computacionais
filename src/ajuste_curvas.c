#include "ajuste_curvas.h"
#include "sistemas_lineares.h"
#include <math.h>



double minimos_quadrados(double *x, double *y, int grau, int n_pontos)
{
    // forma matricial
    int n = grau + 1;
    double **A = matriz_cria(n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i][j] = 0;

    for (int i = 0; i < n; i++)
    {
        // grau do somatório nesse ponto da matriz
        int g = grau * 2 - i;
        for (int j = 0; j < n; j++)
        {
            // Σxi^g
            g -= j;
            for (int k = 0; k < n_pontos; k++)
            {
                A[i][j] += pow(x[k], g);
            }
        }
        
    }

    matriz_imprime(A, n, n);
}