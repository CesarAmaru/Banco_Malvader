#include "io.h"
#include <stdio.h>
#include <string.h>
#include <windows.h> // para utilizar o sleep no windows
#include <unistd.h> // para o sleep funcionar, caso o SO seja Linux

void ler_linha(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

//ler valor double
double ler_double(void) {double valor; scanf("%lf", &valor); limpar_buffer(); return valor;}

//ler valor int
int ler_int(void) {int valor; scanf("%d", &valor); limpar_buffer(); return valor;}

//limpar buffer
void limpar_buffer(void) {int l; while ((l = getchar()) != '\n' && l != EOF);}

//ler conta e valor
void ler_conta_e_valor(char *conta, size_t tam_conta, double *valor) {
    if (!conta || tam_conta == 0 || !valor) return;
    printf("Conta: ");
    ler_linha(conta, tam_conta);

    printf("Valor: ");
    if (scanf("%lf", valor) != 1) {
        // leitura invalida -> zera e limpa buffer
        *valor = 0.0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    // consumir o '\n' que ficou no buffer do stdin
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//limpar tela
void limpar_tela(void) {
    printf("\nPressione enter para retornar ao menu.\n");
    limpar_buffer();
    printf("\nRedirecionando para o menu...");
#ifdef _WIN32 //se o SO for windows
    Sleep(3000); //Sleep para delay
    system("cls");
#else//se for mac ou linux
    sleep(3000)
    system("clear");
#endif


    void limpar_tela(void);
}

// Realizar a Listagem dos Clientes cadastrados.
void menu_listagem(Banco *banco) {
    int op_list;

    printf("\n====================================\n");
    printf("           LISTAR CONTAS            \n");
    printf("====================================\n");
    printf(" [1] - Listar por Numero da Conta\n");
    printf(" [2] - Listar por Nome\n");
    printf("Opcao: ");
    op_list = ler_int();

    switch(op_list) {
        case 1:
            ordenar_por_conta(banco->clientes, banco->tam);
            banco_listar_clientes(banco);
            break;

        case 2:
            ordenar_por_nome(banco->clientes, banco->tam);
            banco_listar_clientes(banco);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
    }
}