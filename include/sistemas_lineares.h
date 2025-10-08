#ifndef SISTEMAS_LINEARES_H
#define SISTEMAS_LINEARES_H


// funções de matriz e vetor

// aloca memória para uma matriz
double **matriz_cria(int n_lin, int n_col);

// libera toda a memória alocada para uma matriz
void matriz_destroi(double **mat, int n_lin);

// multiplica duas matrizes quadradas nxn
double **matriz_multiplica(double **m1, double **m2, int n);

// multiplica uma matriz nxn por um vetor de tamanho n e retora o vetor resultante
double *matriz_multiplica_vetor(double **mat, double *vet, int n);

// imprime uma matriz
void matriz_imprime(double **mat, int n_lin, int n_col);

// imprime um vetor
void vetor_imprime(double *vet, int n);

// imprime um sistema linear
void sistema_imprime(double **mat, double *vet, int n_lin, int n_col);

// resolve um sistema linear a partir de uma matriz aumentada escalonada
double *resolve_sistema(double **mat_aumentada, int n);

// métodos numéricos

// escalona uma matriz aumentada nxn+1 usando eliminação gaussiana e resolve seu sistema linear
double *eliminacao_gaussiana(double **mat, double *vet, int n);

// fatora uma matriz quadrada em uma triangular superior e uma triangular inferior e as retorna
double ***fatoracao_lu(double **mat, int n);

// resolve um sistema linear Ax = b de forma iterativa por transforma-lo na forma x(k+1) = Cx(k) + g
double *gauss_jacobi(double **mat, double *vet, double *chute, int n);




#endif  // SISTEMAS_LINEARES_H