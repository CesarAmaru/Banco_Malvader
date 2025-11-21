#include <stdio.h>
#include "banco.h"              // < Header com funções e estrutura do banco.
#include "io.h"                 // < Header com funções de entrada e saida de dados do usuario.

int main(void) {
    Banco banco;        // Declara a estrutura principal que gerencia o Banco.
    int op = 0;         // Variavel que guarda a opcao escolhida no menu.
    char conta[16], conta_dest[16];     // Strings que armazenam numeros das contas para operações.
    double valor;       // Valor utilizado em depositos, saques e transferencias.

    // Inicializar o banco : define arquivo e estrutura interno.
    banco_init(&banco, "data/clientes.txt", "data/movimentos.txt");

    // Carregar do arquivo os clientes que ja existiam.
    if (!banco_carregar(&banco)) {
        printf("Aviso: Nao foi possivel carregar clientes existentes.\n");
    }

    // Loop do menu principal.
    do {
        // Menu principal exibido ao usuario.
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
        printf(" [8] - Listar Contas\n");
        printf(" [9] - Reativar Conta\n");
        printf(" [0] - Sair\n");
        printf("====================================\n");
        printf("Opcao: ");

        op = ler_int();     // Ler opcao selecionada pelo usuario.

        // Executa uma funcao diferente de acordo com opcao selecionada no menu.
        switch(op) {
            case 1:     // Cadastrar novo cliente.
                banco_criar_conta(&banco);      // Chama o metodo de criar conta (banco.h).
                limpar_tela();      // Realiza limpeza da tela do usuario.
                break;      // Quebra repetiçao do switch.

            case 2:     // Encerrar conta de cliente ja cadastrado.
                banco_encerrar_conta(&banco);       // Chama o metodo de encerrar conta (banco.h).
                limpar_tela();      // Realiza limpeza da tela do usuario.
                break;      // Quebra repeticao do switch.

            case 3:     // Consulta os ddos do cliente.
                banco_consultar(&banco);        // Chama o metodo de realizar consulta a conta do cliente (banco.h).
                limpar_tela();      // Realiza limpeza de tela do usuario.
                break;      // Quebra repeticao do switch.

            case 4:     // Alterar dados do cliente.
                banco_alterar_dados(&banco);        // Chama o metodo de alterar os dados do cliente (banco.h).
                limpar_tela();      // Realiza limpeza da tela do usuario.
                break;      // Quebra repeticao do switch.

            case 5:     // Realizar deposito.
                banco_ui_depositar(&banco);     // Chama o metodo de realizar deposito (banco.h).
                limpar_tela();      // Realiza limpeza de tela do usuario.
                break;       // Quebra repeticao do switch.

            case 6:
                banco_ui_sacar(&banco);     // Chama o metodo de realizar saque (banco.h).
                limpar_tela();      // Realiza limpeza de tela do usuario.
                break;       // Quebra repetiçao do switch.

            case 7:
                banco_ui_transferir(&banco);        // Chama o metodo que realiza transferencias (banco.h).
                limpar_tela();      // Realiza limpeza de tela do usuario.
                break;       // Quebra repetiçao do switch.

            case 8:
                banco_menu_listagem(&banco);        // Chama o metodo menu_listagem para selecionar o tipo de listagem.
                limpar_tela();      // Realiza limpeza da tela do usuario.
                break;       // Quebra repetiçao do switch.

            case 9:
                banco_reativar_conta(&banco);       // Reativa conta inativa.
                limpar_tela();      // Realiza limpeza da tela do usuario.
                break;       // Quebra repetiçao do switch.

            case 0:     // Encerra o sistema.
                printf("\nEncerrando sistema...\n");        // Emite aviso de encerramento.
                printf("Ate logo!\n");
                break;       // Quebra repetiçao do switch.

            default:
                printf("\nOpcao invalida! Tente novamente.\n");     // Emite aviso caso nenhuma das opções fossem selecionadas.
                break;       // Quebra repetiçao do switch.
        }

    } while(op != 0);       // Condiçao para o looping.

    banco_free(&banco);     // Realiza liberaçao de memoria e fecha arquivos do banco.

    return 0;
}
