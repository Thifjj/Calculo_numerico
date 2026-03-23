#ifndef newton_H
#define newton_H
#include <ctype.h>
#include <math.h>
#include <gsl/gsl_deriv.h>
#include "parser.h"

int newton_raphson() {
    char expressao[100];
    double x, erro_req;

    printf("Digite a funcao (ex: x^3-6*x^2+11*x-6.1): ");
    scanf("%s", expressao);
    printf("Ponto inicial x0: ");
    scanf("%lf", &x);
    printf("Erro maximo (%%): ");
    scanf("%lf", &erro_req);

    gsl_function F;
    F.function = &funcao;
    F.params = expressao; // Passamos a string para o parser

    double porcentagem = 100;
    while (porcentagem > erro_req) {
        double v_f = f(x, expressao);
        double der, erro_est;
        
        gsl_deriv_central(&F, x, 1e-7, &der, &erro_est);

        double x_novo = x - (v_f / der);
        porcentagem = fabs(((x_novo - x) / x_novo) * 100);
        
        printf("x = %-10g | f(x) = %-10g | Erro = %g%%\n", x, v_f, porcentagem);
        x = x_novo;
    }

    printf("\nRaiz final: %g\n", x);
    return 0;
}
#endif