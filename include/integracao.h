#ifndef INTEGRACAO_H
#define INTEGRACAO_H


// define um tipo de ponteiro para função que aceita um double como argumento e retorna um double
typedef double (*fx)(double);


// usa a regra dos trapézios para calcular a área abaixo de f(x) em um intervalo [a, b]
double trapezios(fx f, double a, double b, int n);

// usa a regra de 1/3 de simpson para calcular a área abaixo de f(x) em um intervalo [a, b]
double simpson(fx f, double a, double b, int n);


#endif  // INTEGRACAO_H