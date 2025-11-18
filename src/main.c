#include <stdio.h>
#include "banco.h"
#include "io.h"
#include "ordenacao.h"

int main(void) {
    Banco banco;
    int op = 0;
    char conta[16], conta_dest[16];
    double valor;

    // Inicializar o banco
    banco_init(&banco, "data/clientes.txt", "data/movimentos.txt");

    // Carregar clientes existentes
    if (!banco_carregar(&banco)) {
        printf("Aviso: Nao foi possivel carregar clientes existentes.\n");
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
        printf(" [7] - Realizar Transferencia\n");
        printf(" [8] - Listar por Conta\n");
        printf(" [9] - Listar por Nome\n");
        printf(" [10] - Reativar Conta\n");
        printf(" [0] - Sair\n");
        printf("====================================\n");
        printf("Opcao: ");

        op = ler_int();

        switch(op) {
            case 1:
                // Abrir conta
                banco_criar_conta(&banco);
                limpar_tela();
                break;

            case 2:
                // Encerrar conta
                banco_encerrar_conta(&banco);
                limpar_tela();
                break;

            case 3:
                // Consultar dados
                banco_consultar(&banco);
                limpar_tela();
                break;

            case 4:
                // Alterar dados
                banco_alterar_dados(&banco);
                limpar_tela();
                break;

            case 5:
                // Deposito
                printf("\n====================================\n");
                printf("           DEPOSITO                 \n");
                printf("====================================\n");
                printf("Digite o numero da conta: ");
                ler_linha(conta, sizeof(conta));

                printf("Digite o valor do deposito: R$ ");
                valor = ler_double();

                banco_depositar(&banco, conta, valor);
                limpar_tela();
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
                limpar_tela();
                break;

            case 7:
                // Saque
                printf("\n====================================\n");
                printf("              Transferencia            \n");
                printf("====================================\n");
                printf("Digite o numero da conta origem: ");
                ler_linha(conta, sizeof(conta));
                printf("Digite o numero da conta destino: ");
                ler_linha(conta_dest, sizeof(conta_dest));

                printf("Digite o valor da transeferencia: R$ ");
                valor = ler_double();

                banco_transferir(&banco, conta, conta_dest, valor);
                limpar_tela();
                break;

            case 8:
                // Listar contas
                banco_listar_clientes(&banco);
                limpar_tela();
                break;

            case 10:
                // Listar contas
                banco_reativar_conta(&banco);
                limpar_tela();
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

    // Liberar memoria antes de sair
    banco_free(&banco);

    return 0;
}