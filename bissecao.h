#ifndef bissecao_H
#define bissecao_H
#include <stdio.h>
#include <gsl/gsl_deriv.h>
int bissecao() {
    char expressao[100];
    double a, b, c_velho, c_novo = 0, erro_req;

    printf("Digite a funcao (ex: x^2-2): ");
    scanf("%s", expressao);
    printf("Ponto a: ");
    scanf("%lf", &a);
    printf("Ponto b: "); // Corrigido o texto aqui
    scanf("%lf", &b);
    printf("Erro maximo (%%): ");
    scanf("%lf", &erro_req);

    // Validação inicial: Teorema de Bolzano
    if (funcao(a, expressao) * funcao(b, expressao) >= 0) {
        printf("Erro: A raiz pode nao estar nesse intervalo (f(a) e f(b) tem sinais iguais).\n");
        return 1;
    }

    double porcentagem = 100;
    int iteracao = 1;

    printf("\n--- INICIANDO BISSECAO ---\n");
    while (porcentagem > erro_req) {
        c_velho = c_novo;       // Guarda o valor da iteração anterior
        c_novo = (a + b) / 2.0; // Calcula o novo ponto médio
        
        double v_fa = funcao(a, expressao);
        double v_fb = funcao(b,expressao);
        double v_fc = funcao(c_novo, expressao);

        printf("Iteracao %d: a=%g, b=%g, c=%g, f(c)=%g\n", iteracao++, a, b, c_novo, v_fc);

        if (v_fc == 0.0) {
            break; // Achou a raiz exata
        } 
        else if (v_fa * v_fc < 0) {
            b = c_novo; // A raiz está à esquerda
        } 
        else {
            a = c_novo; // A raiz está à direita
        }

        // Cálculo do erro relativo (evitando divisão por zero)
        if (c_novo != 0) {
            porcentagem = fabs((c_novo - c_velho) / c_novo) * 100;
        }
    }

    printf("\nRaiz final encontrada: %g\n", c_novo);
    return 0;
}
#endif