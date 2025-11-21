#include "io.h"     // < Arquivo com os protótipos das funções.
#include <stdio.h>
#include <string.h>
#include <windows.h> // < Para utilizar o sleep no windows.
#include <unistd.h> // < Para o sleep funcionar, caso o SO seja Linux.

void ler_linha(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

// Ler valor double.
double ler_double(void) {double valor; scanf("%lf", &valor); limpar_buffer(); return valor;}

// Ler valor inteiro.
int ler_int(void) {int valor; scanf("%d", &valor); limpar_buffer(); return valor;}

// Limpar buffer.
void limpar_buffer(void) {int l; while ((l = getchar()) != '\n' && l != EOF);}

// Ler conta e valor.
void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor) {
    if (!conta || tam_conta == 0 || !valor) return;
    printf("Conta: ");
    ler_linha(conta, tam_conta);

    printf("Valor: ");
    if (scanf("%lf", valor) != 1) {
        // Leitura invalida -> zera e limpa buffer.
        *valor = 0.0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    // Consumir o '\n' que ficou no buffer do stdin.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Limpar tela.
void limpar_tela(void) {
    printf("\nPressione enter para retornar ao menu.\n");
    limpar_buffer();        // Limpa buffer.
    printf("\nRedirecionando para o menu...");      // Redireciona o usuario para o menu.

#ifdef _WIN32       // Se o SO for windows.
    Sleep(3000);        // Sleep para delay.
    system("cls");      // Realiza limpeza de tela.
#else       // Se for mac ou linux
    sleep(3000)     // Tempo de delay.
    system("clear");        // Limpa a tela do usuario.
#endif

}