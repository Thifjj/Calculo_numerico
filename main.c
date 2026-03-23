#include <stdio.h>
#include <stdlib.h>

// Incluindo as tuas bibliotecas que você já montou
#include "parser.h"
#include "bissecao.h"
#include "newton.h"

int main() {
    int escolha;

    while (1) {
        printf("\n========================================\n");
        printf("   CALCULADORA NUMERICA (FPGA READY)    \n");
        printf("========================================\n");
        printf("1 - Metodo da Bissecao\n");
        printf("2 - Metodo Newton-Raphson\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &escolha) != 1) break;

        switch (escolha) {
            case 1:
                // Chama a funcao que esta dentro do seu bissecao.h
                bissecao();
                break;
            case 2:
                // Chama a funcao que esta dentro do seu newton.h
                newton_raphson();
                break;
            case 3:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida, tente de novo.\n");
        }
    }

    return 0;
}