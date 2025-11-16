#include <stdio.h>
#include "banco.h"
#include "io.h"

int main(void) {
    Banco banco;
    int op = 0;
    char conta[16];
    double valor;

    // Inicializar o banco
    banco_init(&banco, "data/clientes.txt", "data/movimentos.txt");

    // Carregar clientes existentes
    if (!banco_carregar(&banco)) {
        printf("Aviso: Não foi possível carregar clientes existentes.\n");
    }

    do {
        // Menu principal
        printf("\n====================================\n");
        printf("        Seja Bem-Vindo(a)!!         \n");
        printf("====================================\n");
        printf("Escolha uma opcao:\n");
        printf(" [1] - Abrir Nova Conta\n");
        printf(" [2] - Encerrar Conta\n");
        printf(" [3] - Consultar Dados do Cliente\n");
        printf(" [4] - Alterar Dados do Cliente\n");
        printf(" [5] - Realizar Deposito\n");
        printf(" [6] - Realizar Saque\n");
        printf(" [7] - Listar Contas\n");
        printf(" [8] - Consultar Saldo da Conta\n");
        printf(" [0] - Sair\n");
        printf("====================================\n");
        printf("Opcao: ");

        op = ler_int();

        switch(op) {
            case 1:
                // Abrir conta
                banco_criar_conta(&banco);
                break;

            case 2:
                // Encerrar conta
                banco_encerrar_conta(&banco);
                break;

            case 3:
                // Consultar dados
                banco_consultar(&banco);
                break;

            case 4:
                // Alterar dados
                banco_alterar_dados(&banco);
                break;

            case 5:
                // Depósito
                printf("\n====================================\n");
                printf("           DEPOSITO                 \n");
                printf("====================================\n");
                printf("Digite o numero da conta: ");
                ler_linha(conta, sizeof(conta));

                printf("Digite o valor do deposito: R$ ");
                valor = ler_double();

                banco_depositar(&banco, conta, valor);
                break;

            case 6:
                // Saque
                printf("\n====================================\n");
                printf("             SAQUE                  \n");
                printf("====================================\n");
                printf("Digite o numero da conta: ");
                ler_linha(conta, sizeof(conta));

                printf("Digite o valor do saque: R$ ");
                valor = ler_double();

                banco_sacar(&banco, conta, valor);
                break;

            case 7:
                // Listar contas
                banco_listar_clientes(&banco);
                break;

            case 8:
                // Consultar saldo
                printf("\n====================================\n");
                printf("         CONSULTAR SALDO            \n");
                printf("====================================\n");
                printf("Digite o numero da conta: ");
                ler_linha(conta, sizeof(conta));

                banco_consultar_saldo(&banco, conta);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                printf("Ate logo!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while(op != 0);

    // Liberar memória antes de sair
    banco_free(&banco);

    return 0;
}