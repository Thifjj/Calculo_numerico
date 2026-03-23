#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <gsl/gsl_deriv.h>

// --- O MOTOR DO PARSER MANUAL ---

// Função para verificar a precedência dos operadores
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Executa uma operação matemática simples
double aplicar_op(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// Avalia a expressão para um valor de X dado
double avaliar_manual(const char *exp, double x_valor) {
    double valores[100];
    char ops[100];
    int v_topo = -1, o_topo = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isspace(exp[i])) continue;

        // Se for o valor de X
        if (exp[i] == 'x') {
            valores[++v_topo] = x_valor;
        } 
        // Se for um número
        else if (isdigit(exp[i])) {
            double val = 0;
            char buffer[20];
            int b = 0;
            while (isdigit(exp[i]) || exp[i] == '.') buffer[b++] = exp[i++];
            buffer[b] = '\0';
            i--;
            valores[++v_topo] = atof(buffer);
        }
        // Se for parênteses
        else if (exp[i] == '(') {
            ops[++o_topo] = '(';
        }
        else if (exp[i] == ')') {
            while (o_topo != -1 && ops[o_topo] != '(') {
                double val2 = valores[v_topo--];
                double val1 = valores[v_topo--];
                char op = ops[o_topo--];
                valores[++v_topo] = aplicar_op(val1, val2, op);
            }
            o_topo--; // remove '('
        }
        // Se for operador
        else {
            while (o_topo != -1 && precedencia(ops[o_topo]) >= precedencia(exp[i])) {
                double val2 = valores[v_topo--];
                double val1 = valores[v_topo--];
                char op = ops[o_topo--];
                valores[++v_topo] = aplicar_op(val1, val2, op);
            }
            ops[++o_topo] = exp[i];
        }
    }

    while (o_topo != -1) {
        double val2 = valores[v_topo--];
        double val1 = valores[v_topo--];
        char op = ops[o_topo--];
        valores[++v_topo] = aplicar_op(val1, val2, op);
    }

    return valores[0];
}

// --- INTEGRAÇÃO COM SEU CÓDIGO E GSL ---

double f(double x, void *params) {
    char *expressao = (char *)params;
    return avaliar_manual(expressao, x);
}

int main() {
    char expressao[100];
    double x, erro_req;

    printf("Digite a funcao (ex: x^3-6*x^2+11*x-6.1): ");
    scanf("%s", expressao);
    printf("Ponto inicial x0: ");
    scanf("%lf", &x);
    printf("Erro maximo (%%): ");
    scanf("%lf", &erro_req);

    gsl_function F;
    F.function = &f;
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