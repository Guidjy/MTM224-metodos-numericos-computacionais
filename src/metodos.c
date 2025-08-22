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


double newton_raphson(fx f, fx df, double x)
{
    // calcula o quanto x tem que ser deslocado para chegar a raíz para x0
    double delta_x = f(x) / df(x);
    // enquanto a distância até a raíz for maior que e
    while (delta_x > EPSILON)
    {
        // calcula o quanto x tem que ser deslocado para chegar a raíz para xi
        delta_x = f(x) / df(x);
        // xi+1 = xi - f(x) / f'(x)  
        x = x - delta_x;
    }
    return x;
}


double secantes(fx f, double x0, double x1)
{
    double x2;

    while (fabs(f(x1)) > EPSILON)
    {
        // calcula o denominador da formula da secante para prevenir divisão por 0
        double denominador = f(x1) - f(x0);
        if (fabs(denominador) < EPSILON)
        {
            printf("Divisão por zero no método da secante\n");
            return NAN;
        }
        // x2 = x1 - f(x1)*(x1-x0) / (f(x1)-f(x0))
        x2 = x1 - f(x1)*(x1-x0) / denominador;
        // atualiza x para próxima iterações
        x0 = x1;
        x1 = x2;
    }

    return x1;
}