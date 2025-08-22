#ifndef METODOS_H
#define METODOS_H


// define um tpo de ponteiro para função que aceita um double como argumento e retorna um double
typedef double (*fx)(double);


// métodos de encontrar zeros de função

double biscecao(fx f, double a, double b);

void teste();


#endif  // METODOS_H