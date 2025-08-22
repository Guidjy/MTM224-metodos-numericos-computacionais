#include "metodos.h"
#include <stdio.h>
#include <math.h>


// x² - 2
double f(double x) {
    return pow(x, 2) -2;
}


int main(){
    double resultado = biscecao(f, 0, 4);
    printf("%llf\n", resultado);

    return 0;
}
