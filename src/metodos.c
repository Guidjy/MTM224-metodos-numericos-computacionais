#include "metodos.h"
#include <math.h>
#include <stdio.h>


#define EPSILON 0.00001


double biscecao(fx f, double a, double b) 
{
    if (f(a)*f(b) >= 0) 
    {
        printf("Bisection method fails: f(a) and f(b) must have opposite signs.\n");
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
