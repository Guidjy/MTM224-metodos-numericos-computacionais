#include "interpolacao.h"
#include "sistemas_lineares.h"
#include <math.h>
#include <stdlib.h>


double *interpola_polinomio(double *x, double *y, int n_pontos)
{
    // monta a matriz do sistema linear da definição
    double **A = matriz_cria(n_pontos, n_pontos);
    for (int i = 0; i < n_pontos; i++)
    {
        for (int j = 0; j < n_pontos; j++)
        {
            int grau = n_pontos - j - 1;
            A[i][j] = pow(x[i], grau);
        }
    }

    double *coeficientes = resolve_sistema_mat_vet(A, y, n_pontos);

    return coeficientes;
}