#ifndef ZEROS_H
#define ZEROS_H


// define um tipo de ponteiro para função que aceita um double como argumento e retorna um double
typedef double (*fx)(double);

// Todas as funções retornam um x tal que f(x) ≈ 0.

// Encontra uma raiz de f(x) no intervalo [a, b], assumindo que f(a) e f(b) têm sinais opostos.
// - f: função cujo zero se deseja encontrar
// - a: limite inferior do intervalo inicial
// - b: limite superior do intervalo inicial
double biscecao(fx f, double a, double b);

// Variante do método da bisseção que usa interpolação linear entre os pontos (a, f(a)) e (b, f(b))
// para encontrar a nova aproximação da raiz.
// - f: função cujo zero se deseja encontrar
// - a: limite inferior do intervalo inicial
// - b: limite superior do intervalo inicial
double falsa_posicao(fx f, double a, double b);

// Utiliza derivada para encontrar sucessivas aproximações da raiz de f(x) a partir de uma estimativa inicial.
// - f: função cujo zero se deseja encontrar
// - df: derivada da função f
// - x: valor inicial (chute inicial)
double newton_raphson(fx f, fx df, double x);

// Similar ao método de Newton-Raphson, mas utiliza derivadas numéricas. Usa duas aproximações iniciais e uma
// interpolação linear para calcular as próximas.
// - f: função cujo zero se deseja encontrar
// - x0: primeira estimativa inicial
// - x1: segunda estimativa inicial
double secantes(fx f, double x0, double x1);


#endif  // ZEROS_H