#include "integracao.h"
#include <math.h>
#include <stdlib.h>


// usa a regra dos trapézios para calcular a área abaixo de f(x) em um intervalo [a, b]
double trapezios(fx f, double a, double b, int n)
{
    // calcula o tamanho das n subdivisões do intervalo [a, b]
    double tam_intervalo = b - a;
    double h = tam_intervalo / n;

    double area = 0.0;

    // soma das áreas de cada trapézio
    for (int i = 0; i < n; i++)
    {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        double fx0 = f(x0);
        double fx1 = f(x1);
        area += ((fx0 + fx1) / 2.0) * h;
    }

    return area;
}


double simpson(fx f, double a, double b, int n)
{
    // deixa n par
    n += n% 2;

    // calcula o tamanho das n subdivisões do intervalo [a, b]
    double h = (b - a) / n;

    // area += f(x0) + f(xn)
    double area = f(a) + f(b);

    // soma das áreas de cada simpson
    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        if (i % 2 == 0)
        {
            area += 2 * f(x);
        }
        else
        {
            area += 4 * f(x);
        }
    }

    return h/3 * area;
    
}
