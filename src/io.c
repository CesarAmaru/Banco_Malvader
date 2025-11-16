#include "io.h"
#include <stdio.h>
#include <string.h>

void ler_linha(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

double ler_double(void) {double valor; scanf("%lf", &valor); limpar_buffer(); return valor;}

int ler_int(void) {int valor; scanf("%d", &valor); limpar_buffer(); return valor;}

void limpar_buffer(void) {int l; while ((l = getchar()) != '\n' && l != EOF);}

void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor) {
    if (!conta || tam_conta == 0 || !valor) return;
    printf("Conta: ");
    ler_linha(conta, tam_conta);

    printf("Valor: ");
    if (scanf("%lf", valor) != 1) {
        // leitura inválida -> zera e limpa buffer
        *valor = 0.0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    // consumir o '\n' que ficou no buffer do stdin
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}