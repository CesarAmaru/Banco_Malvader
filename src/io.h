
#ifndef BANCO_MALVADER_IO_H
#define BANCO_MALVADER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_linha(char *buffer, size_t tamanho);
double ler_double(void);
int ler_int(void);
void limpar_buffer(void);

//--------------------------
void ler_linha(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

double ler_double(void) {double valor; scanf("%lf", &valor); limpar_buffer(); return valor;}

int ler_int(void) {int valor; scanf("%d", &valor); limpar_buffer(); return valor;}

void limpar_buffer(void) {int l; while ((l = getchar()) != '\n' && l != EOF);}


#endif //BANCO_MALVADER_IO_H