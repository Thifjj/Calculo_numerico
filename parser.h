#ifndef parser_H
#define parser_H
#include <math.h>
#include <ctype.h>
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

double funcao(double x, char *expressao) {
    return avaliar_manual(expressao, x);
}
#endif