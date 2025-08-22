#ifndef METODOS_H
#define METODOS_H


// define um tpo de ponteiro para função que aceita um double como argumento e retorna um double
typedef double (*fx)(double);


// métodos de encontrar zeros de função

double biscecao(fx f, double a, double b);

double falsa_posicao(fx f, double a, double b);

double newton_raphson(fx f, fx df, double x);

double secantes(fx f, double x0, double x1);


#endif  // METODOS_H