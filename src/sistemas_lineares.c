#include "sistemas_lineares.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


#define EPSILON 0.001
#define MAX_ITERACOES 1000


double **matriz_cria(int n_lin, int n_col)
{
    double **m = (double**) malloc(n_lin * sizeof(double*));
    assert(m != NULL);

    for (int i = 0; i < n_lin; i++)
    {
        m[i] = (double*) malloc(n_col * sizeof(double));
        assert(m[i] != NULL);
        for (int j = 0; j < n_col; j++) m[i][j] = 0;
    }

    return m;
}


void matriz_destroi(double **mat, int n_lin)
{
    if (mat == NULL) return;

    for (int i = 0; i < n_lin; i++)
    {
        if (mat[i] != NULL) free(mat[i]);
    }

    free(mat);
}


double **matriz_multiplica(double **m1, double **m2, int n)
{
    // cria matriz resultado n x n
    double **res = matriz_cria(n, n);

    // multiplica as matrizes
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return res;
}


double *matriz_multiplica_vetor(double **mat, double *vet, int n)
{
    // cria vetor resultado
    double *res = (double*) calloc(n, sizeof(double));

    // multiplicação linha × vetor
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i] += mat[i][j] * vet[j];
        }
    }

    return res;
}


void vetor_imprime(double *vet, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%6.2lf, ", vet[i]);
    }
    printf("]\n");
}


void matriz_imprime(double **mat, int n_lin, int n_col)
{
    for (int i = 0; i < n_lin; i++)
    {
        printf("|");
        for (int j = 0; j < n_col; j++)
        {
            printf("%6.2lf ", mat[i][j]);
        }
        printf("|\n");
    }
}


void sistema_imprime(double **mat, double *vet, int n_lin, int n_col)
{
    for (int i = 0; i < n_lin; i++)
    {
        printf("|");
        for (int j = 0; j < n_col; j++)
        {
            printf("%6.2lf ", mat[i][j]);
        }
        printf("|%6.2lf |\n", vet[i]);
    }
}


double *resolve_sistema(double **mat_aumentada, int n)
{
    double *solucao = (double*) malloc(n * sizeof(double));
    // começa resolvendo de baixo para cima
    for (int i = n - 1; i >= 0; i--)
    {
        // xi = b[i]
        solucao[i] = mat_aumentada[i][n];
        for (int j = i + 1; j < n; j++)
        {
            // Aii * xi = b[i] - Aii+1 * xi+1 + Aii+2 * xi+2 + ...
            solucao[i] -= mat_aumentada[i][j] * solucao[j];
        }
        solucao[i] /= mat_aumentada[i][i];
    }
    return solucao;
}


// na real é eliminação gaussiana estável
double *resolve_sistema_mat_vet(double **A, double *b, int n)
{
    int i, j, k, max;
    double temp;

    // Aloca memória para o vetor solução
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL)
    {
        fprintf(stderr, "Erro: falha ao alocar memória para o vetor solução.\n");
        exit(EXIT_FAILURE);
    }

    // Eliminação Gaussiana com pivoteamento parcial
    for (i = 0; i < n - 1; i++)
    {
        // Encontra o pivô máximo na coluna i
        max = i;
        for (k = i + 1; k < n; k++)
        {
            if (fabs(A[k][i]) > fabs(A[max][i]))
                max = k;
        }

        // Troca as linhas se necessário
        if (max != i)
        {
            double *temp_row = A[i];
            A[i] = A[max];
            A[max] = temp_row;

            temp = b[i];
            b[i] = b[max];
            b[max] = temp;
        }

        // Eliminação
        for (k = i + 1; k < n; k++)
        {
            if (A[i][i] == 0)
            {
                fprintf(stderr, "Erro: pivô nulo detectado.\n");
                free(x);
                return NULL;
            }

            double m = A[k][i] / A[i][i];
            for (j = i; j < n; j++)
                A[k][j] -= m * A[i][j];
            b[k] -= m * b[i];
        }
    }

    // Substituição regressiva
    for (i = n - 1; i >= 0; i--)
    {
        double soma = 0.0;
        for (j = i + 1; j < n; j++)
            soma += A[i][j] * x[j];

        if (A[i][i] == 0)
        {
            fprintf(stderr, "Erro: sistema sem solução única.\n");
            free(x);
            return NULL;
        }

        x[i] = (b[i] - soma) / A[i][i];
    }

    return x;
}


// =================================
// Métodos numéricos
// =================================


double *eliminacao_gaussiana(double **mat, double *vet, int n)
{
    // cria a matriz aumentada
    double **mat_aumentada = matriz_cria(n, n+1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) mat_aumentada[i][j] = mat[i][j];
        mat_aumentada[i][n] = vet[i];
    }
    
    // escalona a matriz aumentada
    for (int i = 0; i < n; i++)
    {
        // divide a linha i pelo pivô
        double pivo = mat_aumentada[i][i];
        for (int j = 0; j < n + 1; j++) mat_aumentada[i][j] /= pivo;
        // zera os elementos abaixo do pivô pela operação entre linhas
        for (int k = i+1; k < n; k++)
        {
            double c = mat_aumentada[k][i];
            for (int j = 0; j < n+1; j++) mat_aumentada[k][j] -= mat_aumentada[i][j] * c;
        }
    }

    // resolve o sistema escalonado
    double *solucao = resolve_sistema(mat_aumentada, n);
    
    // libera a matriz aumentada
    matriz_destroi(mat_aumentada, n);

    return solucao;
}


double ***fatoracao_lu(double **mat, int n)
{
    // cria as matrizes L e U
    double **l = matriz_cria(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                l[i][j] = 1;
            }
            else
            {
                l[i][j] = 0;
            }
        }
    }
    double **u = matriz_cria(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) u[i][j] = mat[i][j];

    // escalona a matriz U
    for (int i = 0; i < n; i++)
    {
        // zera os elementos abaixo do pivô pela operação entre linhas
        double pivo = u[i][i];
        for (int k = i+1; k < n; k++)
        {
            double c = u[k][i] / pivo;
            l[k][i] = c;
            for (int j = 0; j < n; j++) u[k][j] -= u[i][j] * c;
        }
    }

    // retorna as matrizes L e U
    double ***lu = (double***) malloc(2 * sizeof(double**));
    lu[0] = l;
    lu[1] = u;
    return lu;
}


double *gauss_jacobi(double **mat, double *vet, double *chute, int n)
{
    // inicializa as variáveis do sistema x(k+1) = Cx(k) + g
    // matriz C
    double **C = matriz_cria(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                C[i][j] = 0;
            }
            else
            {
                C[i][j] = -1 * (mat[i][j] / mat[i][i]);
            }
        }
    }
    // vetor g
    double *g = (double*) malloc(n * sizeof(double));
    assert(g != NULL);
    for (int i = 0; i < n; i++) g[i] = vet[i] / mat[i][i];
    // vetores x(k_1) e x
    double *x_novo = malloc(n * sizeof(double));
    double *x = calloc(n, sizeof(double));
    memcpy(x, chute, n * sizeof(double));

    // método iterativo
    double erro = 1.0;
    int iteracoes = 0;
    while (erro > EPSILON && iteracoes < MAX_ITERACOES)
    {
        // Cx(k)
        double *Cx = matriz_multiplica_vetor(C, x, n);
        // x(k+1) = Cx(k) + g
        for (int i = 0; i < n; i++)
        {
            x_novo[i] = Cx[i] + g[i];
        }
        free(Cx);
        
        // norma euclidiana
        erro = 0;
        for (int i = 0; i < n; i++) erro += pow(x_novo[i] - x[i], 2);
        erro = sqrt(erro);

        iteracoes++;

        for (int i = 0; i < n; i++) x[i] = x_novo[i];
    }

    matriz_destroi(C, n);
    free(x_novo);
    free(g);

    return x;
}