#include <stdio.h>
#include "banco.h"
#include "io.h"
int main(void) {
    Banco banco;
    banco_init(&banco, "data/clientes.txt", "data/movimentos.txt");
    banco_carregar(&banco);
    banco_free(&banco);

    int op = 0; //Variavel de controle para o switch.

    do {

        //Menu principal com opções principais do Banco.
        printf("\n====================================\n");
        printf("        Seja Bem-Vindo(a)!!         \n");
        printf("====================================\n");
        printf("Escolha uma opção:\n");
        printf(" [1] - Abrir Nova Conta\n");
        printf(" [2] - Encerrar Conta\n");
        printf(" [3] - Consultar Dados do Cliente\n");
        printf(" [4] - Alterar Dados do Cliente\n");
        printf(" [5] - Realizar Depósito\n");
        printf(" [6] - Realizar Saque\n");
        printf(" [7] - Listar Contas por Nome\n");
        printf(" [8] - Listar Contas por Número\n");
        printf(" [9] - Consultar Saldo da Conta\n");
        printf(" [0] - Sair\n");
        printf("====================================\n");
        scanf("%d", &op); //Lê a opção selecionada pelo usuário.

        switch(op){
            case 1:
                 /* abrir conta, ler campos com ler_linha, chamar banco_abrir_conta */
                 banco_criar_conta();
                 break;

            case 2:
                 /* encerrar conta, chamar banco_encerrar_conta */
                 break;

            case 3:
                 /* consultar, chamar banco_consultar_cliente e imprimir_dados_cliente */
                 break;

            case 4:
                 /* alterar dados, montar Cliente com novos campos permitidos, banco_alterar_dados */
                 break;

            case 5:
                 /* depósito, banco_depositar */
                 char conta[20];
                 double valor;

                 printf("Digite o número da conta: ");
                 ler_linha(conta, sizeof(conta));

                 printf("Digite o valor do depósito: ");
                 scanf("%lf", &valor);
                 getchar();

                 banco_depositar(Banco *b, conta, valor);
                 break;

            case 6:
                 /* saque, banco_sacar */

                 char conta[20];
                 double valor;

                 printf("Digite o número da conta: ");
                 ler_linha(conta, sizeof(conta));

                 printf("Digite o valor do saque: ");
                 scanf("%lf", &valor);
                 getchar();

                 banco_sacar(Banco &banco, conta, valor);
                 break;

            case 7:
                 /* listar por nome, banco_listar_ordenado_por_nome */
                 break;

            case 8:
                 /* listar por conta, banco_listar_ordenado_por_conta */
                 break;

            case 9:
                 /* consultar saldo, banco_listar_ordenado_por_conta */
                 banco_consultar_saldo();
                 break;
        }
    } while(op != 0);
    banco_free(&banco);

}