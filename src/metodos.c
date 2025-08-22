#include "metodos.h"
#include <math.h>
#include <stdio.h>


#define EPSILON 0.00001


double biscecao(fx f, double a, double b) 
{
    // verifica se o intervalo é válido
    if (f(a)*f(b) >= 0) 
    {
        printf("Intervalo inválido para o método.\n");
        return NAN;
    }

    // calcula o ponto médio
    double pm = (a + b) / 2;

    // enquanto |b-a| > e ou f(pm) > 0
    while (fabs(b-a) >= EPSILON || fabs(f(pm)) > 0)
    {
        // calcula o ponto médio
        pm = (a + b) / 2;
        // verifica se o ponto médio é a raíz
        if (fabs(f(pm)) < EPSILON) return pm;
        // verifica em que lado da biscecão vai continuar o método
        if (f(a)*f(pm) < 0)
        {
            b = pm;
        }
        else
        {
            a = pm;
        }
    }

    return pm;
}


double falsa_posicao(fx f, double a, double b)
{
    // verifica se o intervalo é válido
    if (f(a)*f(b) >= 0) 
    {
        printf("Intervalo inválido para o método.\n");
        return NAN;
    }
    double c;

    // enquanto |b-a| > e ou f(pm) > 0
    while (fabs(b-a) >= EPSILON)
    {
        // acha o ponto entre [a, f(a)], [b, f(b)] que intercepta o eixo x
        c = (a*f(b) - b*f(a)) / (f(b) - f(a));
        // verifica se esse ponto é a raíz
        if (f(c) > EPSILON) return c;
        // escolhe em que lado continuar o método
        if (f(a)*f(c) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }

    return c;
}