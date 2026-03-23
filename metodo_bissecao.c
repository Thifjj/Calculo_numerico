#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// --- MOTOR DO PARSER MANUAL (Mesma lógica sua) ---

int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double aplicar_op(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
        case '^': return pow(a, b);
    }
    return 0;
}

double avaliar_manual(const char *exp, double x_valor) {
    double valores[100];
    char ops[100];
    int v_topo = -1, o_topo = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        if (isspace(exp[i])) continue;

        if (exp[i] == 'x') {
            valores[++v_topo] = x_valor;
        } 
        else if (isdigit(exp[i])) {
            char buffer[20];
            int b = 0;
            while (isdigit(exp[i]) || exp[i] == '.') buffer[b++] = exp[i++];
            buffer[b] = '\0';
            i--;
            valores[++v_topo] = atof(buffer);
        }
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
            o_topo--; 
        }
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

// --- FUNÇÃO DE AJUDA ---

double f(double x, char *expressao) {
    return avaliar_manual(expressao, x);
}

int main() {
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
    if (f(a, expressao) * f(b, expressao) >= 0) {
        printf("Erro: A raiz pode nao estar nesse intervalo (f(a) e f(b) tem sinais iguais).\n");
        return 1;
    }

    double porcentagem = 100;
    int iteracao = 1;

    printf("\n--- INICIANDO BISSECAO ---\n");

    while (porcentagem > erro_req) {
        c_velho = c_novo;       // Guarda o valor da iteração anterior
        c_novo = (a + b) / 2.0; // Calcula o novo ponto médio
        
        double v_fa = f(a, expressao);
        double v_fc = f(c_novo, expressao);

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