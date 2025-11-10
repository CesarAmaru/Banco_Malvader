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