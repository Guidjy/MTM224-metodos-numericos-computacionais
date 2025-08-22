#include "metodos.h"
#include <stdio.h>
#include <math.h>


// x² - 2
double f(double x) {
    return pow(x, 2) -2;
}


// 2x
double df(double x) {
    return 2*x;
}


int main(){
    double resultado = secantes(f, 0, 1);
    printf("%llf\n", resultado);

    return 0;
}
